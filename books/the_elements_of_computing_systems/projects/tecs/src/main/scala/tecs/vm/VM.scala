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

  private def genVMfiles(files: List[File]) = {
    var contents: List[String] = List()

    for (file <- files) {
      Asm.filename = file.getName
      contents = contents ::: (s"// $file" :: f.loadfile(file).map(p.parse(_).toAsm))
    }
    f.writeFile(files(0).getParent + ".asm", contents)
  }

  private def genVMfile(file: File) = {
    Asm.filename = file.getName
    val contents = f.loadfile(file + ".vm").map(p.parse(_).toAsm)
    f.writeFile(file + ".asm", contents)
  }

  private def loadVMfiles(dir: File): List[File] = {
    val main = new File(dir + "/Sys.vm")
    val others = dir.list.toList.
      filter(x => x != "Sys.vm" && x.matches(".*\\.vm") ).
      map(x => new File(dir.toString + s"/$x"))
    main :: others
  }
}
