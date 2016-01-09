package asm

import org.scalatest.FunSpec
import asm._

class ParserTest extends FunSpec {
  describe("A Operator") {
    describe("'@' INT")  {
      assert(parseLine("@123") == AOperator("123"))
      assert(parseLine("@0") == AOperator("0"))
    }

    describe("'@' VAR")  {
      assert(parseLine("@i") == AOperator("16"))

      describe("should be incremental address mapping and should ref") {
        val parser = new Parser
        parser.parse("@i")
        parser.parse("@k") match {
          case Right(x) => assert(x == AOperator("17"))
          case Left(x) => throw new Exception(x)
        }

        parser.parse("@i") match {
          case Right(x) => assert(x == AOperator("16"))
          case Left(x) => throw new Exception(x)
        }
      }
    }
  }

  describe("C Operator") {
    assert(parseLine("D") == COperator(None, "D", None))
    assert(parseLine("D=M") == COperator(Some("D"), "M", None))
    assert(parseLine("D=-1") == COperator(Some("D"), "-1", None))
    assert(parseLine("D=D+A") == COperator(Some("D"), "D+A", None))
  }

  def parseLine(in: String) = {
    val parser = new Parser
    parser.parse(in) match {
      case Right(x) => x
      case Left(x) => throw new Exception(x)
    }
  }
}
