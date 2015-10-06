import org.scalatest.FunSpec

class ParserTest extends FunSpec {

  describe ("rule") {
    assert(parse("rule $EXPR = $TERM @ $TERM { $1 + $2 + 1 } in 1 @ 1") ==
      (ExprList(List(IntLit(1), Op("@"), IntLit(1))),
        Env(None, scala.collection.mutable.Map("1 @ 1" -> Semantics(" $1 + $2 + 1 "))
        )
      )
    )
  }

  def parse(in: String) = Parser.parse(in) match {
    case Right(x) => x
  }
}
