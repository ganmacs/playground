# Reading "Working with TCP Sockets"

https://pragprog.com/book/jstcp/working-with-tcp-sockets

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

### Non-blocking IO

selectはsocketが読み込み可能になるまで待つのでretryはデータが読み込み可能になった時のみ動く

### Multiplexing Connection

selectはIOのオブジェクト配列を渡すと読み込みまたは書き込み可能なものを返す
ファイルディスクリプタが読み込み，または書き込み可能かを教える

### Framing Messages

メッセージのフォーマットの仕方

Protocol vs Message
プロトコルはヘッダーとかと同じように，メッセージの境界を定義する

gets,putsはクライアントとサーバが同じOSじゃないとだめ
-> `$/` がデフォルトのデリミタだけどこの変数はunixだと`\n`だしwindowsだと`\r\n`だから

content lengthをきめる決めてそれを最初に送って受信者はそれを見てデータを受け取る

### Timeouts

### DNS Lookups

### SSL Sockets

### Urgent Data

Urgent dataは一番最初に送ることができる
帯域外として？

