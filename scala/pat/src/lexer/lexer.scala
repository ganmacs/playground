package lexer

object Lexer {
  val EOF_TYPE = 1
  val EOF = -1.toChar
}

abstract class Lexer(val input: String) {
  var p = 0
  var c = input.charAt(p)

  def consume: Unit = {
    p += 1
    c = if (p >= input.length) Lexer.EOF else input.charAt(p)
  }

  // match
  def check(x: Char) = {
    if (c != x) throw new Exception("expecting " + x + "; found" + c)
    consume
  }
}
