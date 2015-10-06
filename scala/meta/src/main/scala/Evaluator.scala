object Evaluator {
  def eval(e: Expr, env: Env[RuleW]) = e match {
    case BinExpr(IntLit(l), Op("+"), IntLit(r)) => IntValue(l + r)
    case BinExpr(IntLit(l), Op("-"), IntLit(r)) => IntValue(l - r)
    case BinExpr(IntLit(l), Op("*"), IntLit(r)) => IntValue(l * r)
    case BinExpr(IntLit(l), Op("/"), IntLit(r)) => IntValue(l / r)
    case b@BinExpr(IntLit(l), Op(x), IntLit(r)) => {
      env.get(b.toString) match { // require syntax?
        case Some(RuleW(nsyntax, sematics)) => {
          val syntax = nsyntax.syntax
          sematics
        }
        case None => new Exception("unkown")
      }
    }
  }
}
