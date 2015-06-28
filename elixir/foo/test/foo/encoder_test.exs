defmodule Foo.EncoderTest do
  use ExUnit.Case, async: true

  defp to_json(value, options \\ []) do
    Foo.Encoder.encode(value, options) |> IO.iodata_to_binary
  end

  test "Atom" do
    assert to_json(nil) == "null"
    assert to_json(true) == "true"
    assert to_json(false) == "false"
    assert to_json(:poison) == ~s("poison")
  end

  test "BitString" do
    assert to_json("") == ~s("")
    assert to_json("hello world") == ~s("hello world")
    assert to_json("hello\nworld") == ~s("hello\\nworld")
  end

  test "Integer" do
    assert to_json(10) == "10"
  end

  test "Float" do
    assert to_json(999.9) == "999.9"
    assert to_json(999.9999) == "999.9999"
  end

  test "list" do
    assert to_json([]) == "[]"
    assert to_json([1, 2, 3]) == "[1, 2, 3]"
    assert to_json([[1, 2, 3], 2, 3]) == "[[1, 2, 3], 2, 3]"
  end
end
