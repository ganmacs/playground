package tecs.compiler

class JackTokenizer(input: String) {
  private var i = 0
  private val STR = """([a-zA-Z0-9]+)(.+)""".r
  private val WS = """\s+(.+)""".r
  private val KW = """(;|\{|\}|\(|\)|\[|\]|=|\+|\-|/|\*|,|<|>|&|\||~|\.)(.+)""".r
  private val S = """(\"[^"\n]*\")(.+)""".r
  val tokens = scan(input)

  def hasMoreTokens: Boolean = {
    return tokens.size == i
  }

  def advance = if (hasMoreTokens) { i += 1 }

  def tokenType(): TKN = tokens(i)

  def keyword: String = tokens(i) match {
    case KEYWORD(s)      => s
    case SYMBOL(s)       => s
    case IDENTIFIER(s)   => s
    case INT_CONST(s)    => s
    case STRING_CONST(s) => s
  }

  def symbol: String = tokens(i) match {
    case SYMBOL(s)       => s
    case _ => throw new Exception("only symbol")
  }

  def identifier: String = tokens(i) match {
    case IDENTIFIER(s) => s
    case _ => throw new Exception("only identifier")
  }

  def intVal: String = tokens(i) match {
    case INT_CONST(s) => s
    case _ => throw new Exception("only int const")
  }

  def stringVal: String = tokens(i) match {
    case STRING_CONST(s) => s
    case _ => throw new Exception("only string const")
  }

  private def scan(str: String): List[TKN] = str match {
    case STR(s, rest) => Token.build(s) :: scan(rest)
    case WS(rest) => scan(rest)
    case KW(s, rest) => Token.build(s) :: scan(rest)
    case S(s, rest) => Token.build(s) :: scan(rest)
    case s => List(Token.build(s))
  }
}
