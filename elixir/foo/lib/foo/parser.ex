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
      {:error, message} -> raise SyntaxError, message: "invalid"
    end
  end

  def parse(iodata) do
    string = IO.iodata_to_binary(iodata)
    a = do_parse(string)
    {:ok, a}
  end

  # def lookup("\"" <> rest), do: parse_string(rest)
  # def lookup("{" <> rest), do: parse_map(rest)
  def do_parse("[" <> rest), do: parse_array(rest)
  def do_parse(<<char, rest :: binary >> = string) when char in '-0123456789' do
    parse_number(string)
  end

  def parse_array("]") do
    []
  end

  # Numbers
  def parse_number("-" <> rest) do
    case rest do
      "0" <> rest -> number_frac(rest, ["-0"])
      rest -> number_int(rest, [?-])
    end
  end

  def parse_number("0" <> rest) do
    number_frac(rest, [?0])
  end

  def parse_number(string) do
    number_int(string, [])
  end

  def number_int(<<char, _>> = string, acc) when char in '123456789' do
    {digit, rest} = number_digit(string)
    generate_number([acc, digit], true)
  end

  def number_int(_, acc), do: raise(Foo.SyntaxError, message: "invalid number")

  def number_frac("." <> rest, acc) do
    {digit, rest} = number_digit(rest)
    generate_number([acc, ?., digit], false)
  end

  def number_digit(<<char, rest :: binary>> = string) when char in '0123456789' do
    size = digit_size(rest, 1)
    <<digit :: binary-size(size), rest :: binary>> = string
    {digit, rest}
  end

  def digit_size(<<char, rest :: binary>>, acc) when char in '1234567890'do
    digit_size(rest, acc + 1)
  end

  def digit_size(_, acc), do: acc

  def generate_number(iolist, true) do
    IO.iodata_to_binary(iolist) |> String.to_integer
  end

  def generate_number(iolist, false) do
    IO.iodata_to_binary(iolist) |> String.to_float
  end

  # def skip_whitespace(<<char>>), do: string
  # def skip_whitespace(string), do: string
end
