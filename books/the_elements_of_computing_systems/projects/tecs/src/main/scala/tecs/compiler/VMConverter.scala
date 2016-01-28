package tecs.compiler

class VMConverter extends Converter {
  def run(s: Syntax): Seq[String] = toVM(s, "")

  def toVM(s: Syntax, className: String): Seq[String] = s match {
    case S_class(S_ident(className), varDecs, subroutines) => {
      val decs = varDecs.map(_.flatMap { e => toVM(e, className) }).getOrElse(List(""))
      val srs = subroutines.map(_.flatMap { e => toVM(e, className) }).getOrElse(List(""))
      decs ++ srs
    }
    case S_subroutineDec(S_keyword(k), S_type(t), S_ident(n), plist, body) => {
      val nn = s"function ${className}.${n} 0"
      val b = toVM(body, className)
      List(nn) ++ b
    }
    case S_subroutineBody(decs, stats) => {
      val d = decs.map(_.flatMap { e => toVM(e, className) }).getOrElse(List(""))
      d ++ toVM(stats, className)
    }
    case S_statements(slist) => slist.map(_.flatMap { e => toVM(e, className) }).getOrElse(List(""))
    case S_statement(syn) => toVM(syn, className)
    case S_do(sc) => toVM(sc, className)
    case S_return(v) => v.map("return " +: toVM(_, className)).getOrElse(List("return"))
    case S_subroutineCall(S_ident(n), recv, elist) => {
      val r = recv.collect { case S_ident(s) => s }.getOrElse(className)
      toVM(elist, className) ++ List(s"call ${r}.${n} ${elist.size}")
    }
    case S_expressionList(l) => l.map(_.flatMap { e => toVM(e, className) }).getOrElse(List(""))
    case S_expression(l, r) => {
      val ll = toVM(l, className)
      val rr = r.map(_.flatMap { e => toVM(e, className) }).getOrElse(List(""))
      ll ++ rr
    }
    case S_term(s) => toVM(s, className)
    case S_rightTerm(S_op(op), t) => {
      val tt = toVM(t, className)
      tt ++ List(opToOpS(op))
    }
    case S_ident(x) => List(x)
    case S_intConst(x) => List(s"push constant ${x}")
  }

  private def opToOpS(s: String) = s match {
    case "*" => "call Math.multiply 2"
    case "-" => "sub"
    case "+" => "add"
  }
}
