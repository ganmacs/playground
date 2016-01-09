package asm

case class SymbolTable() {
  private var t: Map[String, String] = Map.empty[String, String]
  private var i: Int = 16 // address of memory start

  override def toString = t.toString

  def addSymbol(k: String): String = t.get(k) match {
    case Some(v) => v
    case None => {
      val v = i.toString
      put(k, v)
      i += 1
      v
    }
  }

  def setup: SymbolTable = {
    put("SP", "0")
    put("LCL", "1")
    put("ARG", "2")
    put("THIS", "3")
    put("THAT", "4")
    put("SCREEN", "16384")
    put("KBD", "24567")
    (0 to 15).map(_.toString).foreach(e => put(s"R$e", e))
    this
  }

  def put(k: String, v: String) = { t = Map(k -> v) ++ t }
  private def isExist(v: String): Boolean = t.exists(_._1 == v)
}
