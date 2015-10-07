import org.scalatest.FunSpec

class EvaluatorTest extends FunSpec {
  describe("eval") {
    assert(eval("rule $EXPR = $TERM @ $TERM { $1 + $2 + 1 } in 3 @ 3 * 2") ==
      IntValue(10)
    )
  }

  def eval(in: String) = Parser.parse(in) match {
    case Right((x, e)) => Evaluator.eval(x, e)
  }
}
