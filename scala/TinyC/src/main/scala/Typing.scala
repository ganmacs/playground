case object Typing {
  val typing = new Typing
  def check(e: Expr) = typing.check(e, Env.empty[Type])
}

class Typing{
  private def check(e: Expr, env: Env[Type]): Type = e match {
    case IntLit(v) => IntType
    case DoubleLit(v) => DoubleType
    case IdLit(v) => env.get(v) match {
      case Some(x) => x
      case None => throw new Exception(s"unknown variable: $v")
    }
    case BinExpr(l, op, r) => (check(l, env), check(r, env)) match {
      case (IntType, IntType) => IntType
      case (DoubleType, DoubleType) => DoubleType
      case (x, y) => throw new Exception(s"Unmatch type: $x and $y")
    }
    case Let(IdLit(id), v, body) => {
      val newTenv = Env.build[Type](env, (id, check(v, env)))
      check(body, newTenv)
    }
  }
}
