package tecs.compiler

class CompilationEngine(input: String, converter: Converter) {
  lazy val tokenizer = new JackTokenizer(input)
  lazy val tokens = tkn2syntax(tokenizer.tokens)

  private def tkn2syntax(l : List[TKN]): List[Syntax] = l match {
    case KEYWORD(k)      :: xs => S_keyword(k)     :: tkn2syntax(xs)
    case SYMBOL(k)       :: xs => S_symbol(k)      :: tkn2syntax(xs)
    case IDENTIFIER(k)   :: xs => S_ident(k)       :: tkn2syntax(xs)
    case INT_CONST(k)    :: xs => S_intConst(k)    :: tkn2syntax(xs)
    case STRING_CONST(k) :: xs => S_stringConst(k) :: tkn2syntax(xs)
    case Nil => Nil
  }

  def compile(): Seq[String] = compileClass(tokens) match {
    case Right(c) => converter.run(c)
    case Left(c) => throw new Exception(c)
  }

  //  "class" className "{" classVarDec* subroutineDec* "}"
  def compileClass(lst: Seq[Syntax]): Either[String, S_class] = tokens match {
    case S_keyword("class") :: (a@S_ident(_)) :: S_symbol("{") :: xs => compileClassVarDecs(xs) match {
      case Right((cvds, xs)) => compileSubroutines(xs) match {
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

  def compileClassVarDecs(lst: Seq[Syntax]): Either[Seq[Syntax], (Option[Seq[S_classVarDec]], Seq[Syntax])] = compileClassVarDec(lst) match {
    case Right((cvd, xs)) => compileClassVarDecs(xs) match {
      case Right((Some(cvds), xs)) => Right((Some(cvd +: cvds), xs))
      case Right((None, xs)) => Right((Some(Seq(cvd)), xs))
      case Left(_) => Right((Some(Seq(cvd)), xs))
      case _ => Left(lst)
    }
    case Left(_) => Right((None, lst))
  }

  // ("static" | "field") type varName ("," varName)*  ";"
  def compileClassVarDec(lst: Seq[Syntax]): Either[String, (S_classVarDec, Seq[Syntax])] = lst match {
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

  def compileSubroutines(lst: Seq[Syntax]): Either[Seq[Syntax], (Option[Seq[S_subroutineDec]], Seq[Syntax])] = compileSubroutine(lst) match {
    case Right((sr, xs)) => compileSubroutines(xs) match  {
      case Right((Some(lst), xs)) => Right((Some(sr +: lst), xs))
      case Right((None, xs)) => Right((Some(Seq(sr)), xs))
      case Left(_) => Right((Some(Seq(sr)), xs))
      case _ => Left(lst)
    }
    case Left(_) => Right((None, lst))
  }

  // ('constructor' | 'function' | "method") ('void' | type) subroutineName "(" parameterList ")" subroutineBody
  def compileSubroutine(lst: Seq[Syntax]): Either[Seq[Syntax], (S_subroutineDec, Seq[Syntax])] = lst match {
    case (a@(S_keyword("constructor") | S_keyword("function") | S_keyword("method"))) :: xs => compileType(xs) match {
      case Right((typ, S_ident(name) :: S_symbol("(") :: xs)) => compileParametererList(xs) match {
        case Right((l, S_symbol(")") :: xs)) => compileSubroutineBody(xs) match {
          case Right((body, xs)) => Right((S_subroutineDec(a.asInstanceOf[S_keyword], typ, S_ident(name), l, body), xs))
          case _ => Left(lst)
        }
        case _ => Left(lst)
      }
      case Left(S_keyword("void") :: S_ident(name) ::  S_symbol("(") :: xs) => compileParametererList(xs) match {
        case Right((l, S_symbol(")") :: xs)) => compileSubroutineBody(xs) match {
          case Right((body, xs)) => Right((S_subroutineDec(a.asInstanceOf[S_keyword], S_type(S_keyword("void")), S_ident(name), l, body), xs))
          case _ => Left(lst)
        }
        case _ => Left(lst)
      }
      case _ => Left(lst)
    }
    case _ => Left(lst)
  }

  // "{" varDec* statements "}"
  private def compileSubroutineBody(lst: Seq[Syntax]): Either[Seq[Syntax], (S_subroutineBody, Seq[Syntax])] = lst match {
    case S_symbol("{") :: xs => compileVarDecs(xs) match {
      case Right((decs, xs)) => compileStatements(xs) match {
        case Right((ss, S_symbol("}") :: xs)) => Right((S_subroutineBody(decs, ss), xs))
        case _ => Left(lst)
      }
      case _ => Left(lst)
    }
    case _ => Left(lst)
  }

  //  ((type varName) (',' type varName)*)?
  def compileParametererList(lst: Seq[Syntax]): Either[String, (S_parameterList, Seq[Syntax])] = compileType(lst) match {
    case Right((typ, S_ident(vname) :: S_symbol(",") :: xs)) => compileParametererList(xs) match {
      case Right((S_parameterList(Some(l)), xs)) => Right((S_parameterList(Some((typ, S_ident(vname)) +: l)), xs))
      case Right((S_parameterList(None), xs)) => Right((S_parameterList(Some(Seq((typ, S_ident(vname))))), xs))
      case Right(x) => Left(x.toString)
      case Left(x) => Left(x)
    }
    case Right((typ, S_ident(vname) :: xs)) => Right((S_parameterList(Some(Seq((typ, S_ident(vname))))), xs))
    case Left(_) => Right((S_parameterList(None), lst))
  }

  def compileVarDecs(lst: Seq[Syntax]): Either[Seq[Syntax], (Option[Seq[S_varDec]], Seq[Syntax])] = compileVarDec(lst) match {
    case Right((v, xs)) => compileVarDecs(xs) match {
      case Right((Some(ls), xs)) => Right((Some(v +: ls), xs))
      case Right((None, xs)) => Right((Some(Seq(v)), xs))
      case Left(_) => Right((Some(Seq(v)), xs))
    }
    case Left(_) => Right((None, lst))
  }

  //  'var' type varName (',' varName)* ";"
  def compileVarDec(lst: Seq[Syntax]): Either[Seq[Syntax], (S_varDec, Seq[Syntax])] = lst match {
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
  def compileStatements(lst: Seq[Syntax]): Either[Seq[Syntax], (S_statements, Seq[Syntax])] = compileStatement(lst) match {
    case Right((s, xs)) => compileStatements(xs) match {
      case Right((S_statements(Some(ss)), xs)) => Right((S_statements(Some(s +: ss)), xs))
      case Right((S_statements(None), xs)) => Right((S_statements(Some(Seq(s))), xs))
      case Left(lst) => Right((S_statements(Some(Seq(s))), xs))
      case _ => Left(lst)
    }
    case Left(_) => Right((S_statements(None), lst))
  }

  private def compileStatement(lst: Seq[Syntax]): Either[Seq[Syntax], (S_statement, Seq[Syntax])] = compileLet(lst) match {
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
  def compileLet(lst: Seq[Syntax]): Either[Seq[Syntax], (S_letStatement, Seq[Syntax])] = lst match  {
    case S_keyword("let") :: S_ident(vname) :: S_symbol("[") :: xs => compileExpression(xs) match {
      case Right((e, S_symbol("]") :: S_symbol("=") :: xs)) => compileExpression(xs) match {
        case Right((e2, S_symbol(";") :: xs)) => Right((S_letStatement(S_ident(vname), Some(e), e2), xs))
        case _ => Left(lst)
      }
      case _ => Left(lst)
    }
    case S_keyword("let") :: S_ident(vname) :: S_symbol("=") :: xs => compileExpression(xs) match {
      case Right((e2, S_symbol(";") :: xs)) => Right((S_letStatement(S_ident(vname), None, e2), xs))
      case _ => Left(lst)
    }
    case _ => Left(lst)
  }

  // 'if' "(" expression ")" "{" statements "}" ("else" "{" statements"}")?
  def compileIf(lst: Seq[Syntax]): Either[Seq[Syntax], (S_if, Seq[Syntax])] = lst match {
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
  def compileWhile(lst: Seq[Syntax]): Either[Seq[Syntax], (S_while, Seq[Syntax])] = lst match {
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
    case _ => Left(lst)
  }

  // "do" subroutineCall ";"
  def compileDo(lst: Seq[Syntax]): Either[Seq[Syntax], (S_do, Seq[Syntax])] = lst match {
    case S_keyword("do") :: xs => compileSubroutineCall(xs) match {
      case Right((sr, xs)) => xs match  {
        case S_symbol(";") :: xs => Right((S_do(sr), xs))
        case _ => Left(lst)
      }
      case _ => Left(lst)
    }
    case _ => Left(lst)
  }

  // 'return' expression? ";"
  def compileReturn(lst: Seq[Syntax]): Either[Seq[Syntax], (S_return, Seq[Syntax])] = lst match {
    case S_keyword("return") :: xs => compileExpression(xs) match {
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
  def compileExpression(lst: Seq[Syntax]): Either[Seq[Syntax], (S_expression, Seq[Syntax])] = compileTerm(lst) match {
    case Right((t, xs)) => compileOp(xs) match {
      case Right((op, xs)) => compileExpression(xs) match {
        case Right((S_expression(tr, None), xs)) => Right((S_expression(t, Some(Seq(S_rightTerm(op, tr)))), xs))
        case Right((S_expression(tr, Some(x)), xs)) => Right((S_expression(t, Some(S_rightTerm(op, tr) +: x)), xs))
        case _ => Left(lst)
      }
      case Left(xs) => Right((S_expression(t, None), xs))
    }
    case _ => Left(lst)
  }

  // subroutineCall | unaryOp term | keywordcosnt | integerConst | stringConst | varName | varName "[" expression "]"
  // | "(" expression ")"
  def compileTerm(lst: Seq[Syntax]): Either[Seq[Syntax], (S_term, Seq[Syntax])] = compileSubroutineCall(lst) match {
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
              case S_symbol("]") :: xs => Right((S_term(S_accessAry(S_ident(x), ex)), xs))
              case _ => Left(lst)
            }
            case _ => Left(lst)
          }
          case S_ident(x) :: xs => Right((S_term(S_ident(x)),  xs))
          case S_keyword(x) :: xs => Right((S_term(S_keyword(x)),  xs))
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
  private def compileSubroutineCall(lst: Seq[Syntax]): Either[Seq[Syntax], (S_subroutineCall, Seq[Syntax])] = lst match {
    case S_ident(s) :: S_symbol("(") :: xs => compileExpressionList(xs) match {
      case Right((el, xs)) => xs match {
        case S_symbol(")") :: xs => Right((S_subroutineCall(S_ident(s), None, el), xs))
        case _ => Left(lst)
      }
      case Left(_) => Left(lst)
    }
    case S_ident(s) :: S_symbol(".") :: S_ident(r) :: S_symbol("(") :: xs => compileExpressionList(xs) match {
      case Right((el, xs)) => xs match {
        case S_symbol(")") :: xs => Right((S_subroutineCall(S_ident(r), Some(S_ident(s)), el), xs))
        case _ => Left(lst)
      }
      case _ => Left(lst)
    }
    case _ => Left(lst)
  }

  private def compileTermWithuOp(lst: Seq[Syntax]): Either[Seq[Syntax], (S_termWithUOp, Seq[Syntax])] = compileUnaryOp(lst) match {
    case Right((u, xs)) => compileTerm(xs) match {
      case Right((t, xs)) => Right((S_termWithUOp(u, t), xs))
      case _ => Left(lst)
    }
    case _ => Left(lst)
  }

  //  (expression (',' expression)*)?
  def compileExpressionList(lst: Seq[Syntax]): Either[Seq[Syntax], (S_expressionList, Seq[Syntax])] = compileExpression(lst) match {
    case Right((ex, S_symbol(",") :: xs)) => compileExpressionList(xs) match {
      case Right((S_expressionList(Some(el)), xs)) => Right((S_expressionList(Some(ex +: el)), xs))
      case Left(_) => Left(lst)
    }
    case Right((ex, xs)) => Right((S_expressionList(Some(Seq(ex))), xs))
    case Left(xs) => Right((S_expressionList(None), xs))
    case _ => Left(lst)
  }

  // varName ("," varName)*
  def compileVarNameList(lst: Seq[Syntax]): Either[Seq[Syntax], (S_varNameList, Seq[Syntax])] = lst match {
    case S_ident(s1) :: S_symbol(",") :: xs => compileVarNameList(xs) match {
      case Right((S_varNameList(l), xs)) => Right((S_varNameList(S_ident(s1) +: l), xs))
      case _ => Left(lst)
    }
    case S_ident(s1) :: xs => Right((S_varNameList(Seq(S_ident(s1))), xs))
    case _ => Left(lst)
  }

  // "+" | "-" | "*" | "/" | "&" | "|" | "<"| ">" | "="
  private def compileOp(lst: Seq[Syntax]): Either[Seq[Syntax], (S_op, Seq[Syntax])] = lst match {
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
  private def compileUnaryOp(lst: Seq[Syntax]): Either[Seq[Syntax], (S_unaryOp, Seq[Syntax])] = lst match {
    case S_symbol("-") :: xs => Right((S_unaryOp("-"), xs))
    case S_symbol("~") :: xs => Right((S_unaryOp("~"), xs))
    case _ => Left(lst)
  }

  // "true" | "false" | "null" | "this"
  private def compileKeywodConst(lst: Seq[Syntax]): Either[Seq[Syntax], (S_keywordConst, Seq[Syntax])] = lst match {
    case S_ident("true")  :: xs => Right((S_keywordConst("true"), xs))
    case S_ident("false") :: xs => Right((S_keywordConst("false"), xs))
    case S_ident("null")  :: xs => Right((S_keywordConst("null"), xs))
    case S_ident("this")  :: xs => Right((S_keywordConst("this"), xs))
    case _ => Left(lst)
  }

  //  'int' | 'char' | 'boolean' | className
  private def compileType(lst: Seq[Syntax]): Either[Seq[Syntax], (S_type, Seq[Syntax])] = lst match {
    case S_keyword("int")     :: xs => Right((S_type(S_keyword("int")), xs))
    case S_keyword("char")    :: xs => Right((S_type(S_keyword("char")), xs))
    case S_keyword("boolean") :: xs => Right((S_type(S_keyword("boolean")), xs))
    case S_ident(a)           :: xs => Right((S_type(S_ident(a)), xs))
    case _ => Left(lst)
  }


  // ("static" | "field") type varName ("," varName)*  ";"
  def compileClassVarDec2(lst: Seq[Syntax]): Either[String, (S_classVarDec, Seq[Syntax])] = lst match {
    case (a@(S_keyword("static" | "field"))) :: xs => compileType(xs) match {
      case Right((typ, xs)) => compileVarNameList(xs) match {
        case Right((n, xs)) => xs match {
          case S_symbol(";") :: xs => Right((S_classVarDec(a, typ, n), xs))
          case x => Left(x.toString)
        }
        case Left(x) => Left(x.toString)
      }
      case Right(x) => Left(x.toString)
      case Left(x) => Left("Require Type in var dec in class\n" + x.toString)
    }
    case x => Left(x.toString)
  }

  def compileSubroutines2(lst: Seq[Syntax]): Option[(Option[Seq[S_subroutineDec]], Seq[Syntax])] = compileSubroutine2(lst) collect {
    case (sr, xs) => compileSubroutines2(xs) match {
      case None => (Some(Seq(sr)), xs)
      case Some((sr2, xs)) => (Some(sr +: sr2.getOrElse(Nil)), xs)
      case _ => null
    }
  }

  // ('constructor' | 'function' | "method") ('void' | type) subroutineName "(" parameterList ")" subroutineBody
  def compileSubroutine2(lst: Seq[Syntax]): Option[(S_subroutineDec, Seq[Syntax])] = lst match {
    case (a@(S_keyword("constructor" | "function" | "method"))) :: (t@S_keyword("void")) :: (id@S_ident(_)) :: S_symbol("(") :: xs => compileParametererList2(xs) collect {
      case (pl, S_symbol(")") :: xs) => compileSubroutineBody2(xs).map(b => (S_subroutineDec(a, S_type(t), id, pl, b._1), b._2)) getOrElse(null)
    }
    case (a@(S_keyword("constructor" | "function" | "method"))) :: xs => compileType2(xs) collect {
      case (t, (id@S_ident(_)) :: S_symbol(")") :: xs) => compileParametererList2(xs) collect {
        case (pl, S_symbol(")") :: xs) => compileSubroutineBody2(xs).map (b => (S_subroutineDec(a, t, id, pl, b._1), b._2)) getOrElse(null)
      } getOrElse(null)
    }
    case _ => None
  }

  // "{" varDec* statements "}"
  private def compileSubroutineBody2(lst: Seq[Syntax]): Option[(S_subroutineBody, Seq[Syntax])] = lst match {
    case S_symbol("{") :: xs => for {
      (decs, xs) <- compileVarDecs2(xs)
      (ss, xs) <- compileStatements2(xs)
    } yield xs match {
      case S_symbol("}") :: xs => (S_subroutineBody(decs, ss), xs)
      case _ => null
    }
    case _ => None
  }

  //  ((type varName) (',' type varName)*)?
  def compileParametererList2(lst: Seq[Syntax]): Option[(S_parameterList, Seq[Syntax])] = compileType2(lst) match {
    case Some((typ, (id@S_ident(_)) :: S_symbol(",") :: xs )) => compileParametererList2(xs) collect {
      case (S_parameterList(l), xs) => (S_parameterList(Some((typ, id) +: l.getOrElse(Nil))) , xs)
    }
    case Some((typ, (id@S_ident(_)) :: xs )) => Some((S_parameterList(Some(Seq((typ, id)))), xs))
    case _ => Some((S_parameterList(None), lst))
  }

  // compileVarDec*
  def compileVarDecs2(lst: Seq[Syntax]): Option[(Option[Seq[S_varDec]], Seq[Syntax])] = compileVarDec2(lst) match {
    case Some((v, xs)) => compileVarDecs2(lst) match {
      case Some((l, xs)) => Some((Some(v +: l.getOrElse(Nil)), xs))
      case None => Some((Some(Seq(v)), xs))
    }
    case _ => Some((None, lst))
  }

  //  'var' type varName (',' varName)* ";"
  def compileVarDec2(lst: Seq[Syntax]): Option[(S_varDec, Seq[Syntax])] = lst match {
    case S_keyword("var") :: xs => for {
      (t, xs1) <- compileType2(xs)
      (vnames, xs2) <- compileVarNameList2(xs1)
    } yield xs2 match {
      case S_symbol(";") :: xs => (S_varDec(t, vnames), xs)
      case _ => null
    }
    case _ => None
  }

  // Statement ----

  // statement*
  def compileStatements2(lst: Seq[Syntax]): Option[(S_statements, Seq[Syntax])] = compileStatement2(lst) match {
    case Some((s, xs)) => compileStatements2(xs) match {
      case Some((S_statements(k), xs)) => Some((S_statements(Some(s +: k.getOrElse(Nil))), xs))
      case None => Some((S_statements(Some(Seq(s))), xs))
      case _ => None
    }
    case _ => Some((S_statements(None), lst))
  }

  def compileStatement2(lst: Seq[Syntax]): Option[(S_statement, Seq[Syntax])] =
    compileLet2(lst) orElse compileIf2(lst) orElse compileWhile2(lst) orElse compileDo2(lst) orElse compileReturn2(lst) map {
      t => (S_statement(t._1), t._2)
    }

  // 'let' varname ('['  expression ']')? '=' expression ';'
  def compileLet2(lst: Seq[Syntax]): Option[(S_letStatement, Seq[Syntax])] = lst match {
    case S_keyword("let") :: (id@S_ident(_)) :: S_symbol("=") :: xs => compileExpression2(xs) collect {
      case (e2, S_symbol(";") :: xs) => (S_letStatement(id, None, e2), xs)
    }
    case S_keyword("let") :: (id@S_ident(_)) :: S_symbol("[") :: xs => compileExpression2(xs) flatMap {
      case (e, S_symbol("]") :: S_symbol("=") :: xs) => compileExpression2(xs) collect {
        case (e2, S_symbol(";") :: xs) => (S_letStatement(id, Some(e), e2), xs)
      }
      case _ => None
    }
    case _ => None
  }

  // 'if' "(" expression ")" "{" statements "}" ("else" "{" statements"}")?
  def compileIf2(lst: Seq[Syntax]): Option[(S_if, Seq[Syntax])] = lst match {
    case S_keyword("if") :: S_symbol("(") :: xs => compileExpression2(xs) flatMap {
      case (ex, xs) => xs match {
        case S_symbol(")") :: S_symbol("{") :: xs => compileStatements2(xs) collect {
          case (ss, S_symbol("}") :: S_keyword("else") :: S_symbol("{") :: xs) => (compileStatements2(xs) collect {
            case (ss2, S_symbol("}") :: xs)  => ((S_if(ex, ss, Some(ss2))), xs) }).getOrElse(null)
          case (ss, S_symbol("}") :: xs) => ((S_if(ex, ss, None)), xs)
        }
        case _ => None
      }
      case _ => None
    }
    case _ => None
  }

  //  'while' '(' expression ')' "{" statemetns "}"
  def compileWhile2(lst: Seq[Syntax]): Option[(S_while, Seq[Syntax])] =  lst match {
    case S_keyword("while") :: S_symbol("(") :: xs => compileExpression2(xs) flatMap {
      case (e, S_symbol(")") :: S_symbol("{") :: xs) => compileStatements2(xs) collect {
        case (ss, (S_symbol("}") :: xs)) => (S_while(e, ss), xs)
      }
      case _ => None
    }
    case _ => None
  }

  // "do" subroutineCall ";"
  def compileDo2(lst: Seq[Syntax]): Option[(S_do, Seq[Syntax])] = lst match {
    case S_keyword("do") :: xs => compileSubroutineCall2(xs) collect { case (sr, S_symbol(";") :: xs) => (S_do(sr), xs) }
    case _ => None
  }

  // 'return' expression? ";"
  def compileReturn2(lst: Seq[Syntax]): Option[(S_return, Seq[Syntax])] = lst match {
    case S_keyword("return") :: S_symbol(";") :: xs => Some((S_return(None), xs))
    case S_keyword("return") :: xs => compileExpression2(xs) collect { case (ex, xs) => (S_return(Some(ex)), xs) }
    case _ => None
  }

  // Expression ----

  // temr (op term)*
  def compileExpression2(lst: Seq[Syntax]): Option[(S_expression, Seq[Syntax])] = compileTerm2(lst) flatMap {
    case (t, xs) => compileOp2(xs) match {
      case None => Some((S_expression(t, None), xs))
      case Some((op, xs)) => compileExpression2(xs) collect {
        case (S_expression(tr, x), xs) => (S_expression(t, Some(S_rightTerm(op, tr) +: x.getOrElse(Nil))), xs)
      }
    }
  }

  // subroutineCall | unaryOp term | keywordCosnt | integerConst | stringConst | varName | varName "[" expression "]"
  // | "(" expression ")"
  def compileTerm2(lst: Seq[Syntax]): Option[(S_term, Seq[Syntax])] = {
    (compileSubroutineCall2(lst) orElse compileTermWithOp2(lst) orElse compileKeywordConst2(lst) orElse (lst match {
      case (i@S_intConst(_)) :: xs => Some((i,  xs))
      case (s@S_stringConst(_)) :: xs => Some((s, xs))
      case (id@S_ident(x)) :: S_symbol("[") :: xs => compileExpression2(xs) collect {
        case ((ex, S_symbol("]") :: xs)) => (S_accessAry(id, ex), xs)
      }
      case (i@S_ident(x)) :: xs => Some((i,  xs))
      case S_symbol("(") :: xs => compileExpression2(xs) collect { case ((ex, S_symbol(")") :: xs)) => (ex, xs) }
      case (k@S_keyword(x)) :: xs => Some((k,  xs))
      case _ => None
    })) map { t => (S_term(t._1), t._2) }
  }

  // subroutineName "(" expressionList ")" | (className | varName) '.' subroutineName '(' expressionList ")"
  private def compileSubroutineCall2(lst: Seq[Syntax]): Option[(S_subroutineCall, Seq[Syntax])] = lst match {
    case (i@S_ident(_)) :: S_symbol("(") :: xs => compileExpressionList2(xs) collect {
      case ((el, S_symbol(")") :: xs)) => (S_subroutineCall(i, None, el), xs)
    }
    case (i@S_ident(_)) :: S_symbol(".") :: (i2@S_ident(r)) :: S_symbol("(") :: xs => compileExpressionList2(xs) collect {
      case ((el, S_symbol(")") :: xs)) => (S_subroutineCall(i, Some(i2), el), xs)
    }
    case _ => None
  }

  private def compileTermWithOp2(lst: Seq[Syntax]): Option[(S_termWithUOp, Seq[Syntax])] = for {
    op <-  compileUnaryOp2(lst)
    term <- compileTerm2(op._2)
  } yield (S_termWithUOp(op._1, term._1), term._2)

  //  (expression (',' expression)*)?
  def compileExpressionList2(lst: Seq[Syntax]): Option[(S_expressionList, Seq[Syntax])] = compileExpression2(lst) match {
    case Some((x, S_symbol(",") :: xs)) => compileExpressionList2(xs) map ( t => (t._1.prepend(x), t._2) )
    case Some((x, xs)) => compileExpressionList2(xs) map ( t => (t._1.prepend(x), t._2) )
    case None => Some((S_expressionList(None), lst))
    case _ => None
  }

  // varName ("," varName)*
  def compileVarNameList2(lst: Seq[Syntax]): Option[(S_varNameList, Seq[Syntax])] = lst match {
    case (i@S_ident(_)) :: S_symbol(",") :: xs => compileVarNameList2(xs) map ( t => (t._1.prepend(i), t._2) )
    case (i@S_ident(_)) :: xs => Some((S_varNameList(Seq(i)), xs))
    case _ => None
  }

  // "+" | "-" | "*" | "/" | "&" | "|" | "<"| ">" | "="
  private def compileOp2(lst: Seq[Syntax]): Option[(S_op, Seq[Syntax])] = lst match {
    case S_symbol(o@("+" | "-" | "*" | "/" | "&" | "|" | "<" | ">" | "=")) :: xs => Some((S_op(o), xs))
    case _ => None
  }

  // "-" | "~"
  private def compileUnaryOp2(lst: Seq[Syntax]): Option[(S_unaryOp, Seq[Syntax])] = lst match {
    case S_symbol(s@("-" | "~")) :: xs => Some((S_unaryOp(s), xs))
    case _ => None
  }

  // "true" | "false" | "null" | "this"
  private def compileKeywordConst2(lst: Seq[Syntax]): Option[(S_keywordConst, Seq[Syntax])] = lst match {
    case S_ident(k@("true" | "false" | "null" | "this")) :: xs => Some((S_keywordConst(k), xs))
    case _ => None
  }

  //  'int' | 'char' | 'boolean' | className
  private def compileType2(lst: Seq[Syntax]): Option[(S_type, Seq[Syntax])] = Option {
    lst match {
      case (k@S_keyword("int" | "char" | "boolean")) :: xs => (S_type(k), xs)
      case (i@S_ident(a)) :: xs => (S_type(i), xs)
      case _ => null
    }
  }

  private def compileKeyword(str: String, lst: Seq[Syntax]): Option[(S_keyword, Seq[Syntax])] = lst match {
    case S_keyword(str) :: xs => Some((S_keyword(str), xs))
    case _ => None
  }
}
