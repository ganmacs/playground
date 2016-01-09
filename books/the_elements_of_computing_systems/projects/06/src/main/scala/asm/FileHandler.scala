package asm

import scala.io.Source
import java.io.PrintWriter

class FileHandler {
  def loadfile(filePath: String): List[String] = {
    val source = Source.fromFile(filePath)
    source.getLines.toList.map(trimComment(_).trim)
  }

  def writeFile(filePath: String, contents: List[String]) =  {
    val file = new PrintWriter(filePath)
    for (l <- contents) { file.write(l+"\n") }
    file.close()
  }

  def trimComment(line: String): String = line.replaceAll("//.*", "")
}
