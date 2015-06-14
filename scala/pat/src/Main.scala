import lexer._

object Main {
  def main(args: Array[String]) {
    val lexer = new ListLexer(args(0))
    var t = lexer.nextToken

    while (t.typ != Lexer.EOF_TYPE ) {
      println(t)
      t = lexer.nextToken
    }
  }
}
