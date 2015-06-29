defmodule Foo.Parser.Objects do
  def parse("}" <> _, []) do
    {Map.new, ""}
  end

  def parse(<<_>> <> rest , acc) do
    {key, rest} = Foo.Parser.String.parse(rest, [])

    {value, rest} = case trim(rest) do
      ":" <> rest -> Foo.Parser.do_parse(trim(rest))
      _ -> raise Foo.SyntaxError
    end

    acc = [{key, value} | acc]
    case trim(rest) do
      "," <> rest -> parse(trim(rest), acc)
      "}" <> rest -> {:maps.from_list(acc), rest}
      _ -> raise Foo.SyntaxError
    end
  end

  def trim(string_with_white_space) do
    Foo.Parser.skip_whitespace(string_with_white_space)
  end
end
