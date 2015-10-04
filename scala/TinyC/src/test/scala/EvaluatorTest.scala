import org.scalatest.FunSpec

class EvaluatorTest extends FunSpec {
  describe("Eval") {

    describe ("IntT") {
      it ("returns value that was wrapped by IntT")  {
        assert(eval("1 + 1") == IntT(2))
        assert(eval("1 + 2 * 2") == IntT(5))
        assert(eval("(1 + 2) * 2") == IntT(6))
      }
    }

    describe ("Double") {
      it ("returns value that was wrapped by DoubleT")  {
        assert(eval("1.0 + 2.0") == DoubleT(3.0))
        assert(eval("2.0 + 2.0 * 3.0") == DoubleT(8.0))
        assert(eval("(2.0 + 2.0) * 3.0") == DoubleT(12.0))
      }
    }

    describe ("let") {
      it ("uses let keyword")  {
        assert(eval("let x = 1 + 2 in x") == IntT(3))
        assert(eval("let x = 10 in let y = 2 in x + y") == IntT(12))
      }
    }
  }

  def eval(in: String) =
    Parser.parse(in) match {
      case Right(e) => Evaluator.eval(e)
    }
}
