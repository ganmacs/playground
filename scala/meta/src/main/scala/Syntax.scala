sealed trait Expr

case class Op(v: String) extends Expr{
  override def toString() = v
}

case class IdLit(v: String) extends Expr {
  override def toString() = v
}

case class IntLit(v: Int) extends Expr {
  override def toString() = v.toString
}

case class DoubleLit(v: Double) extends Expr {
  override def toString() = v.toString
}

case class BinExpr(lterm: Expr, op: Op, rterm: Expr) extends Expr {
  override def toString() = s"""($op $lterm $rterm)"""
}

case class Let(id: IdLit, value: Expr, body: Expr) extends Expr {
  override def toString() = s"(let (($id $value)) $body)"
}

case class ExprList(v: List[Expr]) extends Expr {
  override def toString() = v.mkString(" ")
}

case class Semantics(v: String) extends Expr {
  override def toString() = v
}
case class NoTerm(v: String) extends Expr {
  override def toString() = v
}

case class Syntax(val lterm: Expr, val op: Op, val rterm: Expr) extends Expr {
  override def toString() = s"""($op $lterm $rterm)"""
}

case class NSyntax(val name: NoTerm, syntax: Syntax) extends Expr

case class Rule(nsyntax: NSyntax, semantics: Semantics, body: Expr) extends Expr
case class RuleW(nsyntax: NSyntax, semantics: Semantics) extends Expr
