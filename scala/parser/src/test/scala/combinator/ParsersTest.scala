package combinator

import org.scalatest._

class ParsersTest extends FunSpec {
  object TestParser extends Parsers {
    type Elem = Char

    val a = elem('1') ^^ (_ - '0')
  }

  import TestParser._
}
