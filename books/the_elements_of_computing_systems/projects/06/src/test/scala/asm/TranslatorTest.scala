package asm

import org.scalatest.FunSpec
import asm._

class EvaluatorTest extends FunSpec {
  describe("#call")  {
    val t = Translator(List("a", "(LOOP:01)", "b", "c"))
    assert(t.call == List(("a", 0), ("b", 1), ("c", 2)))
  }

  describe("#symbolTable") {
    val t = Translator(List("a", "(LOOP_0)", "b", "c"))
    assert(t.symbolTable == List(("LOOP_0", 1)))
  }
}
