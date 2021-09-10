describe 'database' do
  def run_script(commands)
    raw_output = nil
    IO.popen("gradle run -q --console=plain", "r+") do |pipe|
      commands.each do |command|
        pipe.puts command
      end

      pipe.close_write

      # Read entire output
      raw_output = pipe.gets(nil)
    end
    raw_output.split("\n")
  end

  it 'inserts and retrieves a row' do
    result = run_script(["insert 1 user1 person1@example.com", "select", ".exit"])
    expected = [
      "db > Executed.",
      "db > (1, user1, person1@example.com)",
      "Executed.",
      "db > ",
    ]

    expect(result).to eq(expected)
  end

  it 'prints error message when table is full' do
    script = (1..1401).map do |i|
      "insert #{i} user#{i} person#{i}@example.com"
    end
    script << '.exit'
    result = run_script(script)
    expect(result[-2]).to eq('db > Error: Table full.')
  end

  it 'allows inserting strings that are the maximum length' do
    long_username = "a"*(32-4)
    long_email = "a"*(255-4)
    script = [
      "insert 1 #{long_username} #{long_email}",
      "select",
      ".exit",
    ]
    result = run_script(script)
    expected = [
      "db > Executed.",
      "db > (1, #{long_username}, #{long_email})",
      "Executed.",
      "db > ",
    ]
    expect(result).to eq(expected)
  end

  it 'prints error message if strings are too long' do
    long_username = "a"*((32-4) + 1)
    long_email = "a"*((255-4) + 1)
    script = [
      "insert 1 aa #{long_email}",
      "insert 1 #{long_username} bb",
      "select",
      ".exit",
    ]
    result = run_script(script)
    # "db > String is too long.",
    expected = [
      "db > invalid size for userName. username should be less than 32",
      "db > invalid size for email. email should be less than 255",
      "db > Executed.",
      "db > ",
    ]
    expect(result).to eq(expected)
  end

  it 'prints an error message if id is negative' do
    script = [
      "insert -1 cstack foo@bar.com",
      "select",
      ".exit",
    ]
    result = run_script(script)
    expected = [
      "db > ID must be positive.",
      "db > Executed.",
      "db > ",
    ]
    expect(result).to eq(expected)
  end
end
