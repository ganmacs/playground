package tecs.asm

import org.scalatest.FunSpec

class EvaluatorTest extends FunSpec {
  describe("#call")  {
    val t = Translator(List("a", "(LOOP:01)", "b", "c"))
    assert(t.call == List("a", "b", "c"))
  }

  describe("#symbolTable") {
    val t = Translator(List("a", "(LOOP_0)", "b", "c"))
    assert(t.symbolTable == List(("LOOP_0", 1)))
  }
}
