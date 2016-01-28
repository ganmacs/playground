package tecs.compiler

sealed trait Syntax
case class S_class(className: S_ident, classVarDec: Option[Seq[S_classVarDec]], subroutineDec: Option[Seq[S_subroutineDec]]) extends Syntax
case class S_classVarDec(prefix: S_keyword, t: S_type, varNames: S_varNameList) extends Syntax
case class S_subroutineDec(p: S_keyword,  typ: S_type, name: S_ident, plist: S_parameterList, body: S_subroutineBody) extends Syntax
case class S_subroutineBody(dec: Option[Seq[S_varDec]], stat: S_statements) extends Syntax
case class S_statements(vname: Option[Seq[S_statement]]) extends Syntax
case class S_statement(l: Syntax) extends Syntax
case class S_parameterList(l: Option[Seq[(S_type, S_ident)]]) extends Syntax {
  def size: Int = l.map(_.size).getOrElse(0)
}
case class S_varNameList(l: Seq[S_ident]) extends Syntax {
  def prepend(o: S_ident): S_varNameList = S_varNameList(o +: l)
}
case class S_letStatement(vname: S_ident, e1: Option[S_expression], e2: S_expression) extends Syntax
case class S_if(cond: S_expression, tcond: S_statements, fcond: Option[S_statements]) extends Syntax
case class S_while(cond: S_expression, body: S_statements) extends Syntax
case class S_do(v: S_subroutineCall) extends Syntax
case class S_return(v: Option[S_expression]) extends Syntax
case class S_accessAry(vname: S_ident, e: S_expression) extends Syntax
case class S_expression(l: S_term, r: Option[Seq[S_rightTerm]]) extends Syntax
case class S_expressionList(l: Option[Seq[S_expression]]) extends Syntax {
  def prepend(o: S_expression): S_expressionList = S_expressionList { l map (o +: _) }
  def size: Int = l.map(_.size).getOrElse(0)
}
case class S_type(l: Syntax) extends Syntax
case class S_varDec(typ: S_type, varList: S_varNameList) extends Syntax
case class S_subroutineCall(name: S_ident, reciever: Option[S_ident], elist: S_expressionList) extends Syntax
case class S_keyword(keyword: String) extends Syntax
case class S_symbol(keyword: String) extends Syntax
case class S_ident(keyword: String) extends Syntax
case class S_intConst(keyword: String) extends Syntax
case class S_stringConst(keyword: String) extends Syntax
case class S_unaryOp(v: String) extends Syntax
case class S_term(v: Syntax) extends Syntax
case class S_rightTerm(op: S_op, v: S_term) extends Syntax
case class S_termWithUOp(u: S_unaryOp, t: S_term) extends Syntax
case class S_op(v: String) extends Syntax
case class S_keywordConst(v: String) extends Syntax
