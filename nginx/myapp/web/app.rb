# app.rb
require "sinatra"

set :bind, '0.0.0.0'

get "/" do
  # status 500
  status 500
  # "Hello World!"
end
