package patt

type BehivorC interface {
	DoSomethingByOther()
}

type Abstract struct {
}

func (s *Abstract) DoSomething(behivor BehivorC) {
	behivor.DoSomethingByOther()
}

type Concrete struct {
	*Abstract
}

func (c *Concrete) DoSomethingByOther() {
	// do something
}

func NewConcrete() *Concrete {
	concrete := &Concrete{}
	return concrete.DoSomething(concrete)
}
