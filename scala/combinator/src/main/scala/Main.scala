object Main {
  def main(args: Array[String]) {
    ArithParser("1 + 2 * (10 + 10)") match {
      case Left(errorMsg) => println(errorMsg)
      case Right(v) => println(ArithEvaluator.eval(v))
    }
  }
}
