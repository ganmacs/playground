class Value
case class IntValue(v: Int) extends Value {
  override def toString() = v.toString
}
case class DoubleValue(v: Double) extends Value {
  override def toString() = v.toString
}
