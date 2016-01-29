package tecs.compiler

object VMWriter {
  def push(segment: String, idx: String) = s"push $segment $idx"

  def pop(segment: String, idx: String) = s"pop $segment $idx"

  def push(segment: Kind, idx: Int) = segment match {
    case ARG => s"push argument $idx"
    case VAR => s"push local $idx"
  }
  def pop(segment: Kind, idx: Int) = segment match {
    case ARG => s"pop argument $idx"
    case VAR => s"pop local $idx"
  }

  def arithmetic(op: String) = op match {
    case "*" => "call Math.multiply 2"
    case "-" => "sub"
    case "+" => "add"
    case "=" => "eq"
    case "<" => "lt"
    case ">" => "gt"
    case "&" => "and"
    case "|" => "or"
  }
  def uop(s: String) = s match {
    case "-" => "neg"
    case "~" => "not"
  }

  def call(name: String, nArgs: Int) = s"call $name $nArgs"

  def ifg(name: String) = s"if-goto $name"
  def goto(name: String) = s"goto $name"
  def label(s: String) = s"label $s"
  def ret = "return"
}
