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

  /** other class can't access type of Parser, Because Parser is inner class(visible in this class).
    * So, Extending BaseParser (Reader[Elem] => ParseResult[T, Elem] ) allows
    * other classes to use Reader[Elem] => ParseResult[T, Elem] as a reciver type
    **/
  private type BaseParser[T] = Reader[Elem] => ParseResult[T, Elem]

  //  T is type parameter of input type
  private[parsers] class Parser[+T] (val parse: BaseParser[T]) extends BaseParser[T] {
    def apply(in: Reader[Elem]): ParseResult[T, Elem] = parse(in)

    def map[U](f: T => U): Parser[U] = Parser { in => parse(in).map(f) }
    def flatMap[U](f: T => Parser[U]): Parser[U] = Parser { in => parse(in).flatMapWithNext(f) }
    def orElse [U >: T](p: Parser[U]): Parser[U] = Parser { in => parse(in) orElse p(in) }

    def seq[U](p: Parser[U]): Parser[T ~ U] = {
      lazy val q = p
      for ( a <- this; b <- q ) yield new ~(a, b)
    }

    def ~ [U](p: Parser[U]): Parser[T ~ U] = seq(p)
    def | [U >: T](p: Parser[U]): Parser[U] = orElse(p)
    def ^^ [U] (f: T => U): Parser[U] = map(f)
  }

  private[parsers] object Parser {
    def apply[T] (f: Reader[Elem] => ParseResult[T, Elem]) = new Parser[T](f)
  }
}
