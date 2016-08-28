require 'thread'

class RequestQueue
  def initialize
    @queue = Queue.new
  end

  def pop
    @queue.pop
  end

  def push(req)
    @queue.push req
  end

  def size
    @queue.size
  end
end

class Request
  def initialize(name)
    @name = name
  end

  def to_s
    "[ Request #{@name} ]"
  end
end

class ServerThread < Thread
  def initialize(queue, name)
    @queue = queue
    @name = name
    block = Proc.new do
      10000.times do
        req = @queue.pop
        puts "#{@name} handles  #{req}  #{@queue.size}"
        sleep rand(4)
      end
    end

    super(&block)
  end
end

class ClientThread < Thread
  def initialize(queue, name)
    @queue = queue
    @name = name
    block = Proc.new do
      10000.times do |i|
        req = Request.new("No.#{i}")
        @queue.push req
        puts "#{@name} requests #{req}  #{@queue.size}"
        sleep rand(2)
      end
    end

    super(&block)
  end
end

# q = RequestQueue.new
# threads = [ServerThread.new(q, 'Bobby'), ClientThread.new(q, 'Alice')]
# threads.each(&:join)

# puts "END"

class Server
  def initialize(queue, name)
    @queue = queue
    @name = name
  end

  def run
    a = Thread.new do
      10.times do
        req = @queue.pop
        puts "Handle #{@name}: #{req}"
        sleep 2
      end
    end
  end
end

class Client
  def initialize(queue, name)
    @queue = queue
    @name = name
  end

  def run
    a = Thread.new do
      10.times do |i|
        @queue.push i
        puts "Request #{@name}: #{i}"
        sleep 3
      end
    end
    a.join
  end
end

q = Queue.new
Server.new(q, 'You').run
Client.new(q, 'I').run
