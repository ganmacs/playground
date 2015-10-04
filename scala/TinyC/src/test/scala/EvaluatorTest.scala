import org.scalatest.FunSpec

class EvaluatorTest extends FunSpec {
  describe("Eval") {

    describe ("IntT") {
      it ("returns value that was wrapped by IntT")  {
        assert(eval("1 + 1") == IntValue(2))
        assert(eval("1 + 2 * 2") == IntValue(5))
        assert(eval("(1 + 2) * 2") == IntValue(6))
      }
    }

    describe ("Double") {
      it ("returns value that was wrapped by DoubleT")  {
        assert(eval("1.0 + 2.0") == DoubleValue(3.0))
        assert(eval("2.0 + 2.0 * 3.0") == DoubleValue(8.0))
        assert(eval("(2.0 + 2.0) * 3.0") == DoubleValue(12.0))
      }
    }

    describe ("let") {
      it ("uses let keyword")  {
        assert(eval("let x = 1 + 2 in x") == IntValue(3))
        assert(eval("let x = 10 in let y = 2 in x + y") == IntValue(12))
        assert(eval("let x = 10 in x * (let x = 2 in x + x)") == IntValue(40))
      }
    }
  }

  def eval(in: String) =
    Parser.parse(in) match {
      case Right(e) => Evaluator.eval(e)
    }
}
