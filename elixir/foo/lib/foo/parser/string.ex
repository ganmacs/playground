defmodule Foo.Parser.String do
  def parse("\\" <> rest, acc) do
    string_escaped(rest, acc)
  end

  def parse("\"" <> rest, acc) do
    {IO.iodata_to_binary(acc), rest}
  end

  def parse(string, acc) do
    n = chunk_size(string, 0)
    <<chunk :: binary-size(n), rest :: binary>> = string
    parse(rest, [acc, chunk])
  end

  for {key, value} <- Enum.zip('"\\/bfnrt', '"\\\/\b\f\n\r\t') do
    defp string_escaped(<<unquote(key)>> <> rest, acc) do
      parse(rest, [acc, unquote(value)])
    end
  end

  def chunk_size("\"" <> _, acc), do: acc
  def chunk_size("\\" <> _, acc), do: acc
  def chunk_size(<<c>> <> rest, acc) when c < 0x80 do
    chunk_size(rest, acc + 1)
  end

  def chunk_size(<<codepoint :: utf8>> <> rest, acc) do
    chunk_size(rest, acc + codepoint_size(codepoint))
  end

  defp codepoint_size(codepoint) when codepoint < 0x800,   do: 2
  defp codepoint_size(codepoint) when codepoint < 0x10000, do: 3
  defp codepoint_size(_),                                  do: 4
end
