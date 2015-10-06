object Evaluator {
  def eval(e: Expr, env: Env[Value]) = e match {
    case Rule(nsyntax, semantics, body) => body match {
      case BinExpr(IntLit(l), Op("+"), IntLit(r)) => IntValue(l + r)
      case BinExpr(IntLit(l), Op("-"), IntLit(r)) => IntValue(l - r)
      case BinExpr(IntLit(l), Op("*"), IntLit(r)) => IntValue(l * r)
      case BinExpr(IntLit(l), Op("/"), IntLit(r)) => IntValue(l / r)
      case BinExpr(IntLit(l), Op(x), IntLit(r)) => IntValue(l / r)
    }
  }
}
