package tecs.compiler

sealed trait Syntax

case class S_class(className: S_ident, classVarDec: S_classVarDec, subroutineDec: S_subroutineDec) extends Syntax
case class S_classVarDec(prefix: S_keyword, t: S_type, varNames: List[Syntax]) extends Syntax
case class S_subroutineDec(l: List[Syntax]) extends Syntax
case class S_parameterList(l: List[(S_type, S_ident)]) extends Syntax
case class S_type(l: String) extends Syntax
case class S_keyword(keyword: String) extends Syntax
case class S_symbol(keyword: String) extends Syntax
case class S_ident(keyword: String) extends Syntax
case class S_intConst(keyword: String) extends Syntax
case class S_stringConst(keyword: String) extends Syntax
