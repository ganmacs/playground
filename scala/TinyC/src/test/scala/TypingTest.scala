import org.scalatest.FunSpec

class TypingTest extends FunSpec {
  it("IntType") {
    assert(check("1 + 1") == IntType())
    assert(check("1 + 1 * 1") == IntType())
    assert(check("(1 * 10) + 1 * 1") == IntType())
  }

  it("DoubleType") {
    assert(check("1.0 + 1.0") == DoubleType())
    assert(check("1.0 + 1.0 * 10.0") == DoubleType())
  }

  it("let") {
    assert(check("let x = 1 in x + 1") == IntType())
    assert(check("let x = 1 in let x = 1.0 in  x + x") == DoubleType())
  }

  def check(in: String) =
    Parser.parse(in) match { case Right(x) => Typing.check(x) }
}
