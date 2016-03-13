package main

import (
	"bufio"
	"fmt"
	// _ "net/http/pprof"
	"os"
	"os/exec"
	"path/filepath"
	"runtime/pprof"
	"sync"
)

type Repository struct {
	path string
	name string
}

func getReposChannel() chan *Repository {
	repoChan := make(chan *Repository, 50)

	cmd := exec.Command("ghq", "list", "-p")
	defer cmd.Wait()

	stdout, err := cmd.StdoutPipe()
	if err != nil {
		panic(err)
	}

	if err := cmd.Start(); err != nil {
		fmt.Println(err)
		os.Exit(1)
	}

	scanner := bufio.NewScanner(stdout)

	go func() {
		wg := new(sync.WaitGroup)

		for scanner.Scan() {
			wg.Add(1)
			go func(repo string) {
				fmt.Println(repo)
				repoChan <- &Repository{
					repo,
					filepath.Base(repo),
				}
				wg.Done()
			}(scanner.Text())
		}

		wg.Wait()
		close(repoChan)
	}()
	return repoChan
}

func getCommitChannel(repoChan chan *Repository) {
	wg := new(sync.WaitGroup)

	for receive := range repoChan {
		wg.Add(1)
		go func(receive *Repository) {
			cmd2 := exec.Command("git", "log", "--pretty=format:"+"<%an> %B"+"%x07")
			cmd2.Dir = receive.path
			defer cmd2.Wait()

			stdout, err := cmd2.StdoutPipe()
			if err != nil {
				panic(err)
			}

			if err := cmd2.Start(); err != nil {
				os.Exit(1)
			}

			scanner := bufio.NewScanner(stdout)

			for scanner.Scan() {
				scanner.Text()
				// fmt.Println()
				// fmt.Println("a")
			}
			fmt.Println(receive.path)

			wg.Done()
		}(receive)
		// fmt.Println(receive)
	}
	wg.Wait()
}

func main() {
	cpuprofile := "mycpu.prof"
	f, _ := os.Create(cpuprofile)
	pprof.StartCPUProfile(f)
	defer pprof.StopCPUProfile()

	repoChan := getReposChannel()
	getCommitChannel(repoChan)
}

// if cpu := runtime.NumCPU(); cpu == 1 {
// 	runtime.GOMAXPROCS(2)
// } else {
// 	fmt.Println(cpu)
// runtime.GOMAXPROCS(cpu)
// }

// runtime.GOMAXPROCS(4)
// byt, _ := exec.Command("ghq", "list", "-p").CombinedOutput()
// bytes.Replace(byt)
