defmodule Foo.Parser.Numbers do
  @moduledoc """
  123.123e+21
  |   |  |__ exp
  |   |__ frac
  |____ digits

  """

  def parse("-" <> rest) do
    case rest do
      "0" <> rest -> frac(rest, ["-0"])
      rest -> int(rest, [?-])
    end
  end

  def parse("0" <> rest) do
    frac(rest, [?0])
  end

  def parse(string) do
    int(string, [])
  end

  @doc """
  accpet 1-9 char
  """
  def int(<<char, _ :: binary >> = string, acc) when char in '123456789' do
    {digit, rest} = digits(string)
    frac(rest, [acc, digit])
  end

  def frac("." <> rest, acc) do
    {digit, rest} = digits(rest)
    exp(rest, true, [acc, ?., digit])
  end

  def frac(string, acc) do
    exp(string, false, acc)
  end

  def exp(<<e>> <> rest, frac, acc) when e in 'eE' do
    e = if frac, do: ?e, else: ".0e"

    case rest do
      "-" <> rest -> exp_continue(rest, [acc, e, ?-])
      "+" <> rest -> exp_continue(rest, [acc, e])
      rest -> exp_continue(rest, [acc, e])
    end
  end

  def exp_continue(rest, acc) do
    {digits, rest} = digits(rest)
    {generate_number([acc, digits], true), rest}
  end

  @doc """
  When not has exp
  """
  def exp(string, frac, acc) do
    {generate_number([acc], frac), string}
  end

  @doc """
  parse string to digit and anthor part
  digits("1234.1") #=> {"1234", ".1"}
  """
  def digits(<<char>> <> rest = string) when char in '0123456789' do
    size = digits_size(rest, 1)
    <<digit :: binary-size(size), rest :: binary>> = string
    {digit, rest}
  end

  def digits_size(<<char>> <> rest, acc) when char in '0123456789'do
    digits_size(rest, acc + 1)
  end

  def digits_size(_, acc), do: acc

  def generate_number(iolist, false) do
    IO.iodata_to_binary(iolist) |> String.to_integer
  end

  def generate_number(iolist, true) do
    IO.iodata_to_binary(iolist) |> String.to_float
  end
end
