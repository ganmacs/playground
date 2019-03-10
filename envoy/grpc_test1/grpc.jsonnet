{
  version: 1,
  dependencies: [
    {
      name: 'grpc1',
      lb: 'localhost:80',
      cluster_name: 'grpc1',
      connect_timeout_ms: 4000,
      tls: false,
      circuit_breaker: {
        max_connections: 64,
        max_pending_requests: 128,
        max_retries: 3,
      },
      routes: [
        {
          path: '/helloworld.Greeter/SayHello',
          timeout_ms: 3000,
          method: 'POST',
          retry_policy: {
            retry_on: '5xx,connect-failure,refused-stream,cancelled,deadline-exceeded,resource-exhausted',
            num_retries: 3,
            per_try_timeout_ms: 1000,
          },
        },
      ],
    },
  ],
}
