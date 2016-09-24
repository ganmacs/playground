require 'timeout'
require 'pp'

class CleaupThread
  CLEANUP_INTERVAL = 60 * 15           # 15 min

  def initialize(store, dict, mutex)
    @store = store
    @dict = dict
    @mutex = mutex
    @thread = nil
  end

  def start
    @running = true
    @thread = Thread.new do
      while @running
        run_once
        sleep CLEANUP_INTERVAL
      end
    end
  end

  def stop
    @running = false
    begin
      # avoid to wait SLEEP_SEC
      Timeout.timeout(5) do
        @thread.join
      end
    rescue Timeout::Error
      @thread.kill              # ok?
    end
  end

  private

  def run_once
    @mutex.synchronize do
      @dict.each do |(key, mutex)|
        next if Time.now - SLEEP_SEC > @store.get(key).now

        if mutex.try_lock
          m = @dict.delete(key)     # `m` is same as `mutex`
          mutex.unlock

          # Check a waiting queue of lock.
          # Can't get a lock here means this key is used in other places.
          # So restore a mutex value to a corresponding key.
          unless m.locked?
            @dict[key] = m
          end
        end
      end
    end
  end
end

class MutexDict
  def initialize(data_store)
    @store = data_store
    @dict = {}
    @dict_mutex = Mutex.new
    @thread = nil
    @cleaup_thread = CleaupThread.new(@store, @dict, @dict_mutex)
  end

  def start
    @cleaup_thread.start
  end

  def stop
    @cleaup_thread.stop
  end

  def synchronize(*keys)
    locks = {}

    loop do
      @dict_mutex.synchronize do
        keys.each do |key|
          mutex = @dict[key]
          unless mutex
            v = Mutex.new
            @dict[key] = v
            mutex = v
          end

          if mutex.try_lock
            locks[key] = mutex
          else
            locks.values.each(&:unlock)
            locks = {}          # flush locked keys
            break
          end
        end
      end

      next if locks.empty?      # failed to lock all keys

      locks.each do |(k, v)|
        yield @store, k
        v.unlock
      end
      break
    end
  end

  def synchronize_key(*keys)
    keys = keys.dup

    while key = keys.shift
      @dict_mutex.lock

      mutex = @dict[key]
      unless mutex
        v = Mutex.new
        @dict[key] = v
        mutex = v
      end

      if mutex.try_lock
        @dict_mutex.unlock
        yield @store, key
        mutex.unlock
      else
        # release global lock
        @dict_mutex.unlock
        keys.push(key)          # failed lock, retry this key
      end
    end
  end
end

class Store
  VALUE = Struct.new(:value, :now)

  def initialize
    @dict = {}
  end

  def inc(key)
    v = @dict[key]
    v.value = v.value + 1
    v.now = Time.now
  end

  def init(key)
    @dict[key] = VALUE.new(0, Time.now)
  end

  def get(key)
    @dict[key]
  end
end

N = 1000
s = Store.new

v = MutexDict.new(s)
v.synchronize('key', 'key2', 'key3') do |store, key|
  store.init(key)
end

a = []
ts = N.times.map do |x|
  Thread.new(x) do |i|
    v.synchronize('key', 'key2', 'key3') do |store, key|
      store.inc(key)
      a << i
    end
  end
end

b = []
ts2 = N.times.map do |x|
  Thread.new(x) do |i|
    v.synchronize_key('key', 'key2', 'key3') do |store, key|
      store.inc(key)
      b << i
    end
  end
end

v.start
ts.each(&:join)
ts2.each(&:join)
v.stop

p a.size
p b.size
pp s
