package tecs.compiler

object VMWriter {
  def push(segment: String, idx: String) = s"push $segment $idx"

  def pop(segment: String, idx: String) = s"pop $segment $idx"

  def push(segment: Kind, idx: Int) = segment match {
    case ARG => s"push argument $idx"
    case VAR => s"push local $idx"
    case FIELD => s"push this $idx"
    case STATIC => s"push static $idx"
  }
  def pop(segment: Kind, idx: Int) = segment match {
    case ARG => s"pop argument $idx"
    case VAR => s"pop local $idx"
    case FIELD => s"pop this $idx"
    case STATIC => s"pop static $idx"
  }

  def func(name: String, size: Int) = s"function $name $size"

  def arithmetic(op: String) = op match {
    case "*" => "call Math.multiply 2"
    case "/" => "call Math.divide 2"
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

  def ifexp(c: Seq[String], e1: Seq[String], e2: Seq[String], idx: Int) = {
    (c ++ Seq(VMWriter.uop("~"), VMWriter.ifg(s"IF_ELSE_${idx}")) ++ e1 ++
      Seq(VMWriter.goto(s"IF_END_${idx}"), VMWriter.label(s"IF_ELSE_${idx}")) ++ e2) :+
    VMWriter.label(s"IF_END_${idx}")
  }

  def whielexp(cond: Seq[String], body: Seq[String], idx: Int) = {
    VMWriter.label(s"WHILE${idx}") +: (cond ++ Seq(VMWriter.uop("~"), VMWriter.ifg(s"WHILE_END${idx}")) ++
    body ++ Seq(VMWriter.goto(s"WHILE${idx}"), VMWriter.label(s"WHILE_END${idx}")))
  }

  def call(name: String, nArgs: Int) = s"call $name $nArgs"

  def ifg(name: String) = s"if-goto $name"
  def goto(name: String) = s"goto $name"
  def label(s: String) = s"label $s"
  def ret = "return"
}
