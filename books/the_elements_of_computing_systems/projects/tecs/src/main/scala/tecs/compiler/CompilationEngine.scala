package tecs.compiler

class CompilationEngine(input: String) {
  lazy val tokenizer = new JackTokenizer(input)
  lazy val tokens = tkn2syntax(tokenizer.tokens)

  private def tkn2syntax(l : List[TKN]): List[Syntax] = l match {
    case KEYWORD(k)      :: Nil => List(S_keyword(k))
    case SYMBOL(k)       :: Nil => List(S_symbol(k))
    case IDENTIFIER(k)   :: Nil => List(S_ident(k))
    case INT_CONST(k)    :: Nil => List(S_intConst(k))
    case STRING_CONST(k) :: Nil => List(S_stringConst(k))
    case KEYWORD(k)      :: xs => S_keyword(k)     :: tkn2syntax(xs)
    case SYMBOL(k)       :: xs => S_symbol(k)      :: tkn2syntax(xs)
    case IDENTIFIER(k)   :: xs => S_ident(k)       :: tkn2syntax(xs)
    case INT_CONST(k)    :: xs => S_intConst(k)    :: tkn2syntax(xs)
    case STRING_CONST(k) :: xs => S_stringConst(k) :: tkn2syntax(xs)
  }

  def compile() = compileClass(tokens)

  //  "class" className "{" classVarDec* subroutineDec* "}"
  def compileClass(lst: List[Syntax]): Either[String, S_class] = tokens match {
    case S_keyword("class") :: (a@S_ident(_)) :: S_symbol("{") :: xs =>
      compileClassVarDecs(xs) match {
        case Right((cvds, xs)) =>
          compileSubroutines(xs) match {
            case Right((subroutine, xs)) => xs match {
              case S_symbol("}") :: Nil => Right(S_class(a, cvds, subroutine))
              case x => Left("class definition's } is not found\n" + x.toString)
            }
            case Left(x) => Left(x.toString)
          }
        case Left(x) => Left(x.toString)
      }
    case x => Left(x.toString)
  }

  def compileClassVarDecs(lst: List[Syntax]): Either[List[Syntax], (Option[List[S_classVarDec]], List[Syntax])] = compileClassVarDec(lst) match {
    case Right((cvd, xs)) => compileClassVarDecs(xs) match {
      case Right((Some(cvds), xs)) => Right((Some(cvd :: cvds), xs))
      case Right((None, xs)) => Right((Some(List(cvd)), xs))
      case Left(_) => Right((Some(List(cvd)), xs))
      case _ => Left(lst)
    }
    case Left(_) => Right((None, lst))
  }

  // ("static" | "field") type varName ("," varName)*  ";"
  def compileClassVarDec(lst: List[Syntax]): Either[String, (S_classVarDec, List[Syntax])] = lst match {
    case (a@(S_keyword("static") | S_keyword("field"))) :: xs => compileType(xs) match {
      case Right((typ, xs)) => compileVarNameList(xs) match {
        case Right((n, xs)) => xs match {
          case S_symbol(";") :: xs => Right((S_classVarDec(a.asInstanceOf[S_keyword], typ, n), xs))
          case x => Left(x.toString)
        }
        case Left(x) => Left(x.toString)
      }
      case Right(x) => Left(x.toString)
      case Left(x) => Left("Require Type in var dec in class\n" + x.toString)
    }
    case x => Left(x.toString)
  }

  def compileSubroutines(lst: List[Syntax]): Either[List[Syntax], (Option[List[S_subroutineDec]], List[Syntax])] = compileSubroutine(lst) match {
    case Right((sr, xs)) => compileSubroutines(xs) match  {
      case Right((Some(lst), xs)) => Right((Some(sr :: lst), xs))
      case Right((None, xs)) => Right((Some(List(sr)), xs))
      case Left(_) => Right((Some(List(sr)), xs))
      case _ => Left(lst)
    }
    case Left(_) => Right((None, lst))
  }

  // ('constructor' | 'function' | "method") ('void' | type) subroutineName "(" parameterList ")" subroutineBody
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

  //  ((type varName) (',' type varName)*)?
  def compileParametererList(lst: List[Syntax]): Either[String, (S_parameterList, List[Syntax])] = compileType(lst) match {
    case Right((typ, S_ident(vname) :: S_symbol(",") :: xs)) => compileParametererList(xs) match {
      case Right((S_parameterList(l), xs)) => Right((S_parameterList((typ, S_ident(vname)) :: l), xs))
      case Right(x) => Left(x.toString)
      case Left(x) => Left(x)
    }
    case Right((typ, S_ident(vname) :: xs)) => Right((S_parameterList(List((typ, S_ident(vname)))), xs))
    case Left(xs) => Right((S_parameterList(Nil), xs))
  }

  //  'var' type varName (',' varName)* ";"
  def compileVarDec(lst: List[Syntax]): Either[List[Syntax], (S_varDec, List[Syntax])] = lst match {
    case S_keyword("var") :: xs => compileType(xs) match {
      case Right((typ, xs)) => compileVarNameList(xs) match {
        case Right((nameList, xs)) => xs match {
          case S_symbol(";") :: xs => Right((S_varDec(typ, nameList), xs))
          case x => Left(lst)
        }
        case Left(_) => Left(lst)
      }
    }
    case x => Left(lst)
  }

  // statement*
  def compileStatements(lst: List[Syntax]): Either[List[Syntax], (S_statements, List[Syntax])] = compileStatement(lst) match {
    case Right((s, xs)) => compileStatements(xs) match {
      case Right((S_statements(Some(ss)), xs)) => Right((S_statements(Some(s :: ss)), xs))
      case Right((S_statements(None), xs)) => Right((S_statements(Some(List(s))), xs))
      case Left(lst) => Right((S_statements(Some(List(s))), xs))
      case _ => Left(lst)
    }
    case Left(_) => Right((S_statements(None), lst))
  }

  // def compileStatements(lst: List[Syntax]): Either[String, (List[S_statement], List[Syntax])] = compileStatement(lst) match {
  private def compileStatement(lst: List[Syntax]): Either[List[Syntax], (S_statement, List[Syntax])] = compileLet(lst) match {
    case Right((l, xs)) => Right((S_statement(l), xs))
    case _ => compileIf(lst) match  {
      case Right((i, xs)) => Right((S_statement(i), xs))
      case _ => compileWhile(lst) match {
        case Right((w, xs)) => Right((S_statement(w), xs))
        case _ => compileDo(lst) match {
          case Right((d, xs)) => Right((S_statement(d), xs))
          case _ => compileReturn(lst) match {
            case Right((r, xs)) => Right((S_statement(r), xs))
            case _ => Left(lst)
          }
        }
      }
    }
  }


  // 'let' varname ('['  expression ']')? '=' expression ';'
  def compileLet(lst: List[Syntax]): Either[List[Syntax], (S_letStatement, List[Syntax])] = lst match  {
    case S_keyword("let") :: S_ident(vname) :: S_symbol("[") :: xs => compileExpression(xs) match {
      case Right((e, S_symbol("]") :: S_symbol("=") :: xs)) => compileExpression(xs) match {
        case Right((e2, S_symbol(";") :: xs)) => Right((S_letStatement(S_ident(vname), Some(e), e2), xs))
        case _ => Left(lst)
      }
      case _ => Left(lst)
    }
    case S_keyword("let") :: S_ident(vname) :: S_symbol("=") :: xs=> compileExpression(xs) match {
      case Right((e2, S_symbol(";") :: xs)) => Right((S_letStatement(S_ident(vname), None, e2), xs))
      case _ => Left(lst)
    }
  }

  // 'if' "(" expression ")" "{" statements "}" ("else" "{" statements"}")?
  def compileIf(lst: List[Syntax]): Either[List[Syntax], (S_if, List[Syntax])] = lst match {
    case S_keyword("if") :: S_symbol("(") :: xs => compileExpression(xs) match {
      case Right((ex, xs)) => xs match {
        case S_symbol(")") :: S_symbol("{") :: xs => compileStatements(xs) match {
          case Right((ss, xs)) => xs match {
            case S_symbol("}") :: S_keyword("else") :: S_symbol("{") :: xs => compileStatements(xs) match {
              case Right((ss2, S_symbol("}") :: xs))  => Right(((S_if(ex, ss, Some(ss2))), xs))
              case _ => Left(lst)
            }
            case S_symbol("}") :: xs => Right((S_if(ex, ss, None), xs))
            case _ => Left(lst)
          }
          case _ => Left(lst)
        }
        case _ => Left(lst)
      }
      case _ => Left(lst)
    }
    case _ => Left(lst)
  }

  //  'while' '(' expression ')' "{" statemetns "}"
  def compileWhile(lst: List[Syntax]): Either[List[Syntax], (S_while, List[Syntax])] = lst match {
    case S_keyword("while") :: S_symbol("(") :: xs => compileExpression(xs) match {
      case Right((e, xs)) => xs match {
        case S_symbol(")") :: S_symbol("{") :: xs => compileStatements(xs) match {
          case Right((ss, (S_symbol("}") :: xs))) => Right((S_while(e, ss), xs))
          case Left(_) => Left(lst)
        }
        case _ => Left(lst)
      }
      case Left(_) => Left(lst)
    }
  }

  // "do" subroutineCall ";"
  def compileDo(lst: List[Syntax]): Either[List[Syntax], (S_do, List[Syntax])] = lst match {
    case S_symbol("do") :: xs => compileSubroutineCall(xs) match {
      case Right((sr, xs)) => xs match  {
        case S_symbol(";") :: xs => Right((S_do(sr), xs))
        case _ => Left(lst)
      }
      case _ => Left(lst)
    }
    case _ => Left(lst)
  }

  // 'return' expression? ";"
  def compileReturn(lst: List[Syntax]): Either[List[Syntax], (S_return, List[Syntax])] = lst match {
    case S_symbol("return") :: xs => compileExpression(xs) match {
      case Right((e, xs)) => xs match {
        case S_symbol(";") :: xs => Right((S_return(Some(e)), xs))
      }
      case Left(S_symbol(";") :: xs) => Right((S_return(None), xs))
      case _ => Left(lst)
    }
    case _ => Left(lst)
  }

  // ----- Exprssion

  // temr (op term)*
  def compileExpression(lst: List[Syntax]): Either[List[Syntax], (S_expression, List[Syntax])] = compileTerm(lst) match {
    case Right((t, xs)) => compileOp(xs) match {
      case Right((op, xs)) => compileExpression(xs) match {
        case Right((S_expression(tr, None), xs)) => Right((S_expression(t, Some(List(S_rightTerm(op, tr)))), xs))
        case Right((S_expression(tr, Some(x)), xs)) => Right((S_expression(t, Some(S_rightTerm(op, tr) :: x)), xs))
        case _ => Left(lst)
      }
      case Left(xs) => Right((S_expression(t, None), xs))
    }
    case _ => Left(lst)
  }

  // subroutineCall | unaryOp term | keywordcosnt | integerConst | stringConst | varName | varName "[" expression "]"
  // | "(" expression ")"
  def compileTerm(lst: List[Syntax]): Either[List[Syntax], (S_term, List[Syntax])] = compileSubroutineCall(lst) match {
    case Right((sc, xs)) => Right((S_term(sc), xs))
    case _ => compileTermWithuOp(lst) match {
      case Right((c, xs)) => Right((S_term(c), xs))
      case _ => compileKeywodConst(lst) match {
        case Right((k, xs)) => Right((S_term(k), xs))
        case _ => lst match {
          case S_intConst(x) :: xs => Right((S_term(S_intConst(x)),  xs))
          case S_stringConst(x) :: xs => Right((S_term(S_stringConst(x)),  xs))
          case S_ident(x) :: S_symbol("[") :: xs => compileExpression(xs) match {
            case Right((ex, xs)) => xs match {
              case S_symbol("]") :: xs => Right((S_term(ex), xs))
              case _ => Left(lst)
            }
            case _ => Left(lst)
          }
          case S_ident(x) :: xs => Right((S_term(S_ident(x)),  xs))
          case S_symbol("(") :: xs => compileExpression(xs) match {
            case Right((ex, xs)) => xs match {
              case S_symbol(")") :: xs => Right((S_term(ex), xs))
              case _ => Left(lst)
            }
            case _ => Left(lst)
          }
          case _ => Left(lst)
        }
      }
    }
  }

  // subroutineName "(" expressionList ")" | (className | varName) '.' subroutineName '(' expressionList ")"
  private def compileSubroutineCall(lst: List[Syntax]): Either[List[Syntax], (S_subroutineCall, List[Syntax])] = lst match {
    case S_ident(s) :: S_symbol("(") :: xs => compileExpressionList(xs) match {
      case Right((el, xs)) => xs match {
        case S_symbol(")") :: xs => Right((S_subroutineCall(S_ident(s), None, el), xs))
        case _ => Left(lst)
      }
      case Left(_) => Left(lst)
    }
    case S_ident(s) :: S_symbol(".") :: S_ident(r) :: S_symbol("(") :: xs => compileExpressionList(xs) match {
      case Right((el, xs)) => xs match {
        case S_symbol(")") :: xs => Right((S_subroutineCall(S_ident(s), Some(S_ident(r)), el), xs))
        case _ => Left(lst)
      }
      case _ => Left(lst)
    }
    case _ => Left(lst)
  }

  private def compileTermWithuOp(lst: List[Syntax]): Either[List[Syntax], (S_termWithUOp, List[Syntax])] = compileUnaryOp(lst) match {
    case Right((u, xs)) => compileTerm(xs) match {
      case Right((t, xs)) => Right((S_termWithUOp(u, t), xs))
      case _ => Left(lst)
    }
    case _ => Left(lst)
  }

  //  (expression (',' expression)*)?
  def compileExpressionList(lst: List[Syntax]): Either[List[Syntax], (S_expressionList, List[Syntax])] = compileExpression(lst) match {
    case Right((ex, S_symbol(",") :: xs)) => compileExpressionList(xs) match {
      case Right((S_expressionList(Some(el)), xs)) => Right((S_expressionList(Some(ex :: el)), xs))
      case Left(_) => Left(lst)
    }
    case Right((ex, xs)) => Right((S_expressionList(Some(List(ex))), xs))
    case Left(xs) => Right((S_expressionList(None), xs))
    case _ => Left(lst)
  }

  // varName ("," varName)*
  def compileVarNameList(lst: List[Syntax]): Either[List[Syntax], (S_varNameList, List[Syntax])] = lst match {
    case S_ident(s1) :: S_symbol(",") :: xs => compileVarNameList(xs) match {
      case Right((S_varNameList(l), xs)) => Right((S_varNameList(S_ident(s1) :: l), xs))
      case _ => Left(lst)
    }
    case S_ident(s1) :: xs => Right((S_varNameList(List(S_ident(s1))), xs))
    case _ => Left(lst)
  }

  // "+" | "-" | "*" | "/" | "&" | "|" | "<"| ">" | "="
  private def compileOp(lst: List[Syntax]): Either[List[Syntax], (S_op, List[Syntax])] = lst match {
    case S_symbol("+") :: xs => Right((S_op("+"), xs))
    case S_symbol("-") :: xs => Right((S_op("-"), xs))
    case S_symbol("*") :: xs => Right((S_op("*"), xs))
    case S_symbol("/") :: xs => Right((S_op("/"), xs))
    case S_symbol("&") :: xs => Right((S_op("&"), xs))
    case S_symbol("|") :: xs => Right((S_op("|"), xs))
    case S_symbol("<") :: xs => Right((S_op("<"), xs))
    case S_symbol(">") :: xs => Right((S_op(">"), xs))
    case S_symbol("=") :: xs => Right((S_op("="), xs))
    case _ => Left(lst)
  }

  // "-" | "~"
  private def compileUnaryOp(lst: List[Syntax]): Either[List[Syntax], (S_unaryOp, List[Syntax])] = lst match {
    case S_symbol("-") :: xs => Right((S_unaryOp("-"), xs))
    case S_symbol("~") :: xs => Right((S_unaryOp("~"), xs))
    case _ => Left(lst)
  }

  // "true" | "false" | "null" | "this"
  private def compileKeywodConst(lst: List[Syntax]): Either[List[Syntax], (S_keywordConst, List[Syntax])] = lst match {
    case S_ident("true")  :: xs => Right((S_keywordConst("true"), xs))
    case S_ident("false") :: xs => Right((S_keywordConst("false"), xs))
    case S_ident("null")  :: xs => Right((S_keywordConst("null"), xs))
    case S_ident("this")  :: xs => Right((S_keywordConst("this"), xs))
    case _ => Left(lst)
  }

  //  'int' | 'char' | 'boolean' | className
  private def compileType(lst: List[Syntax]): Either[List[Syntax], (S_type, List[Syntax])] = lst match {
    case S_keyword("int")     :: xs => Right((S_type("int"), xs))
    case S_keyword("char")    :: xs => Right((S_type("char"), xs))
    case S_keyword("boolean") :: xs => Right((S_type("boolean"), xs))
    case S_ident(a)           :: xs => Right((S_type(a), xs))
    case _ => Left(lst)
  }
}
