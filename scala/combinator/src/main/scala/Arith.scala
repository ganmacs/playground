import util.parsing.combinator.{PackratParsers, RegexParsers}

object Arith {
  def main(args: Array[String]) {
    ArithParser("1 + 2 * (10 + 10)") match {
      case Left(errorMsg) => println(errorMsg)
      case Right(v) => println(ArithEvaluator.eval(v))
    }
  }

  abstract class Expr
  case class IntLit(v: Int) extends Expr {
    override def toString() = v toString()
  }

  case class BinExpr(lterm: Expr, op: Op, rterm: Expr) extends Expr {
    override def toString() = s"""($op $lterm $rterm)"""
  }

  case class Op(value: String) {
    override def toString() = value
  }

  object ArithEvaluator {
    def eval(e: Expr): Int = e match {
      case BinExpr(l, Op("+"), r) => eval(l) + eval(r)
      case BinExpr(l, Op("-"), r) => eval(l) - eval(r)
      case BinExpr(l, Op("*"), r) => eval(l) * eval(r)
      case BinExpr(l, Op("/"), r) => eval(l) / eval(r)
      case IntLit(v) => v
    }
  }

  object ArithParser extends RegexParsers with PackratParsers {
    private lazy val lParen = "("
    private lazy val rParen = ")"
    private lazy val intToken = """(0|[1-9][0-9]*)""".r
    private lazy val addToken = """\+""".r
    private lazy val subToken = """-""".r
    private lazy val mulToken = """\*""".r
    private lazy val divToken = """/""".r

    private lazy val exprOp = addToken | subToken
    private lazy val termOp = mulToken | divToken
    private lazy val digit = intToken

    private lazy val expr: PackratParser[Expr] = term ~ (exprOp ~ term).* ^^ {
      case l ~ r =>
        val rlst = for ((op ~ fact) <- r) yield (Op(op), fact)
        makeBinExpr(l, rlst)
    }

    private lazy val term: PackratParser[Expr] = fact ~ (termOp ~ fact).* ^^ {
      case l ~ r =>
        val rlst = for ((op ~ fact) <- r) yield (Op(op), fact)
        makeBinExpr(l, rlst)
    }

    private lazy val fact =
      digit ^^ { case e => IntLit(e.toInt) } | lParen ~> expr <~ rParen

    private def makeBinExpr(lterm: Expr , rterms: List[(Op, Expr)]) = {
      (lterm /: rterms) ((a, rt) =>
        rt match { case (op, e) => BinExpr(a, op, e) }
      )
    }

    def apply(in: String): Either[String, Expr] = parseAll(expr, in) match {
      case Success(d, next) => Right(d)
      case NoSuccess(errorMsg, next) =>
        Left(s"$errorMsg : in ${next.pos.line} at column ${next.pos.column}")
    }
  }
}
