package tecs.compiler

import scala.xml.{Elem, NodeSeq, PrettyPrinter}

object XMLConveter {
  def pprint(c: Elem)= {
    val pp = new PrettyPrinter(80, 2)
    println(pp.format(c))
  }

  private def join(l: List[NodeSeq], e: NodeSeq): NodeSeq = l match {
    case Nil => Nil
    case x :: Nil => x
    case x :: xs => x ++: e ++: join(xs, e)
  }

  def toXML(s: Syntax): Elem = s match {
    case S_class(className, varDecs, subroutines) => {
      <class>
      <keyword> {"class"} </keyword>
      { toXML(className) }
      <symbol> {"{"} </symbol>
      { varDecs.getOrElse(Nil).map(toXML _) }
      { subroutines.getOrElse(Nil).map(toXML _) }
      <symbol> {"}"} </symbol>
      </class>
    }
    // case S_classVarDec(p, t, name) => {
    // }
    case S_subroutineDec(S_keyword(p), S_type(typ), name, S_parameterList(plist), body) => {
      <subroutineDec>
      <keyword> {p} </keyword>
      <keyword> {typ} </keyword>
      { toXML(name) }
      <symbol> {"{"} </symbol>
      <parameterList>
      { join(plist.getOrElse(Nil).map { case (typ, s) => toXML(typ) +: toXML(typ) }, <symbol> , </symbol>) }
      </parameterList>
      <symbol> {"}"} </symbol>
      { toXML(body) }
      </subroutineDec>
    }
    case S_subroutineBody(decs, statments) => {
      <subroutineBody>
      <symbol> {"{"} </symbol>
      { decs.getOrElse(Nil).map(toXML _) }
      { toXML(statments) }
      <symbol> {"}"} </symbol>
      </subroutineBody>
    }
    case S_statements(ss) => {
      <statements>
      { ss.getOrElse(Nil).map(toXML _) }
      </statements>
    }
    case S_statement(s) => toXML(s)
    case S_do(S_subroutineCall(S_ident(name), reciever, S_expressionList(elist))) => {
      val r = reciever match {
        case Some(x) => toXML(x) +: <symbol> . </symbol>
        case None => Nil
      }

      <doStatement>
      <keyword> {"do"} </keyword>
      {r}
      <identifier> {name} </identifier>
      <symbol> {"("} </symbol>
      <expressionList>
      { elist.getOrElse(Nil).map(toXML _) }
      </expressionList>
      <symbol> {")"} </symbol>
      <symbol> ; </symbol>
      </doStatement>
    }
    case S_return(v) => {
      val x = v match {
        case None => Nil
        case Some(x) => toXML(x)
      }

      <returnStatement>
      <keyword> {"return"} </keyword>
      { x }
      <symbol> ; </symbol>
      </returnStatement>
    }
    case S_while(c, body) => {
      <whileStatement>
      <keyword> {"while"} </keyword>
      <symbol> {"("} </symbol>
      { toXML(c) }
      <symbol> {")"} </symbol>
      <symbol> {"{"} </symbol>
      { toXML(body) }
      <symbol>  {"}"} </symbol>
      </whileStatement>
    }
    case S_letStatement(v, e1, e2) => {
      val ee = e1 match {
        case None => Nil
        case Some(s) =>  <symbol> {"["} </symbol> +: toXML(s) +: <symbol> {"]"} </symbol>
      }

      <letStatement>
      <keyword> let </keyword>
      { toXML(v) }
      { ee }
      <symbol> = </symbol>
      { toXML(e2) }
      <symbol> ; </symbol>
      </letStatement>
    }
    case S_expression(x, rterm) => {
      <expression>
      { toXML(x) }
      { rterm.getOrElse(Nil).map { case S_rightTerm(op, t) =>  toXML(op) +: toXML(t) } }
      </expression>
    }
    case S_term(s) => {
      val ss = s match {
        case S_subroutineCall(S_ident(name), reciever, S_expressionList(elist)) => {
          val r = reciever match {
            case Some(S_ident(x)) => {
              <identifier> {x} </identifier>
              <symbol> . </symbol>
            }
            case None => Nil
          }

          r :+ <identifier> {name} </identifier>
          <symbol> {"("} </symbol>
          <expressionList>
          { elist.getOrElse(Nil).map(toXML _) }
          </expressionList>
          <symbol> {")"} </symbol>
        }
        case S_intConst(x) => <integerConstant> {x} </integerConstant>
        case S_stringConst(x) => <stringConstant> {x} </stringConstant>
        case i@S_ident(x) => toXML(i)
        case S_termWithUOp(o, x) => {}
        case S_keywordConst(x) => {}
        case S_accessAry(x, e) => {
          toXML(x) +: <symbol> {"["} </symbol> +: { toXML(e) } +: <symbol> {"]"} </symbol>
        }
        case S_expression(s, v) => {}
        case _ => Nil
      }

      <term>
      {ss}
      </term>
    }
    case S_varDec(typ, S_varNameList(varNameList)) => {
      <varDec>
      <keyword> {"var"} </keyword>
      { toXML(typ)}
      { join(varNameList.map(toXML _), <symbol> , </symbol>) }
      <symbol> ; </symbol>
      </varDec>
    }
    case S_ident(s) => <identifier> {s} </identifier>
    case S_type(typ) => <identifier> {typ} </identifier>
    case S_op(op) => <symbol> {op} </symbol>
  }
}
