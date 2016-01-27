package main

import "fmt"

type Song struct {
	SongName string
}

type Play struct {
	Song
	JobName string
}

type Next struct {
	JobName string
}

type Job interface {
	GetJobName() string
}

func (p *Play) GetJobName() string {
	return p.JobName + p.SongName
}

func (n *Next) GetJobName() string {
	return n.JobName
}

func get(j Job) string {
	return j.GetJobName()
}

func NewNext(job string) *Next {
	return &Next{JobName: job}
}

func NewPlay(job string, song string) *Play {
	s := Song{SongName: song}
	p := &Play{JobName: job}
	p.Song = s
	return p
}

func NewJobs(jobs ...Job) []Job {
	return jobs
}

func main() {
	jobs := NewJobs(
		NewPlay("Play: ", "kirakiraboshi"),
		NewNext("Skip  This Song"),
		NewPlay("Play: ", "uzaiaitu"),
	)

	for _, v := range jobs {
		fmt.Println(get(v))
	}
}
