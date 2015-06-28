defmodule Foo.ParserTest do
  use ExUnit.Case, async: true

  import Foo.Parser

  test "Number" do
    assert parse!("-10") == -10
    assert parse!("12") == 12
    assert parse!("0.1") == 0.1
    assert parse!("-0.1") == -0.1
  end

  test "List" do
    assert parse!("[]") == []
  end
end
