defmodule Foo.EncoderTest do
  use ExUnit.Case, async: true

  defp to_json(value, options \\ []) do
    Foo.Encoder.encode(value, options)
  end

  test "Atom" do
    assert to_json(nil) == "null"
    assert to_json(true) == "true"
    assert to_json(false) == "false"
    # assert to_json(:poison) == ~s("poison")
  end
end
