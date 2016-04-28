package parsers

import input._

trait Parsers {
  // the type of input element.
  type Elem

  private[parsers] class Parser[+T] (parse: Reader[Elem] => ParseResult[T, Elem]) extends Parserable[Elem, T] {
    def map [U] (f: T => U): Parserable[Elem, U] = Parser { in => parse(in).map(f) }
    def seq [U] (f: => Parserable[Elem, U]): Parserable[Elem, ~[T, U]] = Parser { in => parse(in).seq(f) }
  }

  object Parser {
    def apply[T] (f: Reader[Elem] => ParseResult[T, Elem]): Parserable[Elem, T] = new Parser(f)
  }
}

/** Trait of parser
  * @tparam T Paring result
  * @tparam E Paring result
  */
trait Parserable [E, +T] {
  def map [U] (f: T => U): Parserable[E, U]
  def seq [U] (f: => Parserable[E, U]): Parserable[E, ~[T, U]]
}
