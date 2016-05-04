package parsers

import input.Reader

/**
  * @tparam T parsing result type
  * @tparam E input type
  */
sealed trait ParseResult[+T, E] {
  def next: Reader[E]
  def get: T
  def orElse[U >: T](f: => ParseResult[U, E]): ParseResult[U, E]
  def map[U](f: T => U): ParseResult[U, E]
  def flatMap[U](f: T => ParseResult[U, E]): ParseResult[U, E]
  def flatMapWithNext[U](f: T => Reader[E] => ParseResult[U, E]): ParseResult[U, E]
}

case class Success[+T, E](result: T, next: Reader[E]) extends ParseResult[T, E] {
  def map[U](f: T => U): ParseResult[U, E] = Success(f(result), next)
  def get = result
  def orElse[U >: T](f: => ParseResult[U, E]): ParseResult[U, E] = this
  def flatMap[U](f: T => ParseResult[U, E]): ParseResult[U, E] = f(result)
  def flatMapWithNext[U](f: T => Reader[E] => ParseResult[U, E]): ParseResult[U, E] = f(result)(next)
}

sealed abstract class NoSuccess[E](msg: String, next: Reader[E]) extends ParseResult[Nothing, E] {
  def map[U](f: Nothing => U): NoSuccess[E] = this
  def get = scala.sys.error("No result when parsing failed")
  def flatMap[U](f: Nothing => ParseResult[U, E]): ParseResult[U, E] = this
  def flatMapWithNext[U](f: Nothing => Reader[E] => ParseResult[U, E]): ParseResult[U, E] = this
}

case class Failure[E](msg: String, next: Reader[E]) extends NoSuccess[E](msg, next) {
  def orElse[U >: Nothing](f: => ParseResult[U, E]): ParseResult[U, E] = { val ret = f
    f match {
      case Success(_, _) => ret
      case x: NoSuccess[E] => longest(f)
    }
  }

  private def longest[U >: Nothing](ret: ParseResult[U, E]): ParseResult[U, E] = {
    if (ret.next.pos < this.next.pos) this else ret
  }
}

case class Error[E](msg: String, next: Reader[E]) extends NoSuccess[E](msg, next) {
  def orElse[U >: Nothing](f: => ParseResult[U, E]): ParseResult[U, E] = this
}

/** A container that contains seq result
  * @tparams A type of lhs
  * @tparams B type of rhs
  **/
case class ~[+A, +B] (first: A, second: B)
