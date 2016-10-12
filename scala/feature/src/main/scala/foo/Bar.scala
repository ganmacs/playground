package foo.bar

import scala.language.implicitConversions

sealed class Ac(val name : String)
object A1 extends Ac("your name is 1")
object A2 extends Ac("your name is 2")

class Watch(phone: Phone) {
  def yourName = s"your phone name is $phone.yourName"
}

private[bar] class Phone(name: String) {
  def yourName = s"your name is $name"
}

object Phone {
  implicit def apply(str: String) = new Phone(str)
}
