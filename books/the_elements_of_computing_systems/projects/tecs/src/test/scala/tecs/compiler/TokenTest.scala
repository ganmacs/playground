package tecs.compiler

import org.scalatest.FunSpec

class TokenTest extends FunSpec {

  describe("KEYWORD") {
    it ("returns KEYWORD") {
      assert(Token.build("class") == KEYWORD("class"))
    }

    it ("returns SYMBOL") {
      assert(Token.build("{") == SYMBOL("{"))
      assert(Token.build("+") == SYMBOL("+"))
      assert(Token.build("&") == SYMBOL("&"))
    }

    it ("returns INT_CONST") {
      assert(Token.build("19273") == INT_CONST("19273"))
      assert(Token.build("0") == INT_CONST("0"))
    }

    it ("returns IDENTIFIER") {
      assert(Token.build("a") == IDENTIFIER("a"))
      assert(Token.build("a0") == IDENTIFIER("a0"))
      assert(Token.build("_a0") == IDENTIFIER("_a0"))
    }

    // it ("returns STRING_CONST") {
    //   assert(Token.build("class") == KEYWORD("class"))
    // }
  }
}
