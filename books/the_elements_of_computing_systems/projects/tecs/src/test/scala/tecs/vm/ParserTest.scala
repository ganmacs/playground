package tecs.vm

import org.scalatest.FunSpec

class ParserTest extends FunSpec {
  val p = Parser()

  describe("#parse") {
    it("commnd") {
      assert(p.parse("eq") == Eq())
    }

    it("label IF_TRUE") {
      // assert(p.parse("label IF_TRUE") == Command("label", Some("IF_TRUE"), None))
    }

    it("push constant 17") {
      assert(p.parse("push constant 17") == Push("constant", "17"))
    }
  }
}
