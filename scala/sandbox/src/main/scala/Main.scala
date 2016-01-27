import scala.util._

object Main {
  def main(args: Array[String]) {
    check3
    check4



    // for {
    //   a <- check1(1).right
    //   b <- Some(1).toRight("asd").left
    // } yield {
    //   return println(a, b)
    // }

    // for {
    //   a <- check2(1)
    // } yield {
    //   a
    // }

  }


  def check1(a: Int): Either[String, (Int, String)] = a match {
    case 1 => Right((1, "aa"))
    case _ => Left("foo")
  }

  def check2(a: Int): Try[Int] = a match {
    case 1 => Success(1)
    case _ => Failure { new Exception("ss") }
  }

  def check3 = {
    val a = for {
      a <- Some(1).toRight(new Exception("None")).right
      b <- Some(a).toRight("ss").right
    } yield a+b

    val b = for {
      a <- None.toRight(new Exception("None")).right
      b <- Right(2).right
    } yield a

    println(a)
    println(b)
  }

  def check4 = println ({
    for { a <- Some(1).toRight("ss").right } yield a
  }.merge)
}
