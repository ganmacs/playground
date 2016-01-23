package tecs.compiler

sealed trait Syntax

case class S_class(className: S_ident, classVarDec: Option[List[S_classVarDec]], subroutineDec: Option[List[S_subroutineDec]]) extends Syntax
case class S_classVarDec(prefix: S_keyword, t: S_type, varNames: S_varNameList) extends Syntax
case class S_subroutineDec(l: List[Syntax]) extends Syntax
case class S_statements(vname: Option[List[S_statement]]) extends Syntax
case class S_statement(l: Syntax) extends Syntax
case class S_parameterList(l: List[(S_type, S_ident)]) extends Syntax
case class S_varNameList(l: List[S_ident]) extends Syntax
case class S_letStatement(vname: S_ident, e1: Option[S_expression], e2: S_expression) extends Syntax
case class S_if(cond: S_expression, tcond: S_statements, fcond: Option[S_statements]) extends Syntax
case class S_while(cond: S_expression, body: S_statements) extends Syntax
case class S_do(v: S_subroutineCall) extends Syntax
case class S_return(v: Option[S_expression]) extends Syntax
case class S_expression(l: S_term, r: Option[List[S_rightTerm]]) extends Syntax
case class S_expressionList(l: Option[List[S_expression]]) extends Syntax
case class S_type(l: String) extends Syntax
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
