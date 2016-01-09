package asm

import scala.util.parsing.combinator.RegexParsers
/*
 op = aop | cor
 aop = "@" (INT | LABLE)
 cop = (LABEL "=")? comp (";" LABEL)?
 OPS = "+" | "-" | "|" | "&"
 ARG = "0" | "1" | "-1" | (("-" | "!")? | LABEL OPS) LABEL
 LABEL = [_:.$A-Z][_:.$A-Z0-9]*
 INT = (0|[1-9][0-9]*)
*/

case class Parser() extends RegexParsers {
  private val table = SymbolTable()

  private val INT = """(0|[1-9][0-9]*)""".r
  private val LABEL = """[_:.$a-zA-Z][_:.$a-zA-Z0-9]*""".r
  private val BUILTINL = """([a-zA-Z]*|[01])""".r
  private val PREFIX = """[!\-]""".r
  private val OPS = """[\+\-&|]""".r

  private val address = "@" ~ INT ^^ { case _ ~ r => AOperator(r) }
  private val variable = "@" ~ LABEL ^^ { case _ ~ r =>
    val v = table.addSymbol(r)
    AOperator(v)
  }

  private val pr = PREFIX.? ~ BUILTINL ^^ { case l ~ r => l.getOrElse("") + r }
  private val exp = BUILTINL ~ OPS ~  BUILTINL ^^ { case l ~ m ~ r => l + m + r }
  private val comp = "0" | "1" | "-1" | exp | pr
  private val dest = BUILTINL ~ "=" ^^ { case l ~ _ => l }
  private val jump = ";" ~ BUILTINL ^^ { case _ ~ r => r }

  private val aOperator = address | variable
  private val cOperator = dest.? ~ comp ~ jump.? ^^ { case d ~ c ~ j => COperator(d, c, j) }
  private val expr = aOperator | cOperator

  def parse(in: String): Either[String, Operator] = {
    parseAll(expr, in) match {
      case Success(d, next) => Right(d)
      case failure: NoSuccess => Left(s"failure")
    }
  }
}
