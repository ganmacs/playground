package tecs.compiler

import scala.collection.mutable.{Map => MMap}

sealed trait Kind
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

  override def toString: String = m.toString + "\n parent: " + parent.map(_.toString)

  def newSymbolTable = SymbolTable(Some(this))

  def get(name: String): Option[SymbolValue] = m.get(name) orElse (parent.flatMap (_.get(name)))
  def getOrDie(name: String): SymbolValue = get(name) match {
    case None => throw new Exception(s"unknown variable: $name")
    case Some(symbol) => symbol
  }

  def exists(name: String): Boolean = None != m.get(name)

  def defineIfNotExist(name: String, typ: String, kind: Kind) =
    if (!exists(name)) { this.define (name, typ, kind) }

  def define(name: String, typ: String, kind: Kind) =  kind match {
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
    case STATIC => staticIdx + 1
    case FIELD => fieldIdx + 1
    case ARG => argIdx + 1
    case VAR => varIdx + 1
  }

  def pVarCount(k: Kind): Int = parent map (_.varCount(k)) getOrElse(0)

  def kindOf(name: String): Option[Kind] = m.get(name) collect { case SymbolValue(_, k, _) => k }
  def typeOf(name: String): Option[String] = m.get(name) collect { case SymbolValue(t, _, _) => t }
  def indexOf(name: String): Option[Int] = m.get(name) collect { case SymbolValue(_, _, i) => i }
}
