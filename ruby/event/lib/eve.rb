require 'eve/agent'

module Eve
  class << self
    def start(data)
      nodes = data[:nodes]
      leader, followers = nodes.partition { |e| e[:leader] }
      leader = leader.first

      uris = followers.map do |e|
        "#{e[:addr]}:#{e[:port]}"
      end

      evloop = Cool.io::Loop.default

      # leader
      opt = leader.merge(
        heartbeat_rate: data[:heartbeat_rate],
        evloop: evloop,
        cluster: uris,
      )
      puts "starting leader node"
      Agent.new(opt).start

      followers.each_with_index do |e, i|
        op = e.merge(evloop: evloop)
        puts "starting #{e[:name]}"
        Agent.new(op).start
      end

      evloop.run(0.01)
    end
  end
end
