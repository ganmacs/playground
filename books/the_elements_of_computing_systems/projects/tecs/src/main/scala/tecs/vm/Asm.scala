package tecs.vm


object Asm {
  private val counter = new {
    private var i = -1
    def inc: String = { this.i += 1; this.i.toString }
  }

  val sp = aop("SP")
  val lcl = aop("LCL")
  val arg = aop("ARG")
  val _this = aop("THIS")
  val that = aop("THAT")
  val screen = aop("SCREEN")
  val kbd = aop("KBD")
  val incSP: String = sp + "M=M+1\n"
  val decSP: String = sp + "M=M-1\n"

  // set SP ptr value to M
  val ptrSP: String = sp + "A=M\n"
  val decAndptrSP: String = decSP + "A=M\n"

  //  pop x and y, then set D = y, M = x
  val popAndSetD_M = pop + decAndptrSP

  def assignPtrSP(v: String) = ptrSP + s"M=$v\n"

  def aop(x: String): String = s"@$x\n"

  // push D register value to SP postion
  def push: String = ptrSP + "M=D\n" + incSP

  // pop value to D register
  def pop: String = decAndptrSP + "D=M\n" + incSP

  def pushA(x: String): String = {
    var s = aop(x)
    s += "D=A\n"
    s + push
  }

  def add: String = popAndSetD_M + "M=M+D\n" + incSP
  def sub: String = popAndSetD_M + "M=M-D\n" + incSP

  def and: String = popAndSetD_M + "M=M&D\n" + incSP
  def or: String = popAndSetD_M + "M=M|D\n" + incSP

  def neg: String = pop + "M=-D\n" + incSP
  def not: String = pop + "M=!D\n" + incSP


  def eq: String = compareWith("JEQ")
  def gt: String = compareWith("JGT")
  def lt: String = compareWith("JLT")

  private def compareWith(cond: String): String = {
    val n = counter.inc

    var s = pop
    s += decAndptrSP
    s += "D=M-D\n"   // x - y
    s += s"@COMP_LABEL_$n\n"
    s += s"D; $cond\n"
    s += assignPtrSP("0")
    s += s"@COMP_LABEL_END_$n\n"
    s += "0; JMP\n"
    s += s"(COMP_LABEL_$n)\n"
    s += assignPtrSP("-1")
    s += s"(COMP_LABEL_END_$n)\n"
    s + incSP
  }
}


// {
//   val n = counter.inc

//   var s = pop
//   s += decAndptrSP
//   s += "D=M-D\n"   // y - x
//   s += s"@EQ_LABEL$n\n"
//   s += "D; JEQ\n"
//   s += assignPtrSP("0")
//   s += s"@EQ_LABEL_END$n\n"
//   s += "0; JMP\n"
//   s += s"(EQ_LABEL$n)\n"
//   s += assignPtrSP("-1")
//   s += s"(EQ_LABEL_END$n)\n"
//   s + incSP
// }
