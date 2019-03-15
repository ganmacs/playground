package msgpack

import (
	"io"
)

type bufReader interface {
	io.Reader
}

type Decoder struct {
	buf []byte
	r   io.Reader
}

func NewDecoder(r io.Reader) *Decoder {
	return &Decoder{
		buf: make([]byte, 0, 64),
		r:   r,
	}
}

func (d *Decoder) Decode(v interface{}) (err error) {
	switch v := v.(type) {
	case *string:
		*v, err = d.DecodeString()
		return err
	}

	return nil
}

func (d *Decoder) DecodeString(v interface{}) (string, err error) {

}
