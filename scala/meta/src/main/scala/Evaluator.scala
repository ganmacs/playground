object Evaluator {
  def eval(e: Expr, env: Env[Semantics]) = e match {
    case BinExpr(IntLit(l), Op("+"), IntLit(r)) => IntValue(l + r)
    case BinExpr(IntLit(l), Op("-"), IntLit(r)) => IntValue(l - r)
    case BinExpr(IntLit(l), Op("*"), IntLit(r)) => IntValue(l * r)
    case BinExpr(IntLit(l), Op("/"), IntLit(r)) => IntValue(l / r)

    case el@ExprList(_) => {
      env.get(el.toString) match {
        case Some(x) =>
          x
        case None => new Exception("unkown")
      }
    }
  }
}
