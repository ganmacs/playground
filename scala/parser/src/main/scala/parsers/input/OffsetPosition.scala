package parsers.input

import scala.collection.mutable.ArrayBuffer

case class OffsetPosition(source: java.lang.CharSequence, offset: Int) extends Position {
  def line = {
    var l = 0
    var r = index.length - 1
    while (l + 1 < r) {
      val m = (l + r) / 2
      if (offset < index(m)) r = m
      else l = m
    }
    l + 1
  }

  def column = offset - index(line - 1) + 1

  private lazy val index: Array[Int] = makeIndex()

  private def makeIndex(): Array[Int] = {
    val index = ArrayBuffer(0)
    for (i <- 0 until source.length) {
      if (source.charAt(i) == '\n') index += (i+1)
    }
    index += source.length
    index.toArray
  }
}
