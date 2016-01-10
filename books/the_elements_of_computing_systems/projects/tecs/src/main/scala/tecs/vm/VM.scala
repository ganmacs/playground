package tecs.vm

import tecs.util._

object VM {
  private val f = new FileHandler
  private val ROOT = "src/test/resources/vm/"
  private val p = Parser()

  def main(args: Array[String]): Unit = {
    val v = f.loadfile(ROOT + args(0) + ".vm").filter(_ != "")
    Asm.filename = args(0)
    val contents = v.map(p.parse(_)).map(_.toAsm).filter(_ != "")
    f.writeFile(ROOT + args(0) + ".asm", contents)
  }

    def eval(commands: List[Command]) = {
    }
  }
