package lexer

object ListLexer {
  val NAME = 2
  val COMMA = 3
  val LBRACK = 4
  val RBRACK = 5
  val tokenNames = List("n/a", "<EOF>", "NAME", "COMMA", "LBRACK", "RBRACK")
}

class ListLexer(input: String) extends Lexer(input) {
  def getTokenName(x: Int) = ListLexer.tokenNames(x)

  def isLETTER = c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'

  def name = {
    var str = ""
    while ( isLETTER ) {
      str = str + c
      consume
    }
    Token(ListLexer.NAME, str)
  }

  def ws = while (' ' == c || '\t' == c || '\n' == c || '\r' == c) consume

  def nextToken: Token = {
    while ( c != Lexer.EOF ) {
      c match {
        case '\t' => ws
        case '\n' => ws
        case '\r' => ws
        case ' ' => ws
        case ',' => {
          consume
          return Token(ListLexer.COMMA, ",")
        }
        case '[' => {
          consume
          return Token(ListLexer.LBRACK, "[")
        }
        case ']' => {
          consume
          return Token(ListLexer.RBRACK, "]")
        }
        case _ => {
          if (isLETTER)
            return name
          else
            throw new Error("invalid charactor" + c)
        }
      }
    }
    Token(Lexer.EOF_TYPE, "<EOF>")
  }
}
