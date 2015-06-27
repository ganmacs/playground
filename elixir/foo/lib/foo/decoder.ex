defmodule Foo.Decode do
  def decode(value, options) do
    case options[:as] do
      nil -> value
      as -> transform(value, as, options)
    end
  end

  def transform(value, as, options) when is_atom(as) do
    transform_struct(value, as, options[:keys], options)
  end

  def transform(value, [as], options) do
    for v <- value, do: transform(v, as, options)
  end

  def transform(value, as, options) do
    value
  end

  def transform_struct(value, as, keys, options) when keys == :atoms do
    Foo.Decoder.decode(struct(as, value), options)
  end

  def transform_struct(value, as, _keys, options) do
    struct = as.__struct__

    Map.from_struct(struct)
    |> Enum.into(%{}, fn {key, default} ->
      {key, Map.get(value, Atom.to_string(key), default)} end)
    |> Map.put(:__struct__, struct.__struct__) # create struct, struct is just bare maps underneath
    |> Foo.Decoder.decode(options)
  end
end

defprotocol Foo.Decoder do
  @fallback_to_any true

  def decode(value, options)
end

defimpl Foo.Decoder, for: Any do
  def decode(value, option) do
    value
  end
end
