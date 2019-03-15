package msgpack

type Code byte

var (
	False Code = 0xc2
	True  Code = 0xc3

	Uint64 Code = 0xcf

	Str8  Code = 0xd9
	Str16 Code = 0xda
	Str32 Code = 0xdb

	Ary16 Code = 0xdc
	Ary32 Code = 0xdd
)
