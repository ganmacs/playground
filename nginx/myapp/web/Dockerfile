FROM ruby:2.4.0

RUN mkdir -p /app

# bundle install
COPY Gemfile Gemfile.lock /tmp/
RUN cd /tmp && bundle install -j4 --deployment --without 'development test'

WORKDIR /app
COPY . /app
# RUN cp -a /tmp/.bundle /tmp/vendor /app/
