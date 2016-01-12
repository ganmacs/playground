package tecs.vm

object Asm {
  private val counter = new {
    private var i = -1
    def inc: String = { this.i += 1; this.i.toString }
  }

  var filename = "filename"
  val sp = "@SP\n"
  val incSP: String = sp + "M=M+1\n"
  val decSP: String = sp + "M=M-1\n"

  // set SP ptr value to M
  val ptrSP: String = sp + "A=M\n"
  val decAndptrSP: String = decSP + "A=M\n"

  //  pop x and y, then set D = y, M = x
  private val popAndSetD_M = pop + decAndptrSP

  def assignPtrSP(v: String) = ptrSP + s"M=$v\n"

  // push D register value to SP postion
  def push: String = ptrSP + "M=D\n" + incSP

  // poped value to D register
  def pop: String = decAndptrSP + "D=M\n"

  def pushC(x: String): String = {
    val s = new StringBuilder
    s.append(loadRamAddress(x))
    s.append(push)
    s.toString
  }

  def push(seg: String, x: String): String = {
    val s = new StringBuilder
    s.append(calcMLocation(seg, x))
    s.append("D=M\n")
    s.append(push)
    s.toString
  }

  def pushS(x: String): String = {
    val s = new StringBuilder
    s.append(loadRamAddress(s"$filename.$x"))
    s.append(push)
    s.toString
  }

  def pushI(seg: String, x: String): String = {
    val s = new StringBuilder
    s.append(calcMLocationI(seg, x))
    s.append("D=M\n")
    s.append(push)
    s.toString
  }

  def pop(seg: String, x: String): String = calcMLocation(seg, x) + storeInMemory
  def popI(seg: String, x: String): String = calcMLocationI(seg, x) + storeInMemory
  def popS(x: String): String = s"@$this.filename.$x\n" + "M=D\n" +storeInMemory

  def add: String = popAndSetD_M + "M=M+D\n" + incSP
  def sub: String = popAndSetD_M + "M=M-D\n" + incSP

  def and: String = popAndSetD_M + "M=M&D\n" + incSP
  def or: String = popAndSetD_M + "M=M|D\n" + incSP

  def neg: String = pop + "M=-D\n" + incSP
  def not: String = pop + "M=!D\n" + incSP

  def label(v: String): String = s"($v$$$filename)\n"
  def goto(v: String): String = s"@$v\n" + "0; JMP\n"
  def ifgoto(v: String): String = {
    val s = new StringBuilder
    s.append(pop)
    s.append(s"@$v\n")
    s.append("D; JGT\n")
    s.toString
  }

  def eq: String = compareWith("JEQ")
  def gt: String = compareWith("JGT")
  def lt: String = compareWith("JLT")

  private def compareWith(cond: String): String = {
    val n = counter.inc

    val s = new StringBuilder
    s.append(popAndSetD_M)
    s.append("D=M-D\n")   // x - y
    s.append(s"@COMP_LABEL_$n\n")
    s.append(s"D; $cond\n")
    s.append(assignPtrSP("0"))
    s.append(s"@COMP_LABEL_END_$n\n")
    s.append("0; JMP\n")
    s.append(label(s"COMP_LABEL_$n"))
    s.append(assignPtrSP("-1"))
    s.append(label(s"COMP_LABEL_END_$n"))
    s.append(incSP)
    s.toString
  }

  def function(name: String, localnum: String): String = {
    val s = new StringBuilder
    s.append(label(name))
    s.append("D=0\n")
      (0 to Integer.parseInt(localnum)).foreach { e =>
        s.append(push)
      }
    s.toString()
  }

  def returnExpr: String = {
    val s = new StringBuilder
    s.append(loadRamValue("LCL"))
    s.append(storeValueToRam("R13"))

    s.append(storeToRAMWithIndex("R14", "5")) // RET = *(FRAME - 5) (R14 = RET)

    s.append(pop)
    s.append("@ARG\n")
    s.append("A=M\n") // *ARG
    s.append("M=D\n") // *ARG = pop

    s.append(loadRamValue("ARG"))
    s.append(s"@1\n")
    s.append("D=D+A\n")
    s.append(storeValueToRam("SP")) //  SP = ARG + 1

    s.append(loadRamValue("R13"))
    s.append(storeToRAMWithIndex("THAT", "1"))

    s.append(loadRamValue("R13"))
    s.append(storeToRAMWithIndex("THIS", "2"))

    s.append(loadRamValue("R13"))
    s.append(storeToRAMWithIndex("ARG", "3"))

    s.append(loadRamValue("R13"))
    s.append(storeToRAMWithIndex("LCL", "4"))

    s.append("@R14\n")
    s.append("A=M\n")
    s.append("0; JMP\n") // goto ret

    s.toString
  }

  // ram = *(D + index)
  private def storeToRAMWithIndex(ram: String, i: String): String = {
    val s = new StringBuilder
    s.append(s"@$i\n")
    s.append("D=D-A\n")
    s.append("A=D\n")
    s.append("D=M\n") // D = *(ram - i)
    s.append(storeValueToRam(ram))
    s.toString
  }

  private def storeInMemory: String = {
    val s = new StringBuilder
    s.append("D=A\n")
    s.append(storeValueToRam("R13"))
    s.append(pop)     // set popd value to D
    s.append("@R13\n")
    s.append("A=M\n")
    s.append("M=D\n")
    s.toString
  }

  // set Memory location to A
  private def calcMLocation(seg: String, x: String): String = {
    val s = new StringBuilder
    s.append(loadRamValue(seg))
    s.append(s"@$x\n")
    s.append(s"A=D+A\n")
    s.toString
  }

  //  set Memory location to A (immideate)
  private def calcMLocationI(seg: String, x: String): String = {
    val s = new StringBuilder
    s.append(loadRamAddress(seg))
    s.append(s"@$x\n")
    s.append(s"A=D+A\n")
    s.toString
  }

  // load ram VALUE to D register
  private def loadRamValue(ram: String) = s"@$ram\n" + "D=M\n"

  // load ram ADREESS to D register
  private def loadRamAddress(ram: String) = s"@$ram\n" + "D=A\n"

  // Store D register value to ram
  private def storeValueToRam(ram: String) = s"@$ram\n" + "M=D\n"
}
