defmodule Foo.Parser.Objects do
  def parse("}" <> _, []) do
    {Map.new, ""}
  end

  def parse(<<_>> <> rest , acc) do
    {key, rest} = Foo.Parser.String.parse(rest, [])

    {value, rest} = case rest do
      ":" <> rest -> Foo.Parser.do_parse(rest)
      _ -> raise Foo.SyntaxError
    end

    acc = [{key, value} | acc]
    case rest do
      "," <> rest -> parse(rest, acc)
      "}" <> rest -> {:maps.from_list(acc), rest}
      _ -> raise Foo.SyntaxError
    end
  end
end
