package tecs.compiler

import scala.xml.Elem

object XMLConveter {
  def toXML(s: Syntax): Elem = s match {
    case S_class(S_ident(className), varDecs, subroutines) => {
      <class>
      <keyword> class </keyword>
      <identifier> {className} </identifier>
      <symbol> {"{"} </symbol>
      { varDecs.getOrElse(Nil).map(toXML _) }
      { subroutines.getOrElse(Nil).map(toXML _) }
      <symbol> {"}"} </symbol>
      </class>
    }
    // case S_classVarDec(p, t, name) => {
    // }
    case S_subroutineDec(S_keyword(p), S_type(typ), name, S_parameterList(plist), body) => {
      // semicolun is lacking
      val pp = plist.getOrElse(Nil).map { case (typ, s) => toXML(typ)  }

      <subroutineDec>
      <keyword> {p} </keyword>
      <keyword> {typ} </keyword>
      { toXML(name) }
      <symbol> ( </symbol>
        <parameterList> {pp} </parameterList>
        <symbol> ) </symbol>
      {toXML(body)}
      </subroutineDec>
    }

    case S_subroutineBody(decs, statments) => {
      <subroutineBody>
      <symbol> {"{"} </symbol>
      { decs.getOrElse(Nil).map(toXML _) }
      {toXML(statments)}
      <symbol> {"}"} </symbol>
      </subroutineBody>
    }
    case S_statements(ss) => ss match {
      case None => <statements> </statements>
      case Some(ss) => {
        <statements>
        { ss.map(toXML _) }
        </statements>
      }
    }
    case S_statement(s) => toXML(s)
    case S_do(S_subroutineCall(S_ident(name), reciever, S_expressionList(elist))) => {
      val r = reciever match {
        case Some(S_ident(x)) => {
          <identifier> {x} </identifier>
          <symbol> . </symbol>
        }
        case None => Nil
      }

      <doStatement>
      <keyword> {"do"} </keyword>
      {r}
      <identifier> {name} </identifier>
      <symbol> ( </symbol>
        <expressionList>{ elist.getOrElse(Nil).map(toXML _) }</expressionList>
        <symbol> ) </symbol>
      <symbol> ; </symbol>
      </doStatement>
    }
    case S_return(v) => {
      val x = v match {
        case None => Nil
        case Some(x) => toXML(x)
      }

      <returnStatement>
      <keyword> return </keyword>
      { x }
      <symbol> ; </symbol>
      </returnStatement>
    }
    case S_while(c, body) => {
      <whileStatement>
      <keyword> {"while"} </keyword>
      <symbol> ( </symbol>
        { toXML(c) }
        <symbol> ) </symbol>
      <symbol> {"{"} </symbol>
      { toXML(c) }
      <symbol>  {"}"} </symbol>
      </whileStatement>
    }
    case S_letStatement(v, e1, e2) => {
      val ee = e1 match {
        case None => Nil
        case Some(s) => toXML(s)
      }

      <letStatement>
      <keyword> let </keyword>
      { toXML(v) }
      <symbol> = </symbol>
      { ee }
      { toXML(e2) }
      <symbol> ; </symbol>
      </letStatement>
    }
    case S_expression(x, rterm) => {
      val lt = toXML(x)
      <expression>
      {lt}
      </expression>
    }
    case S_ident(s) => <identifier> {s} </identifier>
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

          // {r}
          <identifier> {name} </identifier>
          <symbol> ( </symbol>
            <expressionList>
            { elist.getOrElse(Nil).map(toXML _) }
            </expressionList>
            <symbol> ) </symbol>
          <symbol> ; </symbol>
        }
        case S_intConst(x) => {
        }
        case i@S_ident(x) => toXML(i)
        case S_termWithUOp(o, x) => {}
        case S_keywordConst(x) => {}
        case S_accessAry(S_ident(x), e) => {}
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
      { varNameList.map(toXML _) }
      <symbol> ; </symbol>
      </varDec>
    }
    case t@S_type(typ) => <identifier> {typ} </identifier>
  }
}
