package combinator

import org.scalatest._

class ParsersTest extends FunSpec {
  object TestParser extends Parsers {
    type Elem = Char
  }
}
