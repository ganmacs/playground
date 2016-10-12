package foo

package object bar {
  def acPrinter(ac: Ac) = println(s"${ac.name}")
}
