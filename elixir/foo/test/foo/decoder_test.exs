defmodule Foo.DecoderTest do
  use ExUnit.Case, async: true

  import Foo.Decode

  defmodule Person do
    defstruct name: '', age: 20
  end

  defimpl Foo.Decoder, for: Person do
    def decode(person, _option) do
      "#{person.name} (#{person.age})"
    end
  end

  test "decoding single :as with atom keys" do
    person = %{name: "Devin Torres", age: 27}
    assert decode(person, keys: :atoms, as: Person) == "Devin Torres (27)"
  end

  test "decoding single :as with string keys" do
    person = %{"name" => "Devin Torres", "age" => 27}
    assert decode(person, as: Person) == "Devin Torres (27)"
  end

  test "decoding single :as list with string keys" do
    person = [%{"name" => "Devin Torres", "age" => 27}]
    assert decode(person, as: [Person]) == ["Devin Torres (27)"]
  end

  test "decoding nested :as with string keys" do
    person = %{"person" => %{"name" => "Devin Torres", "age" => 27}}
    actual = decode(person, as: %{"person" => Person})
    expected = %{"person" => "Devin Torres (27)"}
    assert actual == expected
  end

  test "decoding into structs with default values" do
    person = %{"name" => "Devin Torres"}
    assert decode(person, as: Person) == "Devin Torres (20)"
  end
end
