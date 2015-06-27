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

  defimpl Foo.Encoder, for: BitString do
    use Bitwise

    def encode(string, options) do
      string
      # [?", escape(string, options[:escape]), ?"]
    end
  end
end
