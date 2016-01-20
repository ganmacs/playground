package tecs.compiler

import java.io.File
import tecs.util._

object Compiler {
  private val ROOT = "src/test/resources/compiler/"
  private val f = new FileHandler


  def main(args: Array[String]): Unit = {
    val filepath = new File(ROOT, args(0))
    val c = load(filepath)
    val ce = new CompilationEngine(c)
    ce.compile()
  }

  private def load(filepath: File): String = {
    val contents = f.loadfile(filepath + ".jack").flatMap(_.split(" "))
    return trimComment(contents).reduce((a, b) => a + " " + b)
  }

  private def trimComment(ss: List[String]): List[String] = {
    var r: List[String] = List()
    var f = true

    for (s <- ss) {
      // start comment
      if (s.matches("""/\*.*""")) { f = false }

      if (f) {
        r = s :: r
      } else {
        if (s.matches(""".*\*/""")) { f = true }
      }
    }
    return r.reverse
  }
}
