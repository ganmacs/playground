package parsers

import input._

trait Parsers {
  // the type of input element.
  type Elem

  def elem(e: Elem): Parser[Elem] = acceptIf(_ == e) ("`"+e+"' expected but " + _ + " found")

  def acceptIf(cond: Elem => Boolean)(err: Elem => String): Parser[Elem] = Parser { in =>
    if (in.atEnd) Failure("end of input", in)
    else if (cond(in.first)) Success(in.first, in.rest)
    else Failure(err(in.first), in)
  }

  class Parser[+T] (parse: Reader[Elem] => ParseResult[T, Elem]) {
    def apply(in: Reader[Elem]): ParseResult[T, Elem] = parse(in)
    // def map [U] (f: T => U): Parser[U] = Parser { in => parse(in).map(f) }
    // def seq [U] (f: => Parser[Elem, U]): Parser[Elem, ~[T, U]] = Parser { in => parse(in).seq(f) }
    def seq [U] (f: => Parser[U]): Parser[~[T, U]] = ???
  }

  object Parser {
    def apply[T] (f: Reader[Elem] => ParseResult[T, Elem]) = new Parser[T](f)
  }
}
