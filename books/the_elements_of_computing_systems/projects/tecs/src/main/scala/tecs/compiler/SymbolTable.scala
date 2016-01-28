package tecs.compiler

import scala.collection.mutable.{Map => MMap}

trait Kind
case object STATIC extends Kind
case object FIELD extends Kind
case object ARG extends Kind
case object VAR extends Kind

case class SymbolValue(typ: String, kind: Kind, i: Int)

case class SymbolTable(parent: Option[SymbolTable]) {
  val m = MMap[String, SymbolValue]()
  var staticIdx = 0
  var fieldIdx = 0
  var argIdx = 0
  var varIdx = 0

  def newSubroutine() = SymbolTable(Some(this))

  def get(name: String): Option[SymbolValue] = m.get(name) match {
    case Some(s) => Some(s)
    case None => parent flatMap (_.get(name))
  }

  def define(name: String, typ: String, kind: Kind) = kind match {
    case STATIC => {
      m += (name -> SymbolValue(typ, kind, staticIdx))
      staticIdx += 1
    }
    case FIELD => {
      m += (name -> SymbolValue(typ, kind, fieldIdx))
      fieldIdx += 1
    }
    case ARG => {
      m += (name -> SymbolValue(typ, kind, argIdx))
      argIdx += 1
    }
    case VAR => {
      m += (name -> SymbolValue(typ, kind, varIdx))
      varIdx += 1
    }
  }

  def varCount(kind: Kind) = kind match {
    case STATIC => staticIdx - 1
    case FIELD => fieldIdx - 1
    case ARG => argIdx - 1
    case VAR => varIdx - 1
  }

  def kindOf(name: String): Option[Kind] = m.get(name) collect { case SymbolValue(_, k, _) => k }
  def typOf(name: String): Option[String] = m.get(name) collect { case SymbolValue(t, _, _) => t }
  def indexOf(name: String): Option[Int] = m.get(name) collect { case SymbolValue(_, _, i) => i }
}
