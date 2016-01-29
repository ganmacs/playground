package tecs.compiler

class VMConverter extends Converter {
  def run(s: Syntax): Seq[String] = toVM(s, "")

  def toVM(s: Syntax, className: String): Seq[String] = s match {
    case S_class(S_ident(className), varDecs, subroutines) => {
      val decs = varDecs.map(_.flatMap { e => toVM(e, className) }).getOrElse(List(""))
      val srs = subroutines.map(_.flatMap { e => toVM(e, className) }).getOrElse(List(""))
      decs ++ srs
    }
    case S_classVarDec(p, t, vnames) => {
      val v = toVM(vnames, className)
      v
    }
    case S_subroutineDec(S_keyword(k), t, S_ident(n), plist, body) => {
      val nn = s"function ${className}.${n} ${body.localVarSize}"
      val b = toVM(body, className)
      List(nn) ++ b
    }
    case S_varNameList(l) => l.flatMap(toVM(_, className))
    case S_subroutineBody(decs, stats) => {
      val d = decs.map(_.flatMap { e => toVM(e, className) }).getOrElse(List(""))
      d ++ toVM(stats, className)
    }
    case S_varDec(typ, vars) => toVM(vars, className)
    case S_statements(slist) => slist.map(_.flatMap { e => toVM(e, className) }).getOrElse(List(""))
    case S_statement(syn) => toVM(syn, className)
    case S_letStatement(S_ident(name), e1, e2) => {
      val e11 = e1.map(toVM(_, className)).getOrElse(List(""))
      val e22 = toVM(e2, className)
      e11 ++ e22
    }
    case S_do(sc) => toVM(sc, className)
    case S_if(cond, e1, e2) => {
      val e11 = toVM(cond, className)
      val e22 = toVM(e1, className)
      val e33 = e2.map(toVM(_, className)).getOrElse(List(""))
      e11 ++ e22 ++ e33
    }
    case S_while(cond, body) => {
      val c = toVM(cond, className)
      val b = toVM(body, className)
      c ++ b
    }
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
    case S_termWithUOp(S_unaryOp(o), term) => {
      val t = toVM(term, className)
      val oo = o match {
        case "-" => "not"
        case "~" => "not"
      }
      t ++ List(oo)
    }
    case S_ident(x) => List(x)
    case S_intConst(x) => List(s"push constant ${x}")
    case S_keyword(x) => List(x)
  }
  private def opToOpS(s: String) = s match {
    case "*" => "call Math.multiply 2"
    case "-" => "sub"
    case "+" => "add"
    case "=" => "eq"
    case "<" => "lt"
    case ">" => "gt"
    case "&" => "and"
    case "|" => "or"
  }
}
