import parsers._
import parsers.input._

object Main {

  object A extends Parsers {
    type Elem = Char
    val a = elem('-')
  }

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

  def main(args: Array[String]) = {

    println(A.a(new CharSequenceReader("-")))
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
