-module(sample61).
-export([start/0,proc/2]).

proc(Greeting, 0) ->
    io:format("~p terminate~n", [Greeting]);
proc(Greeting, X) ->
    io:format("~p : ~p.~n",[Greeting, X]),
    proc(Greeting, X - 1).

start() ->
    spawn(sample61, proc, ["Hello", 5]),
    spawn(sample61, proc, ["Hi", 5]).
