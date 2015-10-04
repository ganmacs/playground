case class Op(v: String) {
  override def toString() = v
}

abstract class Expr

case class IdLit(v: String) extends Expr {
  override def toString() = v
}

case class IntLit(v: Int) extends Expr {
  override def toString() = v toString()
}

case class DoubleLit(v: Double) extends Expr {
  override def toString() = v toString()
}

case class BinExpr(lterm: Expr, op: Op, rterm: Expr) extends Expr {
  override def toString() = s"""($op $lterm $rterm)"""
}

case class Let(id: IdLit, value: Expr, body: Expr) extends Expr {
  override def toString() = s"(let (($id $value)) $body)"
}
