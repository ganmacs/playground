$LOAD_PATH << File.expand_path('.')

require 'bidi_channel'
require 'logger'

$logger = Logger.new(STDOUT)

client = BidiChannel::Client.new(logger: $logger)
client.setup_connection('worker_1')

Thread.new do
end

client.send("hihihihihhi")
