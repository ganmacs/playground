object Evaluator {
  val emptyEnv = Map.empty[String, Type]
  val vm = new Evaluator

  def eval(e: Expr) = vm.eval(e, emptyEnv)
}

class Evaluator {
  def eval(e: Expr, env: Map[String, Type]): Type = e match {
    case IntLit(v) => IntT(v)
    case DoubleLit(v) => DoubleT(v)
    case IdLit(v) => env.get(v) match {
      case Some(v@IntT(_)) => v
      case Some(v@DoubleT(_)) => v
      case None => throw new RuntimeException(s"unknow variable $v")
    }
    case BinExpr(l, op, r) => (eval(l, env), op, eval(r, env)) match {
      // TODO type infer
      case (IntT(x), Op("+"), IntT(y)) => IntT(x + y)
      case (IntT(x), Op("-"), IntT(y)) => IntT(x - y)
      case (IntT(x), Op("*"), IntT(y)) => IntT(x * y)
      case (IntT(x), Op("/"), IntT(y)) => IntT(x / y)
      case (DoubleT(x), Op("+"), DoubleT(y)) => DoubleT(x + y)
      case (DoubleT(x), Op("-"), DoubleT(y)) => DoubleT(x - y)
      case (DoubleT(x), Op("*"), DoubleT(y)) => DoubleT(x * y)
      case (DoubleT(x), Op("/"), DoubleT(y)) => DoubleT(x / y)
    }
    case Let(IdLit(id), value, r) => {
      val env2 = Map[String, Type](id -> eval(value, env)) ++ env
      eval(r, env2)
    }
  }
}
