package tecs.vm

case class Parser() {
  def parse(str: String) = str.split(" ") match {
    case Array(a, b, c) => Command(a, Some(b), Some(c))
    case Array(a, b) => Command(a, Some(b), None)
    case Array(a) => Command(a, None, None)
  }
}
