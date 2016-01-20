package tecs.compiler

class CompilationEngine(input: String) {
  lazy val tokenizer = new JackTokenizer(input)
  lazy val tokens = tkn2syntax(tokenizer.tokens)

  private def tkn2syntax(l : List[TKN]): List[Syntax] = l match {
    case KEYWORD(k)      :: List() => List(S_keyword(k))
    case SYMBOL(k)       :: List() => List(S_symbol(k))
    case IDENTIFIER(k)   :: List() => List(S_ident(k))
    case INT_CONST(k)    :: List() => List(S_intConst(k))
    case STRING_CONST(k) :: List() => List(S_stringConst(k))
    case KEYWORD(k)      :: xs => S_keyword(k)     :: tkn2syntax(xs)
    case SYMBOL(k)       :: xs => S_symbol(k)      :: tkn2syntax(xs)
    case IDENTIFIER(k)   :: xs => S_ident(k)       :: tkn2syntax(xs)
    case INT_CONST(k)    :: xs => S_intConst(k)    :: tkn2syntax(xs)
    case STRING_CONST(k) :: xs => S_stringConst(k) :: tkn2syntax(xs)
  }

  def compile() = {

  }

  def compileClass()(lst: List[Syntax]): S_class = tokens match {
    case S_keyword("class") :: (a@S_ident(_)) :: S_symbol("{") :: xs => compileClassVarDec(xs) match {
      case (b@S_classVarDec(_, _, _, _)) :: xs => compileSubroutine(xs) match {
        case (c@S_subroutineDec(_)) :: xs => xs match {
          case S_symbol("}") :: Nil =>  S_class(a, b, c)
          case x =>  throw new Exception(x.toString)
        }
      }
    }
  }

  def compileClassVarDec(lst: List[Syntax]): List[Syntax] = lst match {
    case
  }


  def compileSubroutine(lst: List[Syntax]): List[Syntax] = List()
  def compileParametererList(lst: List[Syntax]): List[Syntax] = List()
  def compileVarDec(lst: List[Syntax]): List[Syntax] = List()
  def compileStatements(lst: List[Syntax]): List[Syntax] = List()
  def compileDo(lst: List[Syntax]): List[Syntax] = List()
  def compileLet(lst: List[Syntax]): List[Syntax] = List()
  def compileReturn(lst: List[Syntax]): List[Syntax] = List()
  def compileIf(lst: List[Syntax]): List[Syntax] = List()
  def compileExpression(lst: List[Syntax]) : List[Syntax] = List()
  def compileTerm(lst: List[Syntax]): List[Syntax] = List()
  def compileExpressionList(lst: List[Syntax]): List[Syntax] = List()
}
