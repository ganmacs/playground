object Evaluator {
  val vm = new Evaluator

  def eval(e: Expr) = vm.eval(e, Env.empty[Value])
}

class Evaluator {
  def eval(e: Expr, env: Env[Value]): Value = e match {
    case IntLit(v) => IntValue(v)
    case DoubleLit(v) => DoubleValue(v)
    case IdLit(v) => env.get(v) match {
      case Some(v@IntValue(_)) => v
      case Some(v@DoubleValue(_)) => v
      case Some(v) => v
      case None => throw new RuntimeException(s"unknow variable $v")
    }
    case BinExpr(l, op, r) => (eval(l, env), op, eval(r, env)) match {
      case (IntValue(x), Op("+"), IntValue(y)) => IntValue(x + y)
      case (IntValue(x), Op("-"), IntValue(y)) => IntValue(x - y)
      case (IntValue(x), Op("*"), IntValue(y)) => IntValue(x * y)
      case (IntValue(x), Op("/"), IntValue(y)) => IntValue(x / y)
      case (DoubleValue(x), Op("+"), DoubleValue(y)) => DoubleValue(x + y)
      case (DoubleValue(x), Op("-"), DoubleValue(y)) => DoubleValue(x - y)
      case (DoubleValue(x), Op("*"), DoubleValue(y)) => DoubleValue(x * y)
      case (DoubleValue(x), Op("/"), DoubleValue(y)) => DoubleValue(x / y)
    }
    case Let(IdLit(id), value, r) => {
      val newEnv = Env.build[Value](env, (id, eval(value, env)))
      eval(r, newEnv)
    }
  }
}
