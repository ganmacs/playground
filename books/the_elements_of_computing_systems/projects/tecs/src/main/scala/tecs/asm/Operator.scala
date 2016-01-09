package tecs.asm

sealed trait Operator {
  def asm: String
}

case class AOperator(v: String) extends Operator {
  lazy val binaryV = Integer.parseInt(v).toBinaryString
  override def asm: String = ("0000000000000000" + binaryV).takeRight(16)
}

case class COperator(dest: Option[String], comp: String, jump: Option[String]) extends Operator {
  override def asm: String = "111" + Code.comp(comp) + ((dest, jump) match {
    case (None, None) => Code.dest("null") + Code.jump("null")
    case (Some(d), None) => Code.dest(d) + Code.jump("null")
    case (None, Some(j)) => Code.dest("null") + Code.jump(j)
    case (Some(d),  Some(j)) => Code.dest(d) + Code.jump(j)
  })
}

object Code {
  def dest(str: String) = str match {
    case "null" => "000"
    case "M"    => "001"
    case "D"    => "010"
    case "MD"   => "011"
    case "A"    => "100"
    case "AM"   => "101"
    case "AD"   => "110"
    case "AMD"  => "111"
  }

  def jump(str: String) = str match {
    case "null" => "000"
    case "JGT"  => "001"
    case "JEQ"  => "010"
    case "JGE"  => "011"
    case "JLT"  => "100"
    case "JNE"  => "101"
    case "JLE"  => "110"
    case "JMP"  => "111"
  }

  def comp(str: String) = str match {
    case "0"   => "0101010"
    case "1"   => "0111111"
    case "-1"  => "0111010"
    case "D"   => "0001100"
    case "A"   => "0110000"
    case "M"   => "1110000"
    case "!D"  => "0001101"
    case "!A"  => "0110001"
    case "!M"  => "1110001"
    case "-D"  => "0001111"
    case "-A"  => "0110011"
    case "-M"  => "1110011"
    case "D+1" => "0011111"
    case "A+1" => "0110111"
    case "M+1" => "1110111"
    case "D-1" => "0001110"
    case "A-1" => "0110010"
    case "M-1" => "1110010"
    case "D+A" => "0000010"
    case "D+M" => "1000010"
    case "D-A" => "0010011"
    case "D-M" => "1010011"
    case "A-D" => "0000111"
    case "M-D" => "1000111"
    case "D&A" => "0000000"
    case "D&M" => "1000000"
    case "D|A" => "0010101"
    case "D|M" => "1010101"
  }
}
