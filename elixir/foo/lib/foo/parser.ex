# ParseError Struct
defmodule Foo.SyntaxErro do
  defexception [:message, :token]

  def exception(opts) do
    %Foo.SyntaxErro{message: opts[:message], token: 'implements later'}
  end
end

defmodule Foo.Parser do
  def parse!(iodata) do
    case parse(iodata) do
      {:ok, value} -> value
      {:error, message} -> raise SyntaxError, message: "invalid #{message}"
    end
  end

  def parse(iodata) do
    string = IO.iodata_to_binary(iodata)
    {value, rest} = do_parse(string)
    case rest do
      "" -> {:ok, value}
      _ -> {:error, "invalid"}
    end
  end

  # def lookup("\"" <> rest), do: parse_string(rest)
  # def lookup("{" <> rest), do: parse_map(rest)
  def do_parse("[" <> rest), do: Foo.Parser.Arrays.parse(rest, [])
  def do_parse(<<char, _ :: binary >> = string) when char in '-0123456789' do
    Foo.Parser.Numbers.parse(string)
  end

  # def skip_whitespace(<<char>>), do: string
  # def skip_whitespace(string), do: string
end
