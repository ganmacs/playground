FROM rubylang/ruby:2.6.5-bionic

RUN mkdir -p /app

# bundle install
COPY Gemfile Gemfile.lock /tmp/
RUN cd /tmp && bundle install -j4 --deployment --without 'development test'

WORKDIR /app
COPY . /app

CMD ["bundle", "exec", "ruby", "app.rb"]
