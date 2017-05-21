require 'sinatra/base'

class HelloApp < Sinatra::Base
  get '/' do
    'hello World'
  end
end

run HelloApp
