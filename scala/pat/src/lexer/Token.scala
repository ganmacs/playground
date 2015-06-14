package lexer

case class Token(typ: Int, text: String) {
  override def toString = "< " + typeName + ", " + text + " >"
  private def typeName = ListLexer.tokenNames(typ)
}
