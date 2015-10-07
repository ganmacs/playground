object Evaluator {
  def eval(e: Expr, env: Env[RuleW]): Value = e match {
    case IntLit(x) => IntValue(x)
    case BinExpr(l, Op("+"), r) => (eval(l, env), eval(r, env)) match {
      case (IntValue(x), IntValue(y)) => IntValue(x + y)
    }
    case BinExpr(l, Op("-"), r) => (eval(l, env), eval(r, env)) match {
      case (IntValue(x), IntValue(y)) => IntValue(x - y)
    }
    case BinExpr(l, Op("*"), r) => (eval(l, env), eval(r, env)) match {
      case (IntValue(x), IntValue(y)) => IntValue(x * y)
    }
    case BinExpr(l, Op("/"), r) => (eval(l, env), eval(r, env)) match {
      case (IntValue(x), IntValue(y)) => IntValue(x /  y)
    }
    case b@BinExpr(l, Op(x), r) => (eval(l, env), eval(r, env)) match {
      case (IntValue(x), IntValue(y)) =>
        env.get(b.toString) match {
          case Some(RuleW(nsyntax, semantics)) => {
            val syntax = nsyntax.syntax
            var s = semantics.v
            s = s.replace("$1", x.toString())
            s = s.replace("$2", y.toString())
            Parser.parse(s, env) match {
              case Right((x, e)) => eval(x, e)
              case Left(x) => throw new Exception("errro at parse")
            }
          }
        }
    }
  }
}
