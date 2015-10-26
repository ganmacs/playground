class RValue
  attr_accessor :next_obj, :ref_count

  def initialize(next_obj: nil)
    @next_obj = next_obj
    @ref_count = 0
  end

  def ref!
    @ref_count += 1
  end

  def unref!
    @ref_count -= 1
  end

  def last?
    @next_obj.nil?
  end

  def alloc!
    @next_obj = nil
    ref!
    self
  end

  def to_s
    a = super
    "#{a}, refcount: #{ref_count}"
  end
end

class FreeList
  def initialize(limit)
    @limit = limit
  end

  def allocate
    check_allocatable!

    ret = freelist
    @freelist = freelist.next_obj

    ret.alloc!
  end

  def sweep(obj)
    last.next_obj = obj
  end

  def inspect
    str = ''
    str += "======== freelist ========\n"

    t = freelist
    loop do
      str +=  "-> #{t} \n"
      break if t.last?
      t = t.next_obj
    end
    str += "==========================\n\n"

    str += "======== objectlist ========\n"
    str += free_ary.map(&:to_s).join("\n")
    str += "\n==========================\n"
    str
  end

  private

  def freelist
    @freelist ||= free_ary[1..-1].reduce(free_ary.first) do |a, e|
      e.next_obj = a
      e
    end
  end

  def last
    t = freelist
    loop do
      break if t.last?
      t = t.next_obj
    end
    t
  end

  def free_ary
    @free_ary ||= @limit.times.map { RValue.new }
  end

  def check_allocatable!
    fail "Could not allocate object" if freelist.last?
  end
end

class MSGC
  MARK = 0
  UNMARK = 1
  MEMORY_SIZE = 10

  attr_reader :free_bit_map

  def initialize
    @free_bit_map = []
    @allocated_objs = []
    @size = 0
  end

  def run
    run_mark
    run_sweep
  end

  # return RObject
  def allocate
    obj = freelist.allocate
    @allocated_objs << obj
    puts "alloc #{obj}"
    obj
  end

  # erase ref
  def free(obj)
    obj.unref!
    puts "free! #{obj}"
  end

  def inspect
    freelist.inspect
  end

  private

  def run_mark
    @allocated_objs.each do |al|
      if al.ref_count > 0
        @free_bit_map << MARK
      else
        @free_bit_map << UNMARK
      end
    end
  end

  def run_sweep
    new_objs = []
    @free_bit_map.each_with_index do |e, i|
      if e == MARK
        new_objs << @allocated_objs[i]
      else
        freelist.sweep(@allocated_objs[i])
      end
    end
    @free_bit_map = []
    @allocated_objs = new_objs
  end

  def freelist
    @freelist ||= FreeList.new(MEMORY_SIZE)
  end
end

gc = MSGC.new
p gc

a0 = gc.allocate
a1 = gc.allocate
a2 = gc.allocate
a3 = gc.allocate
a4 = gc.allocate
a5 = gc.allocate
a6 = gc.allocate
a7 = gc.allocate
a8 = gc.allocate

gc.free(a3)
gc.free(a5)
gc.free(a7)
p gc
gc.run
p gc
