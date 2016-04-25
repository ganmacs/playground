package input

object CharSequenceReader {
  final val EofCh = '\u001a'
}

class CharSequenceReader(override val source: java.lang.CharSequence, override val offset: Int) extends Reader[Char] {
  import CharSequenceReader._

  def this(source: java.lang.CharSequence) = this(source, 0)

  def first = if (offset < source.length) source.charAt(offset) else EofCh

  def rest: CharSequenceReader = if (offset < source.length) new CharSequenceReader(source, offset + 1) else this
}
