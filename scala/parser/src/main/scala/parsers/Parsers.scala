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

    def ~[U](p: Parser[U]): Parser[T ~ U] = seq(p)
    def ^^[U] (f: T => U): Parser[U] = map(f)

    def map[U](f: T => U): Parser[U] = Parser { in => parse(in).map(f) }
    def seq[U](p: => Parser[U]): Parser[T ~ U] = Parser { in =>
      parse(in) match {
        case Success(x, y) => p(y) match {
          case Success(x2, y2) => Success(new ~(x, x2), y2)
        }
        case Failure(x, y) => Failure(x, y)
      }
    }

    // def map [U] (f: T => U): Parser[U] = Parser { in => parse(in).map(f) }
    // def seq [U] (f: => Parser[Elem, U]): Parser[Elem, ~[T, U]] = Parser { in => parse(in).seq(f) }
  }

  object Parser {
    def apply[T] (f: Reader[Elem] => ParseResult[T, Elem]) = new Parser[T](f)
  }
}
