defprotocol A do
  @fallback_to_any true
  def call(args)
end

defimpl A, for: Any do
  def call(_args) do
    "any"
  end
end

defimpl A, for: Atom do
  def call(_args) do
    "atom"
  end
end

IO.puts A.call(1)               # "any"
IO.puts A.call(:true)           # "atom"
IO.puts A.Atom.call(1)          # "atom"
