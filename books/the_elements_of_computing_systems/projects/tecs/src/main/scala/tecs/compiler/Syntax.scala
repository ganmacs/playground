package tecs.compiler

class SyntaxBuilder {
  // def build(tokens: List[TKN]) : S_class = tkn2syntax(tokens) match {
  //   case S_class(c, cvd, sd) => S_class(c, cvd,sd)
  //   case _ => throw new Exception("unknow in class")
  // }

  private def tkn2syntax(l : List[TKN]): List[Syntax] = l match {
    case KEYWORD(k)      :: List() => List(S_keyword(k))
    case SYMBOL(k)       :: List() => List(S_symbol(k))
    case IDENTIFIER(k)   :: List() => List(S_ident(k))
    case INT_CONST(k)    :: List() => List(S_intConst(k))
    case STRING_CONST(k) :: List() => List(S_stringConst(k))
    case KEYWORD(k)      :: xs => S_keyword(k)     :: tkn2syntax(xs)
    case SYMBOL(k)       :: xs => S_symbol(k)      :: tkn2syntax(xs)
    case IDENTIFIER(k)   :: xs => S_ident(k)       :: tkn2syntax(xs)
    case INT_CONST(k)    :: xs => S_intConst(k)    :: tkn2syntax(xs)
    case STRING_CONST(k) :: xs => S_stringConst(k) :: tkn2syntax(xs)
  }
}


sealed trait Syntax

case class S_class(
  className: S_ident,
  classVarDec: S_classVarDec,
  subroutineDec: S_subroutineDec) extends Syntax

case class S_classVarDec(
  prefix: S_keyword,
  tyep: S_ident,
  varNames: List[S_varName],
  s: List[Syntax]) extends Syntax

// object S_classVarDec {
//   def unapply(s: List[Syntax]):  Option[(S_keyword, S_ident, List[S_varName], List[Syntax])] =
//     s match {
//       case (sf@(S_keyword("static") | S_keyword("field"))) :: S_type(s, rest) => rest match {
//         case (s@(S_ident(_))) :: xs => None
//       }
//       case _ => None
//     }
// }

case class S_subroutineDec(l: List[Syntax]) extends Syntax
// object S_subroutineDec {
//   def unapply(s: List[Syntax]):  Option[(S_keyword, S_ident, List[S_varName], List[Syntax])] = {
//     None
//   }
// }


case class S_varName(l: List[Syntax]) extends Syntax

case class S_type(l: List[Syntax]) extends Syntax
// object S_type {
//   def unapply(s: List[Syntax]):  Option[(Syntax,  List[Syntax])] = s match {
//     case (a@(S_keyword("int") | S_keyword("char") | S_keyword("boolean") | S_ident(_))) :: xs => Some((a, xs))
//     case _ => None
//   }
// }

case class S_keyword(keyword: String) extends Syntax
case class S_symbol(keyword: String) extends Syntax
case class S_ident(keyword: String) extends Syntax
case class S_intConst(keyword: String) extends Syntax
case class S_stringConst(keyword: String) extends Syntax

// val a = List(1, 2, 3, 4, 5)
// a match {
//   case A1(i) => println(i)
// }

// trait A

// case class A1(i: List[Int]) extends A
// object A1 {
//   def unapply(l : List[Int]): Option[List[Int]] = l match {
//     case x :: y :: xs => xs match { case A2(i) => Some(x :: y :: i) }
//     case x :: y => Some(x :: y)
//     case _ => Some(List())
//   }
// }

// case class A2(l: List[Int]) extends A
// object A2 {
//   def unapply(l : List[Int]): Option[List[Int]] = l match {
//     case x :: y :: xs => xs match { case A2(i) => Some(x :: y :: i) }
//     case x :: y => Some(x :: y)
//     case _ => Some(List())
//   }
// }
