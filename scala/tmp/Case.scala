object Case {
  def main(args: Array[String]) {
    val u = new User("ganmacs", 1)
    u match {
      case User(name, id) => println(name + " " + id)
      case _ => println("nothing")
    }
  }

  class User(private val name: String, private val id: Int)

  object User {
    def unapply(u: User) = Option((u.name, u.id))
  }
}
