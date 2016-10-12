package foo

import scala.language.implicitConversions

package object bar {

  def acPrinter(ac: Ac) = println(s"${ac.name}")

  implicit def impString(str: String) = new Phone(str)
}
