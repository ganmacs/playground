package tecs.vm

sealed abstract class Command {
  def toAsm: String
}


case class Push(arg1: String, arg2: String) extends Command {
  override def toAsm: String = arg1 match {
    // case "argument" => ""
    // case "local" => ""
    // case "static" => ""
    case "constant" => Asm.pushA(arg2)
      // case "this" =>
      // case "that" =>
      // case "pointer" =>
      // case "temp" =>
  }
}

case class Pop(arg1: String, arg2: String) extends Command {
  override def toAsm: String = Asm.pop + Asm.incSP
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
