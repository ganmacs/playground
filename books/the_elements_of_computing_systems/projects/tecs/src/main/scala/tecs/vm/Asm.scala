package tecs.vm

object Asm {
  private val counter = new {
    private var i = -1
    def inc: String = { this.i += 1; this.i.toString }
  }

  val sp = "@SP\n"
  val incSP: String = sp + "M=M+1\n"
  val decSP: String = sp + "M=M-1\n"

  // set SP ptr value to M
  val ptrSP: String = sp + "A=M\n"
  val decAndptrSP: String = decSP + "A=M\n"

  //  pop x and y, then set D = y, M = x
  val popAndSetD_M = pop + decAndptrSP

  def assignPtrSP(v: String) = ptrSP + s"M=$v\n"

  // push D register value to SP postion
  def push: String = ptrSP + "M=D\n" + incSP

  // poped value to D register
  def pop: String = decAndptrSP + "D=M\n"


  def pushC(x: String) = {
    var s = s"@$x\n"
    s += "D=A\n"
    s + push
  }

  def push(seg: String, x: String): String = {
    var s = calcMLocation(seg, x)
    s += s"D=M\n"
    s + push
  }

  def pushI(seg: String, x: String): String = {
    var s = calcMLocationI(seg, x)
    s += s"D=M\n"
    s + push
  }

  def popI(seg: String, x: String): String = calcMLocationI(seg, x) + storeInMemory
  def pop(seg: String, x: String): String = calcMLocation(seg, x) + storeInMemory

  private def storeInMemory: String = {
    var s = "D=A\n"
    s += "@R13\n"
    s += "M=D\n" // temp @R12 = D + A
    s += pop // set popd value to D
    s += "@R13\n"
    s += "A=M\n"
    s + "M=D\n"
  }

  // set Memory location to A
  private def calcMLocation(seg: String, x: String): String = {
    var s = s"@$seg\n"
    s += "D=M\n"
    s += s"@$x\n"
    s + s"A=D+A\n"
  }

  //  set Memory location to A (immideate)
  private def calcMLocationI(seg: String, x: String): String = {
    var s = s"@$seg\n"
    s += "D=A\n"
    s += s"@$x\n"
    s + s"A=D+A\n"
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

    var s = popAndSetD_M
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
