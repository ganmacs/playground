package tecs.vm

import java.io.File
import tecs.util._

object VM {
  private val ROOT = "src/test/resources/vm/"
  private val f = new FileHandler
  private val p = Parser()

  def main(args: Array[String]): Unit = {
    val dir = new File(ROOT, args(0))

    if (dir.exists() && dir.isDirectory()) {
      genVMfiles(loadVMfiles(dir))
    } else {
      val file = dir
      genVMfile(file)
    }
  }

  private def genVMfiles(files: Seq[File]) = {
    var contents: List[String] = List()

    for (file <- files) {
      Asm.filename = file.getName

      var s = ""
      if (Asm.filename == "Sys.vm") {
        s += Asm.setup
      }

      s += s"// $file\n"
      contents ++ (f.loadfile(file).map(p.parse(_).toAsm) :+ s)
    }

    val ff = "/" + files(0).getParent.split("/").last
    f.writeFile(files(0).getParent + ff + ".asm", contents)
  }

  private def genVMfile(file: File) = {
    Asm.filename = file.getName
    val contents = f.loadfile(file + ".vm").map(p.parse(_).toAsm)
    f.writeFile(file + ".asm", contents)
  }

  private def loadVMfiles(dir: File): Seq[File] = {
    val main = new File(dir + "/Sys.vm")
    val others = dir.list.toList.
      filter(x => x != "Sys.vm" && x.matches(".*\\.vm") ).
      map(x => new File(dir.toString + s"/$x"))
    main :: others
  }
}
