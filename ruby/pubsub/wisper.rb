require 'set'

class Lister
  def initialize(obj)
    @obj = obj
  end

  def broadcast(event_name, args)
    if @obj.respond_to?(event_name)
      @obj.public_send(event_name, *args)
    end
  end
end

class BlockLister
  def initialize(event_name, block)
    @block = block
    @event_name = event_name
  end

  def broadcast(event_name, args)
    if @event_name == event_name
      @block.call(*args)
    end
  end
end

module Publisher
  def broadcast(event_name, *args)
    listeners.each do |l|
      l.broadcast(event_name, args)
    end
  end

  def subscribe(lister)
    listeners << Lister.new(lister)
    self
  end

  def on(event_name, &block)
    listeners << BlockLister.new(event_name, block)
    self
  end

  private

  def listeners
    @listeners ||= Set.new
  end
end

module Subscriber
  def subscribe(pub)
    pub.subscribe(self)
  end
end

class Pub
  include Publisher

  def call(f)
    if f
      broadcast(:on_success, 'saikou')
    else
      broadcast(:on_fail, 'saiaku')
    end
  end
end

class Sub
  include Subscriber

  def on_success(msg)
    puts msg
  end

  def on_fail(msg)
    fail msg
  end
end

pub = Pub.new
sub = Sub.new
sub1 = Sub.new
sub2 = Sub.new

pub.on(:on_success) { |x| puts "on #{x}" }
sub.subscribe(pub)
sub1.subscribe(pub)
sub2.subscribe(pub)

pub.call(true)

begin
  pub.call(false)
rescue => e
  puts e
end
