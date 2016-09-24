class MutexDict
  def initialize(data_store)
    @store = data_store
    @dict = {}
    @dict_mutex = Mutex.new
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
            locks = {}          # flush
            break
          end
        end
      end

      next if locks.empty?

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
  def initialize
    @dict = {}
  end

  def inc(key)
    @dict[key] += 1
  end

  def init(key)
    @dict[key] = 0
  end
end

N = 5000
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

ts.each(&:join)
ts2.each(&:join)

p a.size
p b.size
p s
