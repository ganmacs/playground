package msgpack

import (
	"io"
	"reflect"
)

var (
	BinLen4  = (2 << 4) - 1
	BinLen5  = (2 << 5) - 1
	BinLen8  = (2 << 8) - 1
	BinLen16 = (2 << 16) - 1
	BinLen32 = (2 << 32) - 1
)

type myWriter interface {
	io.Writer
	WriteByte(byte) error
	WriteString(string) (int, error)
}

type Encoder struct {
	w   myWriter
	buf []byte
}

func NewEncoder(w io.Writer) *Encoder {
	bw, ok := w.(myWriter)
	if !ok {
		panic("failed!")
	}

	return &Encoder{
		w:   bw,
		buf: make([]byte, 10),
	}
}

func (e *Encoder) Encode(v interface{}) error {
	switch t := v.(type) {
	case bool:
		return e.encodeBool(t)
	case uint64:
		return e.encodeUint64(t)
	case string:
		return e.EncodeString(t)
	}

	return e.encodeValue(reflect.ValueOf(v))
}

func (e *Encoder) encodeValue(v reflect.Value) error {
	t := v.Kind()

	switch t {
	case reflect.Array:
		return e.encodeArray(v)
	case reflect.Uint64:
		return e.encodeUint64(uint64(v.Uint()))
	}
	return nil
}

func (e *Encoder) encodeArray(v reflect.Value) error {
	l := v.Len()

	if err := e.EncodeArrayLen(l); err != nil {
		return err
	}

}

func (e *Encoder) encodeArrayLen(len int) error {
	if len < BinLen4 {
		return e.writeCode(0x90 | Code(len))
	}

	if len < BinLen16 {
		return e.write2(Ary16, uint16(len))
	}

	return e.write4(Ary32, uint32(len))
}

func (e *Encoder) encodeBool(v bool) error {
	if v {
		return e.writeCode(True)
	}
	return e.writeCode(False)
}

func (e *Encoder) encodeUint64(v uint64) error {
	return e.write8(Uint64, v)
}

func (e *Encoder) EncodeString(v string) error {
	if err := e.encodeStrLen(len(v)); err != nil {
		return err
	}
	return e.encodeString(v)
}
func (e *Encoder) encodeString(v string) error {
	_, err := e.w.WriteString(v)
	return err
}

func (e *Encoder) encodeStrLen(len int) error {
	if len < BinLen5 {
		return e.writeCode(0xa0 | Code(len))
	}
	if len < BinLen8 {
		return e.write1(Str8, uint8(len))
	}
	if len < BinLen16 {
		return e.write2(Str16, uint16(len))
	}

	return e.write4(Str32, uint32(len))
}

func (e *Encoder) write1(code Code, v uint8) error {
	e.buf = e.buf[:2]
	e.buf[0] = byte(code)
	e.buf[1] = byte(v)
	return e.write()
}

func (e *Encoder) write2(code Code, v uint16) error {
	e.buf = e.buf[:3]
	e.buf[0] = byte(code)
	e.buf[1] = byte(v >> 8)
	e.buf[2] = byte(v)
	return e.write()
}

func (e *Encoder) write4(code Code, v uint32) error {
	e.buf = e.buf[:5]
	e.buf[0] = byte(code)
	e.buf[1] = byte(v >> 24)
	e.buf[2] = byte(v >> 16)
	e.buf[3] = byte(v >> 8)
	e.buf[4] = byte(v)
	return e.write()
}

func (e *Encoder) write8(code Code, v uint64) error {
	e.buf = e.buf[:9]
	e.buf[0] = byte(code)
	e.buf[1] = byte(v >> 56)
	e.buf[2] = byte(v >> 48)
	e.buf[3] = byte(v >> 40)
	e.buf[4] = byte(v >> 32)
	e.buf[5] = byte(v >> 24)
	e.buf[6] = byte(v >> 16)
	e.buf[7] = byte(v >> 8)
	e.buf[8] = byte(v)
	return e.write()
}

func (e *Encoder) write() error {
	_, err := e.w.Write(e.buf)
	return err
}

func (e *Encoder) writeCode(code Code) error {
	return e.w.WriteByte(byte(code))
}
