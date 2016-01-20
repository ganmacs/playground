package tecs.compiler

object Token {
  val num = """([1-9][0-9]*|0)""".r
  val str = """(\"[^"\n]*\")""".r
  val iden = """([a-zA-Z_][a-zA-Z0-9_]*)""".r

  def build(s: String): TKN = s match {
    case k@("class" | "constructor" | "function" | "method" |
        "field" | "static" | "var" |  "int" | "char" |
        "boolean" | "void" | "true" | "false" | "null" |
        "this" | "let" | "do" | "if" | "else" | "while" | "return" ) => KEYWORD(k)
    case k@("{" | "}" | "(" | ")" | "[" | "]" | "," | "." | ";" |
        "+" | "-" | "*" | "/" | "&" | "|" | "<" | ">" | "=" | "~") => SYMBOL(k)
    case num(n) => INT_CONST(n)
    case iden(n) => IDENTIFIER(n)
    case str(n) => STRING_CONST(n)
  }
}

sealed trait TKN
case class KEYWORD(keyword: String) extends TKN
case class SYMBOL(keyword: String) extends TKN
case class IDENTIFIER(keyword: String) extends TKN
case class INT_CONST(keyword: String) extends TKN
case class STRING_CONST(keyword: String) extends TKN
