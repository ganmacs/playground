object Main2 {
  def main(args: Array[String]) {
    println(((x: Int) => x * x)(10))

    val ret = find(4, List(1,2,3,4,5))
    printIfExist(ret)

    println(
      flatten(
        List(
          quickSort(List(5, 2, 6, 1, 7, 3, 4, 5, 10 , 12)),
          quickSort(List(5, 2, 6, 1, 7, 3, 4, 5, 10 , 12)),
          quickSort(List(5, 2, 6, 1, 7, 3, 4, 5, 10 , 12))
        )
      )
    )
  }

  def flatten[T](xs: List[List[T]]): List[T] =
    for (ys <- xs; y <- ys) yield y

  def quickSort(xs: List[Int]): List[Int] =
    xs match {
      case Nil => Nil
      case p :: ys =>  {
        val l = for (y <- ys if y < p) yield y
        val r = for (y <- ys if y >= p) yield y
        quickSort(l) ::: List(p) ::: quickSort(r)
      }
    }

  def identity[T](x: T) = x

  def a(i: Int)(j: Int) = i + j

  def recieve(school: School[Person]) = println("success!!")

  def myRevrse[T](xs: List[T]): List[T] = xs match {
    case Nil => Nil
    case x :: xs => myRevrse(xs) ::: List(x)
  }

  def printIfExist[T](result: Option[T]) = result match {
    case None => println("Not found")
    case Some(x) => println(x)
  }

  def find[T](x: T, xs: List[T]): Option[T] = xs match {
    case Nil => None
    case y :: ys if (x == y) => Some(y)
    case y :: ys => find(x, ys)
  }

  def mfilter[T](f: T => Boolean, xs: List[T]): List[T] = xs match {
    case Nil => Nil
    case y :: ys if (f(y)) => y :: mfilter(f, ys)
    case _ :: ys => mfilter(f, ys)
  }
}
