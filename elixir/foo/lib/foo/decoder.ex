defmodule Foo.Decode do
  def decode(value, options) do
    case options[:as] do
      nil -> value
      as -> transform(value, as, options)
    end
  end

  def transform(value, as, options) when is_atom(as) do
    true
  end

  def transform(value, as, options) when is_list(as) do
    true
  end
end


defprotocol Foo.Decoder do
  @fallback_to_any true

  def decode(value, options)
end

defimpl Foo.Decoder, for: Any do
  def decode(value) do
    value
  end
end
