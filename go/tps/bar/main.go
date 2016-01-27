package main

import (
	"fmt"
	"strings"
)

type Cmd struct {
	Name string
	Args []string
}

func New(ss string) {
	for s := range strings.Split(ss, " ") {
		fmt.Println(s)
	}
}

func (c *Cmd) WithArg(s string) {
	c.Args = append(c.Args, s)
}

func gitOutput(input ...string) {
	cmd := New("git")
	for _, i := range input {
		cmd.WithArg(i)
	}
}

func gitGetConfig(name ...string) {
}

func GlboalConfig(name string) (string, error) {
	return gitGetConfig(anem)
}

func main() {
	GlobalConfig()
	// cmd.GitGlobal()
}
