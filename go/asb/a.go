package main

import (
	"fmt"
	"os/exec"
)

func main() {

	fmt.Println("start")
	cmd := exec.Command("sleep", "5")
	fmt.Println("start 2")
	if e := cmd.Start(); e != nil {
		fmt.Println(e)
	}
	fmt.Println("start 3")

	cmd.Wait()
}
