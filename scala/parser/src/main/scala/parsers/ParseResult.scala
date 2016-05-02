package parsers

import input.Reader

/**
  * @tparam T parsing result type
  * @tparam E input type
  */
sealed trait ParseResult[+T, E] {
  def next: Reader[E]
  def map[U](f: T => U): ParseResult[U, E]
  // def seq
}

case class Success[+T, E](result: T, next: Reader[E]) extends ParseResult[T, E] {
  def map[U](f: T => U): ParseResult[U, E] = Success(f(result), next)
}

sealed abstract class NoSuccess[E](msg: String, next: Reader[E]) extends ParseResult[Nothing, E] {
  def map[U](f: Nothing => U): NoSuccess[E] = this
}

case class Failure[E](msg: String, next: Reader[E]) extends NoSuccess[E](msg, next) {
}

case class Error[E](msg: String, next: Reader[E]) extends NoSuccess[E](msg, next) {
}

case class ~[+A, +B] (first: A, second: B)
