class Type
case class IntType() extends Type
case class DoubleType() extends Type
case class VarType(v: Type) extends Type
