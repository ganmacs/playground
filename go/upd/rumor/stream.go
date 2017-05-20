package rumor

import (
	"bufio"
	"io"
	"net"
)

type stream struct {
	conn   net.Conn
	reader io.Reader
}

// ReaderWriterCloser
func newStream(conn net.Conn) *stream {
	var bufConn io.Reader = bufio.NewReader(conn)

	return &stream{
		conn:   conn,
		reader: bufConn,
	}
}

func (p *stream) Read(buf []byte) (int, error) {
	return p.reader.Read(buf)
}

func (p *stream) Write(buf []byte) (int, error) {
	return p.conn.Write(buf)
}

func (p *stream) Close() error {
	return p.conn.Close()
}
