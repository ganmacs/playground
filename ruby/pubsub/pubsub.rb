require 'set'

class Broker
  def register_pub(publisher, channel: :default)
    publisher << publisher
    self
  end

  def register_sub(subscriber, channel: :default)
    subscribers << subscriber
    self
  end

  private

  def subscribers
    @subscribers ||= Set.new
  end

  def publishers
    @publishers ||= Set.new
  end

  module Publisher
  end

  module Subscriber
  end
end

class Pub
  def publish
    # something
  end
end

class Sub
  def subscribe(msg)
    puts msg
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
