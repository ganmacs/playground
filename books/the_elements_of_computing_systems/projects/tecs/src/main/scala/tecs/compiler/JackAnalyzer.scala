package tecs.compiler

import java.io.File
import tecs.util._

object Compiler {
  private val ROOT = "src/test/resources/compiler/"
  private val f = new FileHandler
  private val r = """(.*\.jack)""".r

  // private lazy val converter = new XMLConveter()
  // private lazy val outputExt = ".xml"

  private lazy val converter = new VMConverter()
  private lazy val outputExt = ".vm"

  def main(args: Array[String]): Unit = {
    val f = new File(ROOT, args(0))
    if (f.exists()) {
      compileAll(f)
    } else {
      throw new Exception(s"not found file: $f")
    }
  }

  private def compileAll(dir: File) = {
    val fext = """(.+)\.jack$""".r

    for (file <- loadfiles(dir)) {
       val contents = f.loadfile(file).flatMap(_.split(" "))
      val c = trimComment(contents).reduce((a, b) => a + " " + b)
      val ce = new CompilationEngine(c, converter)

      file.toString match {
        case fext(ff) => f.writeFile(ff + outputExt, ce.compile())
        case _ => throw new Exception(s"not found file: $file")
      }
    }
  }

  private def loadfiles(dir: File): Seq[File] = dir.list.toSeq.collect {
    case r(x) => new File(dir.toString + "/" + x)
  }

  private def trimComment(ss: Seq[String]): Seq[String] = {
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
