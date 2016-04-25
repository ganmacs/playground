package input

trait Reader[+T] {
  def source: java.lang.CharSequence
  def offset: Int

  def first: T
  def rest: Reader[T]

  def drop(n: Int): Reader[T] = {
    var t: Reader[T] = this
    var cnt = n
    while (cnt > 0) {
      t = t.rest; cnt -= 1
    }
    t
  }
}
