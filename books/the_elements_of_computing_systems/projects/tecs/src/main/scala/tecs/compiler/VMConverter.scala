package tecs.compiler

class VMConverter extends Converter {
  def run(s: Syntax): Seq[String] = toVM(s, "Nil")

  def toVM(s: Syntax, className: String): Seq[String] = s match {
    case S_class(className, varDecs, subroutines) => {
      // varDecs.getOrElse(Nil).map()
      // subroutines.getOrElse(Nil).map()

      // toVM(varDecs, className)
      // toVM(subroutines, className)
      List("function")
    }
      // case S_classVarDec(p, t, S_varNameList(name)) => {
      // }
  }

}
