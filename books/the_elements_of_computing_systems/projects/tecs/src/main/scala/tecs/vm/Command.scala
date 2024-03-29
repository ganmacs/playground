package tecs.vm

 sealed abstract class Command {
  def toAsm: String
}

case class Push(arg1: String, arg2: String) extends Command {
  override def toAsm: String = arg1 match {
    case "argument" => Asm.push("ARG", arg2)
    case "local"    => Asm.push("LCL", arg2)
    case "static"   => Asm.pushS(arg2)
    case "constant" => Asm.pushC(arg2)
    case "this"     => Asm.push("THIS", arg2)
    case "that"     => Asm.push("THAT", arg2)
    case "pointer"  => Asm.pushI("3", arg2)
    case "temp"     => Asm.pushI("5", arg2)
  }
}

case class Pop(arg1: String, arg2: String) extends Command {
  override def toAsm: String = arg1 match {
    case "argument" => Asm.pop("ARG", arg2)
    case "local"    => Asm.pop("LCL", arg2)
    case "static"   => Asm.popS(arg2)
    case "constant" => Asm.pop("SP", arg2)
    case "this"     => Asm.pop("THIS", arg2)
    case "that"     => Asm.pop("THAT", arg2)
    case "pointer"  => Asm.popI("3", arg2)
    case "temp"     => Asm.popI("5", arg2)
  }
}

case class Add() extends Command {
  override def toAsm: String = Asm.add
}

case class Sub() extends Command {
  override def toAsm: String = Asm.sub
}

case class Neg() extends Command {
  override def toAsm: String = Asm.neg
}

case class Eq() extends Command {
  override def toAsm: String = Asm.eq
}

case class Gt() extends Command {
  override def toAsm: String = Asm.gt
}

case class Lt() extends Command {
  override def toAsm: String = Asm.lt
}

case class And() extends Command {
  override def toAsm: String = Asm.and
}

case class Or() extends Command {
  override def toAsm: String = Asm.or
}

case class Not() extends Command {
  override def toAsm: String = Asm.not
}

case class Lable(arg1: String) extends Command {
  override def toAsm: String = Asm.label(arg1)
}

case class Goto(arg1: String) extends Command {
  override def toAsm: String = Asm.goto(arg1)
}

case class IfGoto(arg1: String) extends Command {
  override def toAsm: String = Asm.ifgoto(arg1)
}

case class Function(arg1: String, arg2: String) extends Command {
  override def toAsm: String = Asm.function(arg1, Integer.parseInt(arg2))
}

case class Call(arg1: String, arg2: String) extends Command {
  override def toAsm: String = Asm.callexpr(arg1, arg2)
}

case class Return() extends Command {
  override def toAsm: String = Asm.returnExpr
}
