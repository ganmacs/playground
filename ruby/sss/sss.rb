$LOAD_PATH << File.expand_path(File.join('.'))

require 'logger'

require 'worker'
require 'manager'
require 'engine'

$log = Logger.new(STDOUT)
Engine.new(
  worker_size: 3
).run
