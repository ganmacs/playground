worker_processes 2

listen 8080

after_fork do |server, worker|
  server.logger.info("[after_fork] worker=#{worker.nr} pid=#{$$}")
end

after_worker_exit do |server, worker, status|
  server.logger.info("[after_worker_exit] worker=#{worker.nr} pid=#{$$} status=#{status}")
end

after_worker_ready do |server, worker|
  server.logger.info("[after_worker_ready] worker=#{worker.nr} pid=#{$$}")
end

before_exec do |server|
  server.logger.info("[before_exec] pid=#{$$}")
end

before_fork do |server, worker|
  server.logger.info("[before_fork] worker=#{worker.nr} pid=#{$$}")
end
