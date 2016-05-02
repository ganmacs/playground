import parsers._
import parsers.input._

object Main {
  // class A (parse: String => Int) {
  //   class B {
  //   }

  //   def p(x: String) = parse(x)
  // }

  // object A {
  //   def apply (parse: String => Int) = new A(parse)
  // }

  // abstract class B {
  //   def a = "adf"
  // }

  // class Caller {
  //   def apply(x: Int) = println(x)
  // }

  // case class ~[+A, +B] (first: A, second: B)
  // case class C[+A, +B] (first: A, second: B)

  // trait CC {
  //   def a: Int
  // }
  // def CC() = new CC { def a = 1 }

  object A extends Parsers {
    type Elem = Char
    val a = elem('1') ~ elem('2') ~ elem('3') ^^ {
      case a ~ b ~ c => a+b+c
    }
  }

  def a(x: => Int): Int = {
    println(4)
    x
  }

  abstract class Result[+T] {
    def map[U](f: T => U): Result[U]
    // = new Result(f(x))
    def flatMap[U](f: T => Result[U]): Result[U]

    // = f(x) match {
    //   case Result(v) => new Result(v)
    //   case x => x
    // }
  }

  case class Suc[+T](x: T) extends Result[T] {
    def map[U](f: T => U): Suc[U] =  Suc(f(x))
    def flatMap[U](f: T => Result[U]): Result[U] = f(x)
  }

  case object Err extends Result[Nothing] {
    def map[U](f: Nothing => U) = Err
    def flatMap[U](f: Nothing => Result[U]) = Err
  }

  object Result {
    def apply[T](x: T): Result[T] = if (x == null) Err else Suc(x)
  }

  // (return x) >>= f == f x
  // m >>= return == m
  // (m >>= f) >>= g == m >>= (\x -> f x >>= g)

  def main(args: Array[String]) = {
     val a = Result(10)
    println(a.flatMap(x => Err).map(x => 10))

    // val a = Stat(10)
    // println(a.flatMap(x => Suc(x + 1)))
    // println(a.map(_ + 1).map(null))

    // println(Some(10).map(x => null))
    // println(Some(null))
    // println(Option(null))

    // println(Some(10).flatMap(x => Some(x+1)))
    // println(None.flatMap(x => Some(1)))
    // val a = List(1, 3, 4)
    // println(a.flatMap { in => println(in); List(in) })

    // println(List(1, List(10), 4).flatMap(x => List(x)))
    // println(Some(10).map(x => None))
    // val xx = for {
    //   x <- a
    //   y <- new Result(x)
    // } yield x + 1

    // println(xx)

    // println(a(10))
    // println( println(A.a(new CharSequenceReader("123"))))

    // val a = Some(1)
    // val a2 = for (x <- a) yield x + 1
    // println(a2)

    // println(a({println(1);10}))
    // println(A.a(new CharSequenceReader("-")))
    // val c = CC
    // println(c.a)

    // val a = new Caller
    // a(10)
    // val v = new ~(1, 3)
    // v match { case ~(l, k) => println(l) }
    // v match { case l ~ k => println(l) }

    // val v1 = new C(1, 3)
    // v1 match { case C(v, v2) => println(v) }

    // val a = A { x => 10 }
    // println(a.p("asd"))

    // val b = new B { def c = "cccc" }
    // println(b.a)
  }
}
