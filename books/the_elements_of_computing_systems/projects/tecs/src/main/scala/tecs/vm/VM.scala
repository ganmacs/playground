package tecs.vm

import tecs.util._

object VM {
  private val f = new FileHandler
  private val ROOT = "src/test/resources/"
  private val p = Parser()

  def main(args: Array[String]) {
    val v = f.loadfile(ROOT + args(0) + ".vm").filter(_ != "")
    println(v.map(p.parse _))
  }
}
