FROM ruby:2.5

COPY Gemfile Gemfile.lock /tmp/
RUN cd /tmp && bundle install -j4 --deployment --without 'development test'

RUN mkdir -p /app
WORKDIR /app
COPY . /app
RUN cp -a /tmp/vendor /app/

EXPOSE 8080

CMD ["bundle", "exec", "ruby", "app.rb"]
