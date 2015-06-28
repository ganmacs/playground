defmodule Foo.Encode do
end

defprotocol Foo.Encoder do
  @fallback_to_any true
  def encode(value, options)
end

defimpl Foo.Encoder, for: Atom do
  def encode(nil, _), do: "null"
  def encode(true, _), do: "true"
  def encode(false, _), do: "false"

  def encode(atom, options) do
    Foo.Encoder.BitString.encode(Atom.to_string(atom), options)
  end
end

defimpl Foo.Encoder, for: BitString do
  use Bitwise

  def encode("", _), do: "\"\""

  def encode(string, _) do
    [?", escape(string), ?"]
  end

  def escape("") do
    []
  end

  for {char, seq} <- Enum.zip('"\\\n\t\r\f\b', '"\\ntrfb') do
    def escape(<<unquote(char)>> <> rest) do
      [unquote("\\" <> <<seq>>) | escape(rest)]
    end
  end

  def escape(<<char>> <> rest) when char < 0x1F or char == 0x7F do
    [char | escape(rest)]
  end

  def escape(string) do
    size = chunk_size(string, 0)
    <<chunk :: binary-size(size), rest :: binary >> = string
    [chunk | escape(rest)]
  end

  defp chunk_size(<<char>> <> _, acc) when char < 0x1F or char in '"\\' do
    acc
  end

  defp chunk_size(<<char>> <> rest, acc) when char < 0x80 do
    chunk_size(rest, acc + 1)
  end

  defp chunk_size(<<codepoint :: utf8>> <> rest, acc) do
    size = cond do
      codepoint < 0x800   -> 2
      codepoint < 0x10000 -> 3
      true                -> 4
    end
    chunk_size(rest, acc + size)
  end

  defp chunk_size("", acc), do: acc
end

defimpl Foo.Encoder, for: Integer do
  def encode(integer, _options), do: Integer.to_string(integer)
end

defimpl Foo.Encoder, for: Float do
  def encode(float, _options), do: :io_lib_format.fwrite_g(float)
end

defimpl Foo.Encoder, for: List do
  def encode([], _options), do: "[]"

  def encode(list, options) do
    [?[, Enum.map_join(list, ", ", &Foo.Encoder.encode(&1, options)), ?]]
  end
end
