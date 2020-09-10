# app.rb
require "sinatra"

set :bind, '0.0.0.0'
set :port,  3000

get "/" do

  puts request.env
  p request.env
  # status 500
  status 200
  # "Hello World!"
end
