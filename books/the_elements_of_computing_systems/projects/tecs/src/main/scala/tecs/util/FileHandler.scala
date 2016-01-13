package tecs.util

import java.io.File
import scala.io.Source
import java.io.PrintWriter

class FileHandler {
  def loadfile(file: File): List[String] = load(Source.fromFile(file))
  def loadfile(filePath: String): List[String] = load(Source.fromFile(filePath))

  def writeFile(filePath: String, contents: List[String]) = write(new PrintWriter(filePath), contents)
  def writeFile(file: File, contents: List[String]) = write(new PrintWriter(file), contents)

  def trimComment(line: String): String = line.replaceAll("//.*", "")

  private def load(s: Source): List[String] = {
    val c = s.getLines.toList.map(trimComment(_).trim).filter(_ != "")
    s.close
    c
  }

  private def write(f: PrintWriter, contents: List[String]) =  {
    for (l <- contents.filter(_ != "")) { f.write(l + "\n") }
    f.close
  }
}
