package asm

case class Translator(sources: List[String]) {
  lazy val line = withIndex(sources)

  def call = withoutLable(line)

  def symbolTable: List[(String, Int)] =
    line.filter { case (s, i) => isLabel(s) }
        .map { case (s, i) => ("""[_:.$A-Z][_:.$A-Z0-9]*""".r.findFirstMatchIn(s).get.toString(), i) }

  private def withIndex(s: List[String]): List[(String, Int)] = {
    var i = 0
    var ret: List[(String, Int)] = List()

    for (line <- s) {
      ret = (line, i) :: ret

      if (!isLabel(line)) {
        i += 1
      }
    }
    ret.reverse
  }

  private def withoutLable(l: List[(String, Int)]): List[(String, Int)] = {
    l.filterNot { case (s, i) => isLabel(s) }
  }

  private def isLabel(line: String) = line.matches("""\([_:.$A-Z][_:.$A-Z0-9]*\)""")
}
