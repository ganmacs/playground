import parsers._

object SampleParser extends Parsers {
  type Elem = Char

  val a = elem('1') ~ elem('2') ~ elem('3') ^^ {
    case a ~ b ~ c => a.toInt + b.toInt + c.toInt
  }

  val b = elem('2') ~ elem('3') ~ elem('4') ^^ (_ => 234)

  val b2 = elem('2') ~ elem('3') ~ elem('4') ~ elem('7') ^^ (_ => 2347)

  val b3 = elem('2') ~ elem('3') ~ elem('5') ~ elem('7') ~ elem('8') ^^ (_ => 23578)

  val b4 = elem('2').? ~ elem('8') ^^ { case a ~ b => a }

  val c = a | b

  val d = b2 | b

  val d2 = b3 | b2

  val e = elem('2') ~> elem('4') ^^ identity

  val f = elem('2') ~ elem('4') ^^^ "Success"

  val g = elem('2').+ ~ elem('4') ^^ { case xs ~ x => x :: xs }

  val g2 = elem('2').* ~ elem('4') ^^ { case xs ~ x => x :: xs }

  val h = elem('x').+(elem(','))  ^^ { case x => x }

  val h2 = elem('x').*(elem(','))  ^^ { case x => x }

  val nonZero = elem("non zero", { n => n >= '1' && n <= '9' }) ^^ { _-'0' }

  val i = elem("number", { n => n >= '0' && n <= '9' }) ~ elem('e') ^^ { case n ~ x => x + n }

  val i2 = elem("WhiteSpace", Character.isWhitespace) ~> elem('e') ^^ { case x => x }
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
