trait Tokens {
  val INT = """(0|[1-9][0-9]*)""".r
  val DOUBLE =  """(0|[1-9][0-9]*)\.[0-9]+""".r
  val ID = """[a-z][a-zA-Z0-9]*""".r
  val SOURCE = """\{([^}]*)\}""".r

  val EXPRTERM = "$EXPR"
  val TERMTERM = "$TERM"
  val FACTTERM = "$FACT"
  val IDTERM = "$ID"
  val INTTERM = "$INT"

  val CUSTOMOP = """[^=\{\}\$\s]+""".r

  val RULE = "rule"

  val LPAREN = "("
  val RPAREN = ")"
  val EQ = "="
  val LP = "{"
  val RP = "}"
  val LET = "let"
  val IN = "in"
  val ADD = "+"
  val SUB = "-"
  val MUL = "*"
  val DIV = "/"
}
