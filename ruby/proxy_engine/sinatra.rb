require 'sinatra/base'
require 'logger'

my_app = Sinatra.new {
  set :port, 8000
  set :logging, Logger::DEBUG
  get('/') { "hi" }
}
my_app.run!
