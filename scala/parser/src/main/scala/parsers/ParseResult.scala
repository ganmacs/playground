package parsers

 /**
   * @paramt T parsing result type
   * @paramt E input type
   */
trait ParseResult[+T, E] {
  def map[U](f: T => U): ParseResult[U, E]
}

case class Success[+T, E](result: T) extends ParseResult[T, E] {
  def map[U](f: T => U): ParseResult[U, E] = Success(f(result))
}

case class ~[+A, +B] (first: A, second: B)
