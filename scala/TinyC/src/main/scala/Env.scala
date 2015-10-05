object Env {
  def empty[T] = new Env[T]
  def build[T](parent: Env[T], t: Tuple2[String, T]) = new Env[T](Some(parent), Map(t._1 ->  t._2))
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
