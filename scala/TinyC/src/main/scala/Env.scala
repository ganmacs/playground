object Env {
  def empty() = new Env[Value]
  def emptyType() = new Env[Type]
  def build(parent: Env[Value], t: Tuple2[String, Value]) = new Env[Value](Some(parent), Map(t._1 ->  t._2))
  def buildT(parent: Env[Type], t: Tuple2[String, Type]) = new Env[Type](Some(parent), Map(t._1 ->  t._2))
}

case class Env[T](
  var parent: Option[Env[T]] = None,
  var e: Map[String, T] = Map.empty[String, T]
) {
  def put(k: String, v: T) = { e = Map(k -> v) ++ e }
  def update(k: String, v: T) = e.updated(k, v)
  def getLocal(k: String) = e.get(k)
  def get(k: String): Option[T] = e.get(k) match {
    case None => parent match {
      case None => None
      case Some(x) => x.get(k)
    }
    case x => x
  }
}
