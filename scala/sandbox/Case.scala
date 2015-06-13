object Case {
  def main(args: Array[String]) {
    val u = new User("ganmacs")
    u match {
      case User(user) => println(user)
      case _ => println("nothing")
    }
  }
}

class User(private val name: String)

object User {
  def unapply(u :User) = Option("hoge")
}
