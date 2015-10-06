import org.scalatest.FunSpec

class ParserTest extends FunSpec {

  describe ("rule") {
    assert(parse("rule $EXPR = $TERM @ $TERM { $1 + $2 } in 1 @ 1") ==
      (BinExpr(IntLit(1), Op("@"), IntLit(1)), Env.empty[Value])
    )
  }

  // describe ("rule") {
  //   assert(parse("rule $EXPR = $TERM @ $TERM { $1 + $2 } in 1 @ 1") ==
  //     Rule(
  //       NSyntax(
  //         NoTerm("$EXPR"),
  //         Syntax(NoTerm("$TERM"), Op("@"), NoTerm("$TERM"))
  //       ),
  //       Semantics(" $1 + $2 "),
  //       BinExpr(IntLit(1), Op("@"), IntLit(1))
  //     )
  //   )
  // }

  def parse(in: String) = Parser.parse(in) match {
    case Right(x) => x
  }
}
