object Color {
  def main(args: Array[String]) {
    // val u = new User("ganmacs", 1)
    // u match {
    //   case User(name, id) => println(name + " " + id)
    //   case _ => println("nothing")
    // }

    val s = Student("name")

    println(extract_name(s))
  }

  def extract_name(u: User): String = u match {
    case Student(name) => "student:" + name
    case Teacher(name) => "teacher:" + name
    case Boss(name) => "boss:" + name
    case _ => "Unknow type"
  }

  sealed trait User {
    val name: String
  }

  case class Student(name: String) extends User
  case class Teacher(name: String) extends User
  case class Boss(name: String) extends User
}
