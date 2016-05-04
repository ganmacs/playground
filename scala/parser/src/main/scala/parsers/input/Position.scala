package parsers.input

trait Position {
  def line: Int
  def column: Int

  def < (that: Position): Boolean = {
    this.line < that.line || (this.line == that.line && this.column < that.column)
  }

  def <= (that: Position): Boolean = {
    this < that && (this.line == that.line && this.column == that.column)
  }

  def > (that: Position): Boolean = !(this <= that)

  def >= (that: Position): Boolean = !(this < that)

  def == (that: Position): Boolean = this <= that && this >= that
}
