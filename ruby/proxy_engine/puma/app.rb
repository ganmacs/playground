require 'sinatra'

configure { set :server, :puma }

class HelloApp < Sinatra::Base
  get '/' do
    'hello World'
  end
end
