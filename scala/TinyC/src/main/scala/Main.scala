object Main {
  def main(args: Array[String]) {
    val in = "let x = 10 in let y = 20 in x + y"
    eval(in)
  }

  def eval(in: String) = Parser.parse(in) match {
    case Left(x) => println(x)
    case Right(x) => {
      Typing.check(x)
      println(Evaluator.eval(x))
    }
  }
}
