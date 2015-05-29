# Reading "Working with TCP Sockets"

### server lifecycle

socketのportとip addressはユニークである

socketは2つの役割を持つ必要があるinitiator, listener

create: socket作る
bind: portとipをしてい
listen: コネクションまちリストの数を指定
accept: 接続を受け入れ
close: コネクションを閉じる

```
require 'socket'

# create
server = Socket.new(:INET, :STREAM)

# bind
addr = Socket.pack_sockaddr_in(4481, '0.0.0.0')
server.bind(addr)

# listen
server.listen(128)

loop do
  # accept
  connection, _ = server.accept

  # handle connection

  # close
  connection.close
end
```

### client lifecycle

create, bind, connect ,closeの順
bindは普通しないらしい

### Exchangeing Data

### Sockets Can Read

### Sockets can Write

一気にたくさん書くのがいいか，分けて細かく書くのがいいか
ー＞バッファを使ってkernelがいい感じにやってくれる

### Our First Client/Server


