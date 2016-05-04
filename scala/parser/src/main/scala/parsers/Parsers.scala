package parsers

import input._

trait Parsers {
  // the type of input element.
  type Elem

  def elem(e: Elem): Parser[Elem] = acceptIf(_ == e) ("`"+e+"' expected but " + _ + " found")
  def elem(kind: String, p: Elem => Boolean): Parser[Elem] = acceptIf(p) (kind+" expected but "+ _ +"found")

  def acceptIf(cond: Elem => Boolean)(err: Elem => String): Parser[Elem] = Parser { in =>
    if (in.atEnd) Failure("end of input", in)
    else if (cond(in.first)) Success(in.first, in.rest)
    else Failure(err(in.first), in)
  }

  def success[T](x: T): Parser[T] = Parser { in => Success(x, in) }

  /** Other class can't access type of Parser, Because Parser is inner class of Parsers(only visible in Parsers).
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
    def opt: Parser[Option[T]] = map { Some(_) } orElse success(None)
    def rep: Parser[List[T]] = rep1 orElse success(Nil)
    def rep1: Parser[List[T]] = seq(rep) map { case x ~ xs => x :: xs }
    def repsep(sep: => Parser[Any]): Parser[List[T]] = rep1sep(sep) orElse success(Nil)
    def rep1sep (sep: => Parser[Any]): Parser[List[T]] = seq((sep ~> repsep(sep)).opt) ^^ {
      case x ~ xs => xs.fold(List(x))(x :: _)
    }

    def seq[U](f: => Parser[U]): Parser[T ~ U] = {
      lazy val p = f
      for ( a <- this; b <- p ) yield new ~(a, b)
    }

    def ~ [U](p: => Parser[U]): Parser[T ~ U] = seq(p)
    def ~> [U] (p: => Parser[U]): Parser[U] = seq(p) map { _.second }
    def <~ [U] (p: => Parser[U]): Parser[T] = seq(p) map { _.first }
    def | [U >: T](p: => Parser[U]): Parser[U] = orElse(p)
    def ? : Parser[Option[T]] = opt
    def + : Parser[List[T]] = rep1
    def * : Parser[List[T]] = rep
    def * (sep: => Parser[Any]): Parser[List[T]] = repsep(sep)
    def + (sep: => Parser[Any]): Parser[List[T]] = rep1sep(sep)
    def ^^ [U] (f: T => U): Parser[U] = map(f)
    def ^^^ [U] (f: => U): Parser[U] = map(_ => f)
  }

  private[parsers] object Parser {
    def apply[T] (f: Reader[Elem] => ParseResult[T, Elem]) = new Parser[T](f)
  }
}
