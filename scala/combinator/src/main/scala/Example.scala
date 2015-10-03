import util.parsing.combinator.{PackratParsers, Parsers, RegexParsers}
import util.parsing.input.CharSequenceReader

object Example {
  def main(args: Array[String]) {
    println(PackatExmaple.parseInput("ac"))
    println(PostalCodeParser("123-3453"))
    println(PostalCodeParser("123"))
  }

  case class PostalCode(threeDigit: String, fourDigit: String)

  object PostalCodeParser extends RegexParsers {
    def postalCode = """\d{3}""".r ~ "-" ~ """\d{4}""".r ^^ {
      case (x ~ "-" ~ y) => PostalCode(x, y)
    }

    def apply(in: String): Either[String, PostalCode] = parseAll(postalCode, in) match {
      case Success(postalCodeData, next) => Right(postalCodeData)
      case NoSuccess(errorMessage, next) =>
        Left(s"$errorMessage on line ${next.pos.line} on column ${next.pos.column}")
    }
  }

  object PackatExmaple extends PackratParsers {
    type Elem = Char

    lazy val X: PackratParser[Any] = Y ~ 'b' | Y ~ 'c'
    lazy val Y: PackratParser[Any] =
      elem("a", char => {
        println("Parsing a in packrat parser.")
        char == 'a'
      })

    def parseInput(in: String) = X(
      new PackratReader(
        new CharSequenceReader(in)
      )
    )
  }
}
