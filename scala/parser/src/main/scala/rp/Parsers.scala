package rp

trait Parsers[E] {
}

trait Parser [E, +T] {
  private[rp] def apply(in: Reader[E]): Result[E, T]
}
