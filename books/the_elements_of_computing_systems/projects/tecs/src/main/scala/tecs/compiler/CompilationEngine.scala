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

  def compileClass(lst: List[Syntax]): Either[String, S_class] = tokens match {
    case S_keyword("class") :: (a@S_ident(_)) :: S_symbol("{") :: xs =>
      compileClassVarDec(xs) match {
        case Right((clasVarDec, xs)) =>
          compileSubroutine(xs) match {
            case Right((subroutine, xs)) => xs match {
              case S_symbol("}") :: Nil => Right(S_class(a, clasVarDec, subroutine))
              case x => Left("class definition's } is not found\n" + x.toString)
            }
            case Left(x) => Left(x)
          }
        case Left(x) => Left(x)
      }
    case x => Left(x.toString)
  }

  def compileClassVarDec(lst: List[Syntax]): Either[String, (S_classVarDec, List[Syntax])] = lst match {
    case (a@(S_keyword(_) | S_keyword(_))) :: xs => compileType(xs) match {
      case Right((typ, S_ident(k) :: xs)) => compileVarNames(0, xs) match {
        case (i, l) => {
          val s = l.take(i)
          l.drop(i) match {
            case S_symbol(";") :: xs => Right((S_classVarDec(a.asInstanceOf[S_keyword], typ, S_ident(k) :: l), xs))
            case x => Left(x.toString)
          }
        }
      }
      case Right(x) => Left(x.toString)
      case Left(x) => Left("Require Type in var dec in class\n" + x.toString)
    }
    case x => Left(x.toString)
  }

  def compileSubroutine(lst: List[Syntax]): Either[String, (S_subroutineDec, List[Syntax])] = lst match {
    case (a@(S_keyword("constructor") | S_keyword("function") | S_keyword("method"))) :: xs => xs match {
      case xs => compileType(xs) match {
        case Right((typ, S_ident(subname) :: S_symbol("(") :: xs)) => compileParametererList(xs) match {
          // case Right((S_parameterList(l), S_symbol(")") :: xs)) =>
          case Left(x) => Left(x)
        }
        case Left(S_keyword("void") :: S_ident(subname) ::  S_symbol("(") :: xs) => compileParametererList(xs) match {
          // case Right((S_parameterList(l), S_symbol(")") :: xs)) =>
          case Left(x) => Left(x)
        }
        case Left(x) => Left(x.toString())
      }
    }
    case x => Left(x.toString)
  }

  def compileParametererList(lst: List[Syntax]): Either[String, (S_parameterList, List[Syntax])] = compileType(lst) match {
    case Right((typ, S_ident(vname) :: S_symbol(",") :: xs)) => compileParametererList(xs) match {
      case Right((S_parameterList(l), xs)) => Right((S_parameterList((typ, S_ident(vname)) :: l), xs))
      case Left(x) => Left(x)
    }
    case Right((typ, S_ident(vname) :: xs)) => Right((S_parameterList(List((typ, S_ident(vname)))), xs))
    case Left(xs) => Right((S_parameterList(Nil), xs))
  }

  def compileVarDec(lst: List[Syntax]): List[Syntax] = List()
  def compileStatements(lst: List[Syntax]): List[Syntax] = List()
  def compileDo(lst: List[Syntax]): List[Syntax] = List()
  def compileLet(lst: List[Syntax]): List[Syntax] = List()
  def compileReturn(lst: List[Syntax]): List[Syntax] = List()
  def compileIf(lst: List[Syntax]): List[Syntax] = List()
  def compileExpression(lst: List[Syntax]) : List[Syntax] = List()
  def compileTerm(lst: List[Syntax]): List[Syntax] = List()
  def compileExpressionList(lst: List[Syntax]): List[Syntax] = List()


  // def compileSubRoutineBody(i: Int, lst: List[Syntax]): (Int, List[Syntax]) = lst match {

  // }

  def compileVarNames(i: Int, lst: List[Syntax]): (Int, List[Syntax]) = lst match {
    case S_symbol(",") :: (s@S_symbol(_)) :: xs => {
      compileVarNames(i + 1, xs) match { case (k, ss) =>  (k, s :: ss) }
    }
    case x => (i, x)
  }

  private def compileType(lst: List[Syntax]): Either[List[Syntax], (S_type, List[Syntax])] = lst match {
    case S_keyword("int")     :: xs => Right((S_type("int"), xs))
    case S_keyword("char")    :: xs => Right((S_type("char"), xs))
    case S_keyword("boolean") :: xs => Right((S_type("boolean"), xs))
    case S_ident(a)           :: xs => Right((S_type(a), xs))
    case _ => Left(lst)
  }
}
