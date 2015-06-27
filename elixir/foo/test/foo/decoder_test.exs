defmodule Foo.DecoderTest do
  use ExUnit.Case, async: true

  import Foo.Decode

  defmodule Person do
    defstruct name: '', age: 20
  end

  test "decoding single :as with atom keys" do
    person = %{name: "Devin Torres", age: 27}
    assert decode(person, as: Person) == "Devin Torres (27)"
  end
end
