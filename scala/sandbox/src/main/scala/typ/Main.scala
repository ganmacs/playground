package typ

object Main {
  implicit def stringToHoge(s: String) = Hoge(s)

  val a = new A {
    def name = "first"
  }

  trait Who[T] {
    def who(x: T): String
  }

  implicit def WhoInt = new Who[Int] {
    def who(x: Int) = "Int"
  }

  implicit def WhoDouble = new Who[Double] {
    def who(x: Double) = "Double"
  }

  implicit def saikou = new Who[String] {
    def who(x: String) = "String " + x
  }

  trait WhoOps[T] {
    def self: T
    implicit def instance: Who[T]

    def whoMethod() = instance.who(self)
  }

  implicit def ToWhoOps[T](v: T)(implicit i: Who[T]) = new WhoOps[T] {
    def self = v;
    implicit def instance: Who[T] = i
  }

  // def sayWho[T](x: T)(implicit instance: Who[T]) = println(instance.who(x))

  def sayWho[T: Who](x: T) = println(implicitly[Who[T]].who(x))


  case class Address(no: Int, street: String, city: String, state: String, zip: String)

  trait LabelMarker[T] {
    def toLabel(value: T): String
  }

  case class AddressLabelMaker() extends LabelMarker[Address] {
    def toLabel(address: Address) = {
      import address._
      "%d %s, %s, %s - %s".format(no, street, city, state, zip)
    }
  }

  // def printLabel[T](t: T)(lm: LabelMarker[T]) = lm.toLabel(t)

  // object LabelMarker {
  implicit object AddressLabelMarker extends LabelMarker[Address] {
    def toLabel(address: Address): String = {
      import address._
      "%d %s, %s, %s - %s".format(no, street, city, state, zip)
    }

  }
  // }

  def printLabel[T: LabelMarker](t: T) = implicitly[LabelMarker[T]].toLabel(t)

  trait FlipFlapper[T] {
    def doFlipFlap(x: T): T
  }

  implicit object IntFlipFlapper extends FlipFlapper[Int] {
    def doFlipFlap(x:Int) = - x
  }

  implicit object StringFlipFlapper extends FlipFlapper[String] {
    def doFlipFlap(x:String) = x.reverse
  }

  implicit object BooleanFlipFlapper extends FlipFlapper[Boolean] {
    def doFlipFlap(x:Boolean) = !x
  }

  def flipFlap[T](x: T)(implicit instance: FlipFlapper[T]) = instance.doFlipFlap(x)

  // def flipFlap[T](x:T, flipFlapper: FlipFlapper[T]) = flipFlapper.doFlipFlap(x)

  // implicit def IntToFlapper(x: Int) = new IntFlipFlapper(x)

  // def flapFlap[T](x: T) = x.doFlipFlap(x)

  // trait Plus[A] {
  //   def plus(a: A): A
  // }

  // def plus[A <: Plus[A]](a: A, a2: A): A = a.plus(a2)

  trait Plus[A] {
    def plus(a1: A, a2: A): A
  }

  implicit val PlusInt =  new Plus[Int] {
    def plus(a1: Int, a2: Int) = a1 + a2
  }

  // def plus[A: Plus](a1: A, a2: A): A = implicitly[Plus[A]].plus(a1, a2)

  // def sum(xs: List[Int]): Int = xs.foldLeft(0) { _ + _ }

  // object IntMonoid {
  //   def mappend(a: Int, b: Int): Int = a + b
  //   def mzero: Int =  0
  // }

  // def sum(xs: List[Int]): Int = xs.foldLeft(IntMonoid.mzero) (IntMonoid.mappend)

  trait Monoid[A] {
    def mappend(a: A, b: A): A
    def mzero: A
  }

  // implicit object IntMonoid extends Monoid[Int] {
  //   def mappend(a: Int, b: Int): Int = a + b
  //   def mzero: Int =  0
  // }

  // def sum(xs: List[Int], m: Monoid[Int]): Int = xs.foldLeft(m.mzero)(m.mappend)
  // def sum[A](xs: List[A])(implicit m: Monoid[A]): A = xs.foldLeft(m.mzero)(m.mappend)

  // def sum[A: Monoid](xs: List[A]): A = {
  //   val m = implicitly[Monoid[A]]
  //   xs.foldLeft(m.mzero)(m.mappend)
  // }

  object Monoid {
    implicit val IntMonoid: Monoid[Int] = new Monoid[Int] {
      def mappend(a: Int, b: Int): Int = a + b
      def mzero: Int = 0
    }

    implicit val StringMonoid: Monoid[String] = new Monoid[String] {
      def mappend(a: String, b: String): String = a + b
      def mzero: String = ""
    }
  }

  val multiMonoid: Monoid[Int] = new Monoid[Int] {
    def mappend(a: Int, b: Int): Int = a * b
    def mzero: Int = 1
  }

  def plus[A: Monoid](a: A, b: A) = implicitly[Monoid[A]].mappend(a, b)

  // object FoldLeftList {
  //   def foldLeft[A, B](xs: List[A], b: B, f: (B, A) => B) = xs.foldLeft(b)(f)
  // }

  // def sum[A: Monoid](xs: List[A]): A = {
  //   val m = implicitly[Monoid[A]]
  //   FoldLeftList.foldLeft(xs, m.mzero, m.mappend)
  // }

  // trait FoldLeft[F[_]] {
  //   def foldLeft[A, B](xs: List[A], b: B, f: (B, A) => B): B
  // }

  trait FoldLeft[F[_]] {
    def foldLeft[A, B](xs: F[A], b: B, f: (B, A) => B): B
  }

  object FoldLeft {
    implicit val FoldLeftList: FoldLeft[List] = new FoldLeft[List] {
      def foldLeft[A, B](xs: List[A], b: B, f: (B, A) => B) = xs.foldLeft(b)(f)
    }
  }

  def sum[M[_]: FoldLeft, A: Monoid](xs: M[A]): A = {
    val m = implicitly[Monoid[A]]
    val fl = implicitly[FoldLeft[M]]
    fl.foldLeft(xs, m.mzero, m.mappend)
  }

  trait A {
    def name: String
  }

  case class Hoge(s: String) {
    def hoge = "fuga"
  }

  def id[T](x: T) = x

  implicit def floatToInt(f: Float): Int = f.toInt

  def logInt(i: Int) = println(i)

  class SuperInt(val i: Int) {
    def double = i * i
  }

  implicit def intToSuper(i: Int): SuperInt = new SuperInt(i)


  trait MonoidOp[A] {
    val F: Monoid[A]
    val value: A
    def |+|(a2: A) = F.mappend(value, a2)
  }

  implicit def toMonoidOp[A: Monoid](a: A): MonoidOp[A] = new MonoidOp[A] {
    val F = implicitly[Monoid[A]]
    val value = a
  }

  def main(args: Array[String]) {
    // println(3 |+| 3)
    // println("a" |+| "d")

    // implicit val intMonoid = IntMonoid
    // sum(List(1, 2, 3, 4), IntMonoid)
    println(sum(List(1, 2, 3, 4)))
    println(sum(List("a", "b", "c")))

    plus(10, 30)

    // plus(1, 2)
    // flipFlap(1)
    // flipFlap(true)
    // flapFlap(1)
    // val a = Address(100, "Monroe Street", "Denver", "CO", "80231")
    // val r = AddressLabelMaker().toLabel(a)
    // println(r)
    // println(printLabel(Address(100, "Monroe Street", "Denver", "CO", "80231")))

    // logInt(0.2f)
    // println(2.double)
    // println(id(10))
    // println(a.name)

    // println("hoge".hoge)
    // println("hoge".hoge)
    // val i = 1

    // sayWho("asdf")

    // println(i.whoMethod)

    // Typer.Red == Typer.Red
  }
}
