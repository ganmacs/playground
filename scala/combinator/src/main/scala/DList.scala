class Cell[A](var prev: Cell[A] = null, var next: Cell[A] = null)
class CellItem[A](var v: A) extends Cell[A]

class DList[A] {
  private val head: Cell[A] = new Cell()
  head.prev = head
  head.next = head

  private def nth(n: Int): Cell[A] = {
    val lit = if (n >= 0) n else n.abs - 1
    var cp = if (n >= 0) head.next else head.prev

    for (x <- 0 to lit) {
      if (cp == head) return cp
      cp = if (n >= 0) head.next else head.prev
    }
    cp
  }

  def apply(n: Int): Option[CellItem[A]] = nth(n) match {
    case x: CellItem[A] => Some(x)
    case _ => None
  }

  def update(n: Int, x: A) = nth(n) match {
    case y: CellItem[A] => y.v = x
    case _ => throw new Exception("DList.update: out of range")
  }

  def length(): Int = {
    var cp = head.next
    var n = 0;
    while (cp != head) {
      n += 1
      cp = cp.next
    }
    n
  }
}
