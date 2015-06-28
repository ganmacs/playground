defmodule Foo.ParserTest do
  use ExUnit.Case, async: true

  import Foo.Parser

  test "Number" do
    assert parse!("0") == 0
    assert parse!("1") == 1
    assert parse!("-0") == 0
    assert parse!("-1") == -1
    assert parse!("0.1") == 0.1
    assert parse!("-0.1") == -0.1
    assert parse!("0e0") == 0
    assert parse!("0E0") == 0
    assert parse!("1e0") == 1
    assert parse!("1E0") == 1
    assert parse!("1.0e0") == 1.0
    assert parse!("1e+0") == 1
    assert parse!("1.0e+0") == 1.0
    assert parse!("0.1e1") == 0.1e1
    assert parse!("0.1e-1") == 0.1e-1
    assert parse!("99.99e99") == 99.99e99
    assert parse!("-99.99e-99") == -99.99e-99
    assert parse!("123456789.123456789e123") == 123456789.123456789e123
  end

  test "String" do
    assert parse!("[]") == []
    assert parse!("[1,2,3]") == [1, 2, 3]
  end

  test "Arrays" do
    assert parse!(~s("")) == ""
    assert parse!(~s("foo")) == "foo"
    assert parse!(~s("\\b\\f\\n\\r\\t")) == ~s(\b\f\n\r\t)
    assert parse!(~s("\\b\\f\\n\\r\\tabc")) == ~s(\b\f\n\r\tabc)
    assert parse!(~s("abc\\b\\f\\n\\r\\t")) == ~s(abc\b\f\n\r\t)
    assert parse!(~s("最高")) == "最高"
  end
end
