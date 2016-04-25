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

  case class ~[+A, +B] (first: A, second: B)
  case class C[+A, +B] (first: A, second: B)

  def main(args: Array[String]) = {
    val v = new ~(1, 3)
    // v match { case ~(l, k) => println(l) }
    v match { case l ~ k => println(l) }

    val v1 = new C(1, 3)
    v1 match { case C(v, v2) => println(v) }

    // val a = A { x => 10 }
    // println(a.p("asd"))

    // val b = new B { def c = "cccc" }
    // println(b.a)
  }
}
