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
        case Right((subroutine, S_symbol("}") :: Nil)) => Right(S_class(a, cvds, subroutine))
        case x => Left(x.merge.toString)
      }
      case x => Left(x.merge.toString)
    }
    case x => Left(x.toString)
  }

  def compileClassVarDecs(lst: Seq[Syntax]): Either[Seq[Syntax], (Option[Seq[S_classVarDec]], Seq[Syntax])] = compileClassVarDec(lst) match {
    case Right((cvd, xs)) => compileClassVarDecs(xs) match {
      case Right((cvds, xs)) => Right((Some(cvd +: cvds.getOrElse(Nil)), xs))
      case _ => Right((Some(Seq(cvd)), xs))
    }
    case _ => Right((None, lst))
  }

  // ("static" | "field") type varName ("," varName)*  ";"
  def compileClassVarDec(lst: Seq[Syntax]): Either[Seq[Syntax], (S_classVarDec, Seq[Syntax])] = lst match {
    case (a@(S_keyword("static" | "field"))) :: xs => compileType(xs) match {
      case Right((typ, xs)) => compileVarNameList(xs) match {
        case Right((n, S_symbol(";") :: xs)) => Right((S_classVarDec(a, typ, n), xs))
        case _ => Left(xs)
      }
      case _ => Left(xs)
    }
    case _ => Left(lst)
  }

  def compileSubroutines(lst: Seq[Syntax]): Either[Seq[Syntax], (Option[Seq[S_subroutineDec]], Seq[Syntax])] = compileSubroutine(lst) match {
    case Right((sr, xs)) => compileSubroutines(xs) match  {
      case Right((lst, xs)) => Right((Some(sr +: lst.getOrElse(Nil)), xs))
      case Left(_) => Right((Some(Seq(sr)), xs))
      case _ => Left(xs)
    }
    case Left(_) => Right((None, lst))
    case _ => Left(lst)
  }

  // ('constructor' | 'function' | "method") ('void' | type) subroutineName "(" parameterList ")" subroutineBody
  def compileSubroutine(lst: Seq[Syntax]): Either[Seq[Syntax], (S_subroutineDec, Seq[Syntax])] = lst match {
    case (a@(S_keyword("constructor" | "function" | "method"))) :: (t@S_keyword("void")) :: (id@S_ident(_)) :: S_symbol("(") :: xs => compileParametererList(xs) match {
      case Right((pl, S_symbol(")") :: xs)) => compileSubroutineBody(xs).right map { b => (S_subroutineDec(a, S_type(t), id, pl, b._1), b._2) }
      case _ => Left(xs)
    }
    case (a@(S_keyword("constructor" | "function" | "method"))) :: xs => compileType(xs) match {
      case Right((t, (id@S_ident(_)) :: S_symbol("(") :: xs)) => compileParametererList(xs) match {
        case Right((pl, S_symbol(")") :: xs)) => compileSubroutineBody(xs) .right map (b => (S_subroutineDec(a, t, id, pl, b._1), b._2))
        case _ => Left(xs)
      }
      case _ => Left(xs)
    }
    case _ => Left(lst)
  }

  // "{" varDec* statements "}"
  private def compileSubroutineBody(lst: Seq[Syntax]): Either[Seq[Syntax], (S_subroutineBody, Seq[Syntax])] = lst match {
    case S_symbol("{") :: xs => compileVarDecs(xs).right flatMap {
      case (decs, xs) => compileStatements(xs) match {
        case Right((ss, S_symbol("}") :: xs)) => Right((S_subroutineBody(decs, ss), xs))
        case _ => Left(xs)
      }
    }
    case _ => Left(lst)
  }

  //  ((type varName) (',' type varName)*)?
  def compileParametererList(lst: Seq[Syntax]): Either[Seq[Syntax], (S_parameterList, Seq[Syntax])] = compileType(lst) match {
    case Right((typ, S_ident(vname) :: S_symbol(",") :: xs)) => compileParametererList(xs) match {
      case Right((S_parameterList(l), xs)) => Right((S_parameterList(Some((typ, S_ident(vname)) +: l.getOrElse(Nil))), xs))
      case _ => Left(xs)
    }
    case Right((typ, S_ident(vname) :: xs)) => Right((S_parameterList(Some(Seq((typ, S_ident(vname))))), xs))
    case _ => Right((S_parameterList(None), lst))
  }

  def compileVarDecs(lst: Seq[Syntax]): Either[Seq[Syntax], (Option[Seq[S_varDec]], Seq[Syntax])] = compileVarDec(lst) match {
    case Right((v, xs)) => compileVarDecs(xs) match {
      case Right((l, xs)) => Right((Some(v +: l.getOrElse(Nil)), xs))
      case _ => Right((Some(Seq(v)), xs))
    }
    case _ => Right((None, lst))
  }

  //  'var' type varName (',' varName)* ";"
  def compileVarDec(lst: Seq[Syntax]): Either[Seq[Syntax], (S_varDec, Seq[Syntax])] = lst match {
    case S_keyword("var") :: xs => compileType(xs).right flatMap {
      case (typ, xs) => compileVarNameList(xs) match {
        case Right((nl, S_symbol(";") :: xs)) => Right((S_varDec(typ, nl), xs))
        case _ => Left(xs)
      }
    }
    case _ => Left(lst)
  }

  // Statement ----

  // statement*
  def compileStatements(lst: Seq[Syntax]): Either[Seq[Syntax], (S_statements, Seq[Syntax])] = compileStatement(lst) match {
    case Right((s, xs)) => compileStatements(xs) match {
      case Right((S_statements(k), xs)) => Right((S_statements(Some(s +: k.getOrElse(Nil))), xs))
      case Left(lst) => Right((S_statements(Some(Seq(s))), xs))
      case _ => Left(xs)
    }
    case Left(_) => Right((S_statements(None), lst))
  }

  private def compileStatement(lst: Seq[Syntax]): Either[Seq[Syntax], (S_statement, Seq[Syntax])] = (for {
    _ <- compileLet(lst).left
    _ <- compileIf(lst).left
    _ <- compileWhile(lst).left
    _ <- compileDo(lst).left
    _ <- compileReturn(lst).left
  } yield lst).right map (t => (S_statement(t._1), t._2))

  // 'let' varname ('['  expression ']')? '=' expression ';'
  def compileLet(lst: Seq[Syntax]): Either[Seq[Syntax], (S_letStatement, Seq[Syntax])] = lst match  {
    case S_keyword("let") :: S_ident(vname) :: S_symbol("=") :: xs => compileExpression(xs) match {
      case Right((e2, S_symbol(";") :: xs)) => Right((S_letStatement(S_ident(vname), None, e2), xs))
      case _ => Left(xs)
    }
    case S_keyword("let") :: S_ident(vname) :: S_symbol("[") :: xs => compileExpression(xs) match {
      case Right((e, S_symbol("]") :: S_symbol("=") :: xs)) => compileExpression(xs) match {
        case Right((e2, S_symbol(";") :: xs)) => Right((S_letStatement(S_ident(vname), Some(e), e2), xs))
        case _ => Left(xs)
      }
      case _ => Left(xs)
    }
    case _ => Left(lst)
  }

  // 'if' "(" expression ")" "{" statements "}" ("else" "{" statements"}")?
  def compileIf(lst: Seq[Syntax]): Either[Seq[Syntax], (S_if, Seq[Syntax])] = lst match {
    case S_keyword("if") :: S_symbol("(") :: xs => compileExpression(xs) match {
      case Right((ex, S_symbol(")") :: S_symbol("{") :: xs)) => compileStatements(xs) match {
        case Right((ss, S_symbol("}") :: S_keyword("else") :: S_symbol("{") :: xs)) => compileStatements(xs) match {
          case Right((ss2, S_symbol("}") :: xs))  => Right((S_if(ex, ss, Some(ss2)), xs))
          case _ => Left(lst)
        }
        case Right((ss, S_symbol("}") :: xs)) => Right(((S_if(ex, ss, None)), xs))
        case _ => Left(xs)
      }
      case _ => Left(xs)
    }
    case _ => Left(lst)
  }

  //  'while' '(' expression ')' "{" statemetns "}"
  def compileWhile(lst: Seq[Syntax]): Either[Seq[Syntax], (S_while, Seq[Syntax])] = lst match {
    case S_keyword("while") :: S_symbol("(") :: xs => compileExpression(xs) match {
      case Right((e, S_symbol(")") :: S_symbol("{") :: xs)) => compileStatements(xs) match {
        case Right((ss, (S_symbol("}") :: xs))) => Right((S_while(e, ss), xs))
        case _ => Left(xs)
      }
      case _ => Left(xs)
    }
    case _ => Left(lst)
  }

  // "do" subroutineCall ";"
  def compileDo(lst: Seq[Syntax]): Either[Seq[Syntax], (S_do, Seq[Syntax])] = lst match {
    case S_keyword("do") :: xs => compileSubroutineCall(xs) match {
      case Right((sr, S_symbol(";") :: xs)) => Right((S_do(sr), xs))
      case _ => Left(xs)
    }
    case _ => Left(lst)
  }

  // 'return' expression? ";"
  def compileReturn(lst: Seq[Syntax]): Either[Seq[Syntax], (S_return, Seq[Syntax])] = lst match {
    case S_keyword("return") :: S_symbol(";") :: xs => Right((S_return(None), xs))
    case S_keyword("return") :: xs => compileExpression(xs) match {
      case Right((e, S_symbol(";") :: xs)) => Right((S_return(Some(e)), xs))
      case _ => Left(xs)
    }
    case _ => Left(lst)
  }

  // ----- Exprssion

  // temr (op term)*
  def compileExpression(lst: Seq[Syntax]): Either[Seq[Syntax], (S_expression, Seq[Syntax])] = compileTerm(lst).right flatMap {
    case (t, xs) => compileOp(xs) match {
      case Left(xs) => Right((S_expression(t, None), xs))
      case Right((op, xs)) => compileExpression(xs) match {
        case Right((S_expression(tr, x), xs)) => Right((S_expression(t, Some((S_rightTerm(op, tr) +: x.getOrElse(Nil)))), xs))
        case _ => Left(xs)
      }
    }
  }

  // subroutineCall | unaryOp term | keywordcosnt | integerConst | stringConst | varName | varName "[" expression "]"
  // | "(" expression ")"
  def compileTerm(lst: Seq[Syntax]): Either[Seq[Syntax], (S_term, Seq[Syntax])] = (for {
    _ <- compileSubroutineCall(lst).left
    _ <- compileTermWithOp(lst).left
    _ <- compileKeywordConst(lst).left
    _ <- (lst match {
      case (i@S_intConst(_)) :: xs => Right((i,  xs))
      case (s@S_stringConst(_)) :: xs => Right((s, xs))
      case (k@S_keyword(x)) :: xs => Right((k,  xs))
      case (id@S_ident(x)) :: S_symbol("[") :: xs => compileExpression(xs) match {
        case Right((ex, S_symbol("]") :: xs)) => Right((S_accessAry(id, ex), xs))
        case _ => Left(xs)
      }
      case (i@S_ident(x)) :: xs => Right((i,  xs))
      case S_symbol("(") :: xs => compileExpression(xs) match {
        case Right((ex, S_symbol(")") :: xs)) => Right((ex, xs))
        case _ => Left(xs)
      }
      case _ => Left(lst)
    }).left
  } yield lst).right.map (t => (S_term(t._1), t._2))

  // subroutineName "(" expressionList ")" | (className | varName) '.' subroutineName '(' expressionList ")"
  private def compileSubroutineCall(lst: Seq[Syntax]): Either[Seq[Syntax], (S_subroutineCall, Seq[Syntax])] = lst match {
    case (i@S_ident(_)) :: S_symbol("(") :: xs => compileExpressionList(xs) match {
      case Right((el, S_symbol(")") :: xs)) => Right((S_subroutineCall(i, None, el), xs))
      case _ => Left(xs)
    }
    case (i@S_ident(_)) :: S_symbol(".") :: (i2@S_ident(r)) :: S_symbol("(") :: xs => compileExpressionList(xs) match {
      case Right((el, S_symbol(")") :: xs)) => Right((S_subroutineCall(i2, Some(i), el), xs))
      case _ => Left(xs)
    }
    case _ => Left(lst)
  }

  private def compileTermWithOp(lst: Seq[Syntax]): Either[Seq[Syntax], (S_termWithUOp, Seq[Syntax])] = for {
    o <- compileUnaryOp(lst).right
    t <- compileTerm(o._2).right
  } yield (S_termWithUOp(o._1, t._1), t._2)

  //  (expression (',' expression)*)?
  def compileExpressionList(lst: Seq[Syntax]): Either[Seq[Syntax], (S_expressionList, Seq[Syntax])] = compileExpression(lst) match {
    case Right((x, S_symbol(",") :: xs)) => compileExpressionList(xs).right map ( t => (t._1.prepend(x), t._2) )
    case Right((ex, xs)) => Right((S_expressionList(Some(Seq(ex))), xs))
    case Left(xs) => Right((S_expressionList(None), xs))
  }

  // varName ("," varName)*
  def compileVarNameList(lst: Seq[Syntax]): Either[Seq[Syntax], (S_varNameList, Seq[Syntax])] = lst match {
    case (i@S_ident(_)) :: S_symbol(",") :: xs => compileVarNameList(xs).right map ( t => (t._1.prepend(i), t._2) )
    case (i@S_ident(_)) :: xs => Right((S_varNameList(Seq(i)), xs))
    case _ => Left(lst)
  }

  // "+" | "-" | "*" | "/" | "&" | "|" | "<"| ">" | "="
  private def compileOp(lst: Seq[Syntax]): Either[Seq[Syntax], (S_op, Seq[Syntax])] = lst match {
    case S_symbol(o@("+" | "-" | "*" | "/" | "&" | "|" | "<" | ">" | "=")) :: xs => Right((S_op(o), xs))
    case _ => Left(lst)
  }

  // "-" | "~"
  private def compileUnaryOp(lst: Seq[Syntax]): Either[Seq[Syntax], (S_unaryOp, Seq[Syntax])] = lst match {
    case S_symbol(s@("-" | "~")) :: xs => Right((S_unaryOp(s), xs))
    case _ => Left(lst)
  }

  // "true" | "false" | "null" | "this"
  private def compileKeywordConst(lst: Seq[Syntax]): Either[Seq[Syntax], (S_keywordConst, Seq[Syntax])] = lst match {
    case S_ident(k@("true" | "false" | "null" | "this")) :: xs => Right((S_keywordConst(k), xs))
    case _ => Left(lst)
  }

  //  'int' | 'char' | 'boolean' | className
  private def compileType(lst: Seq[Syntax]): Either[Seq[Syntax], (S_type, Seq[Syntax])] = lst match {
    case (k@S_keyword("int" | "char" | "boolean")) :: xs => Right((S_type(k), xs))
    case (i@S_ident(a)) :: xs => Right((S_type(i), xs))
    case _ => Left(lst)
  }
}
