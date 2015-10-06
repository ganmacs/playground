import org.scalatest.FunSpec

class EvaluatorTest extends FunSpec {

  describe("eval") {
    assert(eval("rule $EXPR = $TERM @ $TERM { $1 + $2 + 1 } in 1 @ 1") ==
      Semantics(" $1 + $2 + 1 ")
    )
  }

  def eval(in: String) = Parser.parse(in) match {
    case Right((x, e)) => Evaluator.eval(x, e)
  }
}
