object Sandbox {
  def main(args: Array[String]) {
    val a1 = new Animal("user1")
    val a2 = new Animal("user2")
    val a3 = Animal.apply("hoge", 11)
    println(((_: Int) + (_: Int))(10, 21))

    println(a1 < a3)

    test(a1)
    test(a2)
  }

  def test(a: Animal) = a match {
    case Animal("user1", age)  => println(a)
    case _ => println("No!!!")
  }
}

trait Orderable {
  def <(that: Any): Boolean
  def <=(that: Any) = this < that || this == that
  def >(that: Any) = !(this < that) && this != that
  def >=(that: Any) = !(this < that)
}

class Animal(private val name: String = "", val age: Int = 10) extends Orderable {
  override def toString = s"{\n  name: $name, \n  age: $age \n}"
  override def equals(other: Any) = other match {
    case x: Animal => (x.name == this.name) && (x.age == this.age)
    case _ => false
  }

  def <(that: Any): Boolean = that match {
    case x: Animal => this.age < x.age
    case _ => false
  }
}
object Animal {
  def getName(a: Animal) =  a.name + ": get form object Animal"
  def apply(name: String, age: Int) = new Animal(name, age)
  def unapply(a: Animal) = Some((a.name, a.age))
}

class Person extends Animal
class Student extends Person
class School[+T]

trait Who[T] {
  def who(x: T): String

  implicit def WhoInt = new Who[Int] {
    def who(x: Int) = "Int"
  }

  implicit def WhoDouble = new Who[Double] {
    def who(x: Double) = "Double"
  }
}
