package tecs.compiler

import scala.xml.{Elem, NodeSeq, PrettyPrinter, XML}

trait Converter {
  def run(s: Syntax): Seq[String]
}

class XMLConveter extends Converter {
  def run(s: Syntax): Seq[String] = format(toXML(s))

  def format(c: Elem): Seq[String]= {
    val printer = new PrettyPrinter(80, 2)
    printer format(c) split("\n")
  }

  private def join(l: Seq[NodeSeq], e: NodeSeq): NodeSeq = l match {
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
      { varDecs.getOrElse(Nil).map(toXML) }
      { subroutines.getOrElse(Nil).map(toXML) }
      <symbol> {"}"} </symbol>
      </class>
    }
    case S_classVarDec(p, t, S_varNameList(name)) => {
      <classVarDec>
      { toXML(p) }
      { toXML(t) }
      { join(name.map(toXML), <symbol> , </symbol>) }
      <symbol> ; </symbol>
      </classVarDec>
    }
    case S_subroutineDec(k, typ, name, S_parameterList(plist), body) => {
      <subroutineDec>
      { toXML(k) }
      { toXML(typ) }
      { toXML(name) }
      <symbol> {"("} </symbol>
      <parameterList>
      { join(plist.getOrElse(Nil).map { case (typ, s) => toXML(typ) +: toXML(s) }, <symbol> , </symbol>) }
      </parameterList>
      <symbol> {")"} </symbol>
      { toXML(body) }
      </subroutineDec>
    }
    case S_subroutineBody(decs, statments) => {
      <subroutineBody>
      <symbol> {"{"} </symbol>
      { decs.getOrElse(Nil).map(toXML) }
      { toXML(statments) }
      <symbol> {"}"} </symbol>
      </subroutineBody>
    }
    case S_statements(ss) => {
      <statements>
      { ss.getOrElse(Nil).map(toXML) }
      </statements>
    }
    case S_statement(s) => toXML(s)
    case S_do(S_subroutineCall(S_ident(name), reciever, S_expressionList(elist))) => {
      <doStatement>
      <keyword> {"do"} </keyword>
      { reciever map (toXML(_) +: <symbol> . </symbol>) getOrElse Nil }
      <identifier> {name} </identifier>
      <symbol> {"("} </symbol>
      <expressionList>
      { join(elist.getOrElse(Nil).map(toXML), <symbol> ,  </symbol>) }
      </expressionList>
      <symbol> {")"} </symbol>
      <symbol> {";"} </symbol>
      </doStatement>
    }
    case S_return(v) => {
      <returnStatement>
      <keyword> {"return"} </keyword>
      { v map(toXML) getOrElse Nil }
      <symbol> ; </symbol>
      </returnStatement>
    }
    case S_if(c, t, f) => {
      <ifStatement>
      <keyword> {"if"} </keyword>
      <symbol> {"("} </symbol>
      { toXML(c) }
      <symbol> {")"} </symbol>
      <symbol> {"{"} </symbol>
      { toXML(t) }
      <symbol> {"}"} </symbol>
      { f map (<keyword> {"else"} </keyword> +: <symbol> {"{"} </symbol> +: toXML(_) +: <symbol> {"}"} </symbol>) getOrElse Nil }
      </ifStatement>
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
      <letStatement>
      <keyword> let </keyword>
      { toXML(v) }
      { e1 map (<symbol> {"["} </symbol> +: toXML(_) +: <symbol> {"]"} </symbol>) getOrElse Nil }
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
        case S_subroutineCall(name, reciever, S_expressionList(elist)) => {
          (reciever map (toXML(_) +: <symbol> . </symbol>) getOrElse Nil) :+ toXML(name) :+
          <symbol> {"("} </symbol>
          <expressionList>
          { join(elist.getOrElse(Nil).map(toXML), <symbol> , </symbol> )}
          </expressionList>
          <symbol> {")"} </symbol>
        }
        case S_accessAry(x, e) => {
          toXML(x) +: <symbol> {"["} </symbol> +: { toXML(e) } +: <symbol> {"]"} </symbol>
        }
        case S_termWithUOp(o, x) => toXML(o) +: toXML(x)
        case S_expression(s, v) => {
          <symbol> {"("} </symbol> +:
          <expression>
          { toXML(s) }
          { v.getOrElse(Nil).map { case S_rightTerm(op, t) =>  toXML(op) +: toXML(t) } }
          </expression>
          <symbol> {")"} </symbol>
        }
        case s => toXML(s)
      }

      <term>
      {ss}
      </term>
    }
    case S_varDec(typ, S_varNameList(varNameList)) => {
      <varDec>
      <keyword> {"var"} </keyword>
      { toXML(typ)}
      { join(varNameList.map(toXML), <symbol> , </symbol>) }
      <symbol> ; </symbol>
      </varDec>
    }
    case S_ident(s) => <identifier> {s} </identifier>
    case S_type(typ) => typ match {
      case S_ident(t) => <identifier> {t} </identifier>
      case S_keyword(t) => <keyword> {t} </keyword>
      case _ => throw new Exception("type")
    }
    case S_op(op) => <symbol> {op} </symbol>
    case S_keyword(k) => <keyword> {k} </keyword>
    case S_keywordConst(k) => <keywordConstant> {k} </keywordConstant>
    case S_intConst(x) => <integerConstant> {x} </integerConstant>
    case S_stringConst(x) => <stringConstant> {x} </stringConstant>
    case S_unaryOp(x) => <symbol> {x} </symbol>
  }
}
