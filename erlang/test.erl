-module(test).
-export([test/0, test/1, test/2, length/2]).


test() -> io:format("引数なし~n").
test(X) -> io:format("~p~n",[X]).
test(X, Y) -> io:format("~p~n",[X]),
              io:format("~p~n",[Y]).

length(A, B) ->
  A2 = A + A,
  B2 = B + B,
  math:sqrt(A2 + B2).
