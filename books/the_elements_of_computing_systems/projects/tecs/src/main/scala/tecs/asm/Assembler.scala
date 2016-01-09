package tecs.asm

import tecs.util._

object Assembler {
  private val ROOT = "src/test/resources/"
  private val f = new FileHandler
  private val st = SymbolTable().setup

  def main(args: Array[String]) {
    val v = f.loadfile(ROOT + args(0) + ".asm").filter(_ != "")
    val t = Translator(v)
    for ((k, v) <- t.symbolTable) { st.put(k, v.toString) }

    val parser = Parser(st)

    val r = t.call.map(parser.parse(_)).map {
      case Right(v) => v.asm
      case Left(v) => throw new Exception(v)
    }
    f.writeFile(ROOT + args(0) + ".hack", r)
  }
}
