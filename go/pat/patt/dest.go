package patt

type Strategy interface {
	DoSomthing()
}

type ConcreteStrategy struct {
}

func (s *ConcreteStrategy) DoSomthing() {
	// Do something
}

type StructS struct {
	strategy Strategy
}

func (s *StructS) Operation() {
	s.strategy.DoSomthing()
}
