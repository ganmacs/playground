import util.parsing.combinator.{RegexParsers, PackratParsers}

object Parser extends RegexParsers with PackratParsers with Tokens {
  var env = Env.empty[RuleW] // args with parse?

  def parse(in: String, env: Env[RuleW] = Env.empty[RuleW]) = {
    this.env = env
    parseAll(stmnt, in) match {
      case Success(d, next) => Right((d, env))
      case NoSuccess(errorMsg, next) =>
        Left(s"$errorMsg : in ${next.pos.line} at column ${next.pos.column}")
    }
  }

  lazy val stmnt = rule | expr

  lazy val rule: PackratParser[Expr] = RULE ~> ruleWithoutIn ~ (IN ~> expr) ^^ {
    case rulew ~ e =>
      Rule(rulew.nsyntax, rulew.semantics, e)
      e
  }

  lazy val ruleWithoutIn = nsyntax ~ semantics ^^ {
    case s ~ se =>
      addRule(s.name, s, se)
      RuleW(s, se)
  }

  lazy val nsyntax: PackratParser[NSyntax] = noTerm ~ (EQ ~> noTerm) ~ (CUSTOMOP ~ noTerm).* ^^ {
    case n ~ l ~ r =>
      val rl = for ((op ~ fact) <- r) yield (Op(op), fact)
      val s = makeSyntax(l, rl)
      NSyntax(n, s)
  }

  lazy val noTerm: PackratParser[NoTerm] = (EXPRTERM | IDTERM | TERMTERM | INTTERM) ^^ {
    case e => NoTerm(e)
  }

  lazy val semantics: PackratParser[Semantics] = SOURCE ^^ {
    case e => e match { case SOURCE(s) => Semantics(s) }
  }

  private val exprOp  = ADD | SUB
  private val termOp  = MUL | DIV
  private val int = INT ^^ { case e => IntLit(e.toInt) }
  private val id = ID ^^ { case e => IdLit(e) }

  private val let = (LET ~> id) ~ (EQ ~> expr) ~ (IN ~> expr) ^^ {
    case id ~ value ~ body => Let(id, value, body)
  }

  private var expr: PackratParser[Expr] = let | term ~ (exprOp ~ term).* ^^ {
    case l ~ r =>
      val rl = for ((op ~ fact) <- r) yield (Op(op), fact)
      makeBinExpr(l, rl)
  }

  private var term: PackratParser[Expr] = fact ~ (termOp ~ fact).* ^^ {
    case l ~ r =>
      val rl = for ((op ~ fact) <- r) yield (Op(op), fact)
      makeBinExpr(l, rl)
  }

  private var fact: PackratParser[Expr] = int | id | LPAREN ~> expr <~ RPAREN

  private def makeBinExpr(lterm: Expr , rterms: List[(Op, Expr)]) = {
    (lterm /: rterms) { case (a, (op, e)) => BinExpr(a, op, e) }
  }

  private def makeSyntax(lterm: Expr , rterms: List[(Op, Expr)]): Syntax = {
    rterms.foldLeft(lterm) { case (a, (op, e)) => Syntax(a, op, e) }.asInstanceOf[Syntax]
  }

  private def addRule(rule: NoTerm, s: NSyntax, se: Semantics): Unit = {
    val e = s.syntax
    rule match {
      case NoTerm(EXPRTERM) => (e.lterm, e.rterm) match {
        case (NoTerm(TERMTERM), NoTerm(TERMTERM)) => {
          expr = term ~ e.op.v ~ term ^^ {
            case t1 ~ o ~ t2 =>
              val bexpr = BinExpr(t1, Op(o), t2)
              this.env.put(bexpr.toString(), RuleW(s, se))
              bexpr
          } | let | term ~ (exprOp ~ term).* ^^ {
            case l ~ r =>
              val rl = for ((op ~ fact) <- r) yield (Op(op), fact)
              makeBinExpr(l, rl)
          }
        }
      }
      case NoTerm(TERMTERM) => {}
      case NoTerm(FACTTERM) => {}
      case NoTerm(_) => {}
    }
  }
}
