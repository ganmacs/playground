this is Plugin mechanism.

`Plug.const_get`で`Plug::`の名前空間から`class_name`として渡されたものがあるかを探す  
なのでpluginとして新たに追加したい場合は`Plug::Hoge`のようなクラスを作ってそれを`require`することで`Plug::`以下の名前空間に`Hoge`が作られるので`constg_get`の対象となって後からいくらでもactionのようなpluginをたせる

```sh
$ bundle exec ruby run
```

