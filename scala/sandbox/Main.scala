object Main {
  def main(args: Array[String]) {
    // val m = Map.empty[Int, Person]
    // val k = m + (1 -> new Animal)
    // println(k)

    variable_length("hoge", "fuga", "piyo")
  }

  def variable_length(s: String*) = s.foreach(println _)

  class Animal
  class Person extends Animal
  class Student extends Person
}
