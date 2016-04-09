-module(a).
-export([length/1]).

length([_|XS], C) -> length(XS, C+1);
length([], C) -> C.

length(XS)-> length(XS, 0).
