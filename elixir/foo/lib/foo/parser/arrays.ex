defmodule Foo.Parser.Arrays do
  def parse("]", []) do
    {[], ""}
  end

  def parse(string, acc) do
    {value, rest} = Foo.Parser.do_parse(string)

    acc = [value | acc]
    case rest do
      "," <> rest -> parse(rest, acc)
      "]" <> rest -> {Enum.reverse(acc) , rest}
      _ -> raise Error
    end
  end
end
