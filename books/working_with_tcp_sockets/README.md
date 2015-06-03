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

### Netwrok Architecture Pattern

### Serial

すべてのクライアントのコネクションを連続的にとりあつかう(並行ではない)

1. クライアントがコネクションをつくる
2. クライアントとサーバがリクエストとレスポンスを交換する
3. クライアントがコネクションをきる
4. １番にもどる

##### pros and cons

_pros_

* シンプルであること(ロックがない，共有状態がない)

_cons_

* 並行処理できない(他のコネクションがあるときはブロックされてしまう)

### Process per connection

forkを使って実現
ロックとかしなくていいし便利？

1. サーバにコネクションが来る
2. メインのサーバプロセスがconnectionを受け付ける
3. メインのサーバプロセスのコピー（全く同じ）をforkする
4. メインのプロセスは最初に戻って，並列に子プロセスはコネクションを処理

##### pros and cons

_pros_

* マルチクライアントに対応するのにシリアルだっと時に比べても十分シンプルシンプル
* ロックとか競合状態もない

_cons_

* fork数に上限がないので，大量にforkしてしまうとシステムが落ちる可能性がある
* OSに依存している

### Thread per connection

前章のプロセスがスレッドに変わったパターン

プロセスに比べて軽量だけど
スレッドの数が増えすぎるとシステムを圧迫する

#### threads vs processes

_Spawning_

* スレッドはプロセスに比べコストが小さい
* プロセスを作るときは元のプロセスのすべてをコピーする
* スレッドは１つのプロセスで動きメモリを共有するのでコピーするよりはやい

_Synchronizing_

* スレッドはメモリをスレッド同士で共有しているので，データを触るときは十分に気をつける必要がある(mutex, lock, synchronizingとかをつかう)
* プロセスはそれぞれすべてをコピーして作られているのでそんなめんどいことはない

_Parallelism_

* グローバルロック

_スレッドは軽くて，プロセスはそれに比べ重い．_
_両方共，並列実行できる．_
_それぞれに対してユースケースがある．_

