package tecs.compiler

class VMConverter extends Converter {
  private val counter = new {
    private var i = -1
    def inc = { this.i += 1; this.i }
  }

  def run(s: Syntax): Seq[String] = toVM(s, "", SymbolTable(None))

  def toVM(s: Syntax, className: String, st: SymbolTable): Seq[String] = s match {
    case S_class(S_ident(className), varDecs, subroutines) => {
      val decs = varDecs.map(_.flatMap { e => toVM(e, className,st) }).getOrElse(Seq(""))
      val srs = subroutines.map(_.flatMap { e => toVM(e, className,st) }).getOrElse(Seq(""))
      decs ++ srs
    }
    case S_classVarDec(key, t, vnames) => {
      val typ = getTypeName(t)
      toVM(vnames, className, st).foreach { n => st.defineIfNotExist(n, typ, keywordToKind(key)) }
      List("")
    }
    case S_subroutineDec(S_keyword(k), t, S_ident(n), S_parameterList(plist), body) => {
      val nst = st.newSymbolTable
      plist.foreach (_.foreach { case (typ, S_ident(s)) => nst.defineIfNotExist(s, getTypeName(typ), ARG) })
      List(VMWriter.func(s"${className}.${n}", body.localVarSize)) ++ toVM(body, className, nst)
    }
    case S_varNameList(l) => l.map { case S_ident(i) => i }
    case S_subroutineBody(decs, stats) => {
      decs.map(_.flatMap { e => toVM(e, className, st) }).getOrElse(List("")) ++ toVM(stats, className,st)
    }
    case S_varDec(t, vars) => {
      val vnl = toVM(vars, className, st)
      val typ = getTypeName(t)
      vnl.foreach { n => st.defineIfNotExist(n, typ, VAR) }
      List("")
    }
    case S_statements(slist) => slist.map(_.flatMap { e => toVM(e, className, st) }).getOrElse(List(""))
    case S_statement(syn) => toVM(syn, className, st)
    case S_letStatement(S_ident(name), e1, e2) => {
      val s = st.getOrDie(name)
      val e11 = e1.map(toVM(_, className, st)).getOrElse(List(""))
      val e22 = toVM(e2, className, st)
      e11 ++ e22 :+ VMWriter.pop(s.kind, s.i)
    }
    case S_do(sc) => toVM(sc, className, st)
    case S_if(cond, e1, e2) => {
      val c = toVM(cond, className, st) :+ VMWriter.uop("~")
      val e11 = toVM(e1, className, st)
      val e22 = e2.map(toVM(_, className, st)).getOrElse(List(""))
      VMWriter.ifexp(c, e11, e22, counter.inc)
    }
    case S_while(cond, body) => {
      val c = toVM(cond, className, st)
      val b =  toVM(body, className, st)
      VMWriter.whielexp(c, b, counter.inc)
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
      case "false" => Seq(VMWriter.push("constant", "1"), VMWriter.uop("~"))
      case x => Seq(x)
    }
  }

  private def keywordToKind(p: S_keyword) = p match {
    case S_keyword("static") => STATIC
    case S_keyword("field") => FIELD
    case S_keyword("var") => VAR
    case s => throw new Exception(s"Not found typ: $s")
  }

  private def getTypeName(x : S_type) = x match {
    case S_type(s) => s match {
      case S_keyword(x) => x
      case S_ident(x) => x
      case t => throw new Exception(s"unknow type: $t")
    }
  }
}
