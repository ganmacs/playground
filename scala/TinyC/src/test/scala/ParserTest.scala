import org.scalatest.FunSpec

class ParserTest extends FunSpec {
  describe("Syntax") {
    describe("Literal") {
      it ("returns IntLit") {
        assert(parse("1") == IntLit(1))
        assert(parse("100") == IntLit(100))
      }

      it ("returns DoubleLit") {
        assert(parse("3.14") == DoubleLit(3.14))
        assert(parse("0.34") == DoubleLit(0.34))
      }

      it ("returns IdLit") {
        assert(parse("x") == IdLit("x"))
        assert(parse("xS2") == IdLit("xS2"))
      }
    }

    it ("returns BinExpr") {
      assert(parse("1 * 2") == BinExpr(
        IntLit(1), Op("*"), IntLit(2)
      ))

      assert(parse("1.0 * x") == BinExpr(
        DoubleLit(1.0), Op("*"), IdLit("x")
      ))
    }

    it ("should ignore paren") {
      assert(parse("(1 + 2)") == BinExpr(
        IntLit(1), Op("+"), IntLit(2)
      ))

      assert(parse("3 * (1 + 2)") == BinExpr(
        IntLit(3), Op("*"), BinExpr(
          IntLit(1), Op("+"), IntLit(2)
        )
      ))
    }
  }

  def parse(in: String) =
    Parser.parse(in) match {
      case Right(x) => x
      case Left(x) => x
    }
}
