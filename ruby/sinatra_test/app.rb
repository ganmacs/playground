require 'sinatra/base'
require 'yaml'
require 'erb'
require 'tilt/erb'
require_relative 'models/user.rb'
require_relative 'utils/loader.rb'

class App < Sinatra::Base
  get '/' do
    @users = users.all

    erb :index
  end

  get '/create' do

    erb :create
  end

  post '/new' do
    @repo = @params['repo']
    @user = users.find { |e| e.repo == @repo }

    erb :new
  end

  def users
    @users ||= Utils::Loader.new(:User, 'users.data')
  end
end
