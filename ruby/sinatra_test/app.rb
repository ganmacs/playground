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
    p YAML.load_file('src/users.data.yml')

    erb :create
  end

  post '/new' do
    @repo = @params['repo']
    @user = users.find { |e| e.repo == @repo }

    unless @user
      user = Models::User.new(repo: @repo, ip: '')
      user.save
    end

    erb :new
  end

  def users
    @users ||= Utils::Loader.new(:User, 'src/users.data.yml')
  end
end
