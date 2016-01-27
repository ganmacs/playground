package tecs.util

import java.io.File
import scala.io.Source
import java.io.PrintWriter

class FileHandler {
  def loadfile(file: File): Seq[String] = load(Source.fromFile(file))
  def loadfile(filePath: String): Seq[String] = load(Source.fromFile(filePath))

  def writeFile(filePath: String, contents: Seq[String]) = write(new PrintWriter(filePath), contents)
  def writeFile(file: File, contents: Seq[String]) = write(new PrintWriter(file), contents)

  def trimComment(line: String): String = line.replaceAll("//.*", "")

  private def load(s: Source): Seq[String] = {
    val c = s.getLines.toList.map(trimComment(_).trim).filter(_ != "")
    s.close
    c
  }

  private def write(f: PrintWriter, contents: Seq[String]) =  {
    for (l <- contents.filter(_ != "")) { f.write(l + "\n") }
    f.close
  }
}
