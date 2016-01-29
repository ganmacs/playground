package tecs.compiler

class VMConverter extends Converter {
  def run(s: Syntax): Seq[String] = toVM(s, "", SymbolTable(None))

  def toVM(s: Syntax, className: String, st: SymbolTable): Seq[String] = s match {
    case S_class(S_ident(className), varDecs, subroutines) => {
      val decs = varDecs.map(_.flatMap { e => toVM(e, className,st) }).getOrElse(Seq(""))
      val srs = subroutines.map(_.flatMap { e => toVM(e, className,st) }).getOrElse(Seq(""))
      decs ++ srs
    }
    case S_classVarDec(S_keyword(p), t, vnames) => {
      val typ = toVM(t, className, st)(0)
      st.defineIfNotExist(p, typ, p match {
        case "static" => STATIC
        case "field" => FIELD
        case "var" => VAR
        case s => throw new Exception(s"Not found typ: $s")
      })
      toVM(vnames, className,st)
    }
    case S_subroutineDec(S_keyword(k), t, S_ident(n), S_parameterList(plist), body) => {
      val nst = st.newSymbolTable
      plist.foreach (_.foreach { case (t, S_ident(s)) => nst.defineIfNotExist(s, toVM(t, className, nst)(0), ARG) })
      val nn = s"function ${className}.${n} ${body.localVarSize}"
      val b = toVM(body, className, nst)
      List(nn) ++ b
    }
    case S_varNameList(l) => l.map { case S_ident(i) => i }
    case S_subroutineBody(decs, stats) => {
      val d = decs.map(_.flatMap { e => toVM(e, className,st) }).getOrElse(List(""))
      d ++ toVM(stats, className,st)
    }
    case S_varDec(t, vars) => {
      val vnl = toVM(vars, className, st)
      val typ = toVM(t, className, st)(0)
      vnl.foreach { n => st.defineIfNotExist(n, typ, VAR) }
      List("")
    }
    case S_statements(slist) => slist.map(_.flatMap { e => toVM(e, className,st) }).getOrElse(List(""))
    case S_statement(syn) => toVM(syn, className,st)
    case S_letStatement(S_ident(name), e1, e2) => {
      val s = st.getOrDie(name)
      val e11 = e1.map(toVM(_, className, st)).getOrElse(List(""))
      val e22 = toVM(e2, className, st)
      e11 ++ e22 :+ VMWriter.pop(s.kind, s.i)
    }
    case S_do(sc) => toVM(sc, className,st)
    case S_if(cond, e1, e2) => {
      val e11 = toVM(cond, className,st)
      val e22 = toVM(e1, className,st)
      val e33 = e2.map(toVM(_, className,st)).getOrElse(List(""))
      val s = e11 ++ Seq(VMWriter.uop("~"), VMWriter.ifg("if1")) ++ e22
      val ss = s ++ Seq(VMWriter.goto("if2"), VMWriter.label("if1")) ++ e33
      ss :+ VMWriter.label("if2")
    }
    case S_while(cond, body) => {
      val c = VMWriter.label("while1") +: toVM(cond, className,st)
      val dd = c ++ Seq(VMWriter.uop("~"), VMWriter.ifg("while2"))
      val l = Seq(VMWriter.goto("while1"), VMWriter.label("while2"))
      dd ++ toVM(body, className,st) ++ l
    }
    case S_return(v) => v.map(VMWriter.ret +: toVM(_, className, st)).getOrElse(List("return"))
    case S_subroutineCall(S_ident(n), recv, elist) => {
      val r = recv.collect { case S_ident(s) => s }.getOrElse(className)
      toVM(elist, className, st) :+ VMWriter.call(s"${r}.${n}", elist.size)
    }
    case S_expressionList(l) => l.map(_.flatMap { e => toVM(e, className,st) }).getOrElse(List(""))
    case S_expression(l, r) => {
      val ll = toVM(l, className,st)
      val rr = r.map(_.flatMap { e => toVM(e, className,st) }).getOrElse(List(""))
      ll ++ rr
    }
    case S_term(s) => toVM(s, className,st)
    case S_rightTerm(S_op(op), t) => {
      val tt = toVM(t, className,st)
      tt ++ Seq(VMWriter.arithmetic(op))
    }
    case S_termWithUOp(S_unaryOp(o), term) => {
      val t = toVM(term, className,st)
      t ++ Seq(VMWriter.uop(o))
    }
    case S_type(s) => s match {
      case S_keyword(x) => Seq(x)
      case S_ident(x) => Seq(x)
      case t => throw new Exception(s"unknow type: $t")
    }
    case S_ident(x) => {
      val sym = st.getOrDie(x)
      Seq(VMWriter.push(sym.kind, sym.i))
    }
    case S_intConst(x) => Seq(VMWriter.push("constant", x))
    case S_keyword(x) => x match {
      case "true" => Seq(VMWriter.push("constant", "1"))
      case "false" => Seq(VMWriter.push("constant", "0"), VMWriter.uop("~"))
      case x => Seq(x)
    }
  }
}
