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


  // def a(x: => Int): Int = {
  //   println(4)
  //   x
  // }

  // def rNone[T](x: T): Option[T] = None
  // def rWrap[T](x: T): Option[T] = Some(x)

  // def lazyFn(q: => Int): (Int => Int) = {
  //   println("2")
  //   lazy val p = q
  //   println("1")
  //   _ => p
  // }

  // var b = 10
  // lazy val a = if(b < 0) "aaa" else  "bbb"

  def main(args: Array[String]) = {

    println( SampleParser.a(new CharSequenceReader("123")) )
    println( SampleParser.d2(new CharSequenceReader("2348")) )
    println( SampleParser.e(new CharSequenceReader("24")) )
    println( SampleParser.f(new CharSequenceReader("24")) )

    // println(a)
    // b = -1
    // println(a)

    // val x = lazyFn({
    //   println("xxx")
    //   10})

    // println(x(10))
    // println(x(10))
    // println(x(10))
    // println(x(10))


    // val a = Result(10)
    // // println(a.flatMap(x => Err("null")).map(x => 10))
    // val b = Result(null)

    // val c = a match {
    //   case Suc(x) => b match {
    //     case Suc(y) => Suc(x + y)
    //     case Err(y) => Err(y)
    //   }
    //   case Err(x) => Err(x)
    // }

    // val d = a.map( x => b.map ( y => x + y ))

    // println(c)
    // println(d)

    // val c = for {
    //   x <- a
    //   y <- b
    // } yield {
    //   x + y
    // }

    // println(c)


    // // val v = Some(1)
    // val v = None
    // println(v.flatMap(rWrap))
    // // println(v.map(rWrap))


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
