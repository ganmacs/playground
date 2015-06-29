defmodule Foo.Parser.Arrays do
  def parse("]", []) do
    {[], ""}
  end

  def parse(string, acc) do
    {value, rest} = Foo.Parser.do_parse(string)

    acc = [value | acc]
    case trim(rest) do
      "," <> rest -> parse(trim(rest), acc)
      "]" <> rest -> {Enum.reverse(acc) , rest}
      _ -> raise Error
    end
  end

  def trim(string_with_white_space) do
    Foo.Parser.skip_whitespace(string_with_white_space)
  end
end
