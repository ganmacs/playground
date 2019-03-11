FROM ruby:2.5

RUN apt-get update && apt-get install -y valgrind vim build-essential

RUN mkdir -p /app


COPY Gemfile Gemfile.lock /tmp/
RUN cd /tmp && bundle install -j4 --deployment --without 'development test' --path /app/vendor/bundle

COPY . /app
WORKDIR /app

EXPOSE 50051

CMD ["bundle", "exec", "ruby", "server.rb"]
