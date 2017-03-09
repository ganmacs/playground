package main

import (
	"crypto/tls"
	"log"
)

func main() {
	log.SetFlags(log.Lshortfile)

	conf := &tls.Config{
		InsecureSkipVerify: true,
	}

	conn, err := tls.Dial("tcp", "127.0.0.1:443", conf)
	if err != nil {
		log.Println(err)
		return
	}
	defer conn.Close()

	if n, err := conn.Write([]byte("hello\n")); err != nil {
		log.Println(n, err)
		return
	}

	buf := make([]byte, 100)
	if n, err := conn.Read(buf); err != nil {
		log.Println(n, err)
		return
	}

	log.Println("return: " + string(buf))
}
