object Apply {
  def main(args: Array[String]) {
    val f = new Bar
    println(f("aa"))
    val ff = f.build
    println(ff("bb"))

    // val h = new Hoge
    // println(h)
    // println(h.a.x)
    // println(h.a.f)
    // println(h.a.x)

    // val f = new Fuga
    // println(f.a.b)
    // println(
    //   f.c {
    //     println("call-by name")
    //     1
    //   })

    // val kk = f.factory("hgoe")
    // println(kk ("aaa"))

  }

  class Hoge extends N(10)
  class Fuga extends M
  class Bar extends F

  abstract class F {
    def apply(in: String) = "one" + in

    def build = new F {
      override def apply(in: String) = "two" +in
    }
  }

  abstract class M {
    def d(q: () => Int) = q ()

    def c(q: => Int) = {
      println("wryyyyy")
      q
    }

    def factory(hoge: String) = new M {
      def apply(in: String) =  hoge + in
    }

    def a = new M {
      def b = Some(1)
    }
  }

  abstract class N(val y: Int) {
    var x = "name"
    def a = new N(10) {
      def f = {
        x = "fua"
      }
    }
  }
}
