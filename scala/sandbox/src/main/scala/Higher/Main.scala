object Higher {
  def decorate[T](x: T)(implicit deco: Decorating[T]) = deco(x)

  trait Decorating[T] {
    def apply(x: T): String
  }

  implicit val DecoratingString = new Decorating[String] {
    def apply(x: String) = s"$x at DecoratingString"
  }

  implicit val DecoratingInt = new Decorating[Int] {
    def apply(x: Int) = s"$x at DecoratingString"
  }

  // implicit object OptionString extends Decorating[Option[String]] {
  //   def apply(x: Option[String]) = x.fold("") ("at OptionOptionString" + _: String)
  // }

  implicit def DecoratingOption[T](implicit d: Decorating[T]) = new Decorating[Option[T]] {
    def apply(x: Option[T]) = x.fold("")(d(_))
  }


  trait Sendable[T] {
    def send(x: T): Boolean
  }

  def send[T](x: T)(implicit ins : Sendable[T]) = ins.send(x)

  implicit val SendString = new Sendable[String] {
    def send(x: String): Boolean = {
      println(x)
      true
    }
  }

  def main(args: Array[String]) {
    send("df")
    println(decorate(10))
    println(decorate(Option("sdf")))
    println(decorate("sadf"))
  }
}
