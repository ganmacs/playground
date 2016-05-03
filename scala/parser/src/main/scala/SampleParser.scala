import parsers._

object SampleParser extends Parsers {
  type Elem = Char

  val a = elem('1') ~ elem('2') ~ elem('3') ^^ {
    case a ~ b ~ c => a.toInt + b.toInt + c.toInt
  }
}

abstract class Result[+T] {
  def map[U](f: T => U): Result[U]
  def flatMap[U](f: T => Result[U]): Result[U]
}

object Result {
  def apply[T](x: T): Result[T] = if (x == null) Err("null") else Suc(x)
}

case class Suc[+T](x: T) extends Result[T] {
  def map[U](f: T => U): Suc[U] =  Suc(f(x))
  def flatMap[U](f: T => Result[U]): Result[U] = f(x)
}

case class Err(x: String) extends Result[Nothing] {
  def map[U](f: Nothing => U) = Err(x)
  def flatMap[U](f: Nothing => Result[U]) = Err(x)
}
