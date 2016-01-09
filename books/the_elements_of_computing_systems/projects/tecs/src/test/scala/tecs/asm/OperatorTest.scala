package tecs.asm

import org.scalatest.FunSpec

class OperatorTest extends FunSpec {
  describe("AOprator")  {
    it("INT") {
      assert(AOperator("1024").asm ==  "0000010000000000")
      assert(AOperator("1").asm ==     "0000000000000001")
    }
  }

  describe("COprator")  {
    it("comp") {
      assert(COperator(None, "M", None).asm ==  "1111110000000000")
      assert(COperator(None, "1", None).asm ==  "1110111111000000")
    }

    it("dest = comp") {
      assert(COperator(Some("D"), "M", None).asm ==  "1111110000010000")
      assert(COperator(Some("M"), "0", None).asm ==  "1110101010001000")
      assert(COperator(Some("M"), "1", None).asm ==  "1110111111001000")
      assert(COperator(Some("M"), "D+M", None).asm ==  "1111000010001000")
      assert(COperator(Some("M"), "M+1", None).asm ==  "1111110111001000")
      assert(COperator(Some("D"), "D+A", None).asm ==  "1110000010010000")
    }

    it("comp;dest") {
      assert(COperator(None, "0", Some("JMP")).asm ==  "1110101010000111")
      assert(COperator(None, "D", Some("JGT")).asm ==  "1110001100000001")
    }
  }
}
