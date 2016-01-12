package tecs.vm

case class Parser() {
  def parse(str: String): Command = str.split(" ") match {
    case Array("push", a, b) => Push(a, b)
    case Array("pop", a, b) => Pop(a, b)
    case Array("function", a, b) => Function(a, b)
    case Array("label", a) => Lable(a)
    case Array("goto", a) => Goto(a)
    case Array("if-goto", a) => IfGoto(a)
    case Array("call", a) => Call(a)
    case Array("return") => Return()
    case Array("add") => Add()
    case Array("sub") => Sub()
    case Array("neg") => Neg()
    case Array("eq")  => Eq()
    case Array("gt")  => Gt()
    case Array("lt")  => Lt()
    case Array("and") => And()
    case Array("or")  => Or()
    case Array("not") => Not()
  }
}
