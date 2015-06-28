defmodule B do
  def escape(<<10>> <> _rest) do
    ["\\" <> <<110>>]
  end
end

IO.puts B.escape("\n")

defmodule A do
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

IO.puts A.escape "abx\"あ\n"
# IO.puts ~s("hello\\nworld")

# defprotocol A do
#   @fallback_to_any true
#   def call(args)
# end

# defimpl A, for: Any do
#   def call(_args) do
#     "any"
#   end
# end

# defimpl A, for: Atom do
#   def call(_args) do
#     "atom"
#   end
# end

# IO.puts A.call(1)               # "any"
# IO.puts A.call(:true)           # "atom"
# IO.puts A.Atom.call(1)          # "atom"
