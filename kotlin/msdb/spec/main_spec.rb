describe 'database' do
  before do
    `rm -rf test1.db`
  end

  after do
    `rm -rf test1.db`
  end

  def run_script(commands)
    raw_output = nil
    IO.popen("gradle run -q --console=plain --args='test1.db'", "r+") do |pipe|
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
      "db > invalid size for email. email should be less than 255",
      "db > invalid size for userName. username should be less than 32",
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

  it 'keeps data after closing connection' do
    result1 = run_script(["insert 1 user1 person1@example.com", ".exit"])
    expect(result1).to eq(["db > Executed.", "db > "])

    result2 = run_script(["select", ".exit"])
    expected = [
      "db > (1, user1, person1@example.com)",
      "Executed.",
      "db > ",
    ]
    expect(result2).to eq(expected)
  end

  it 'prints constants' do
    script = [
      ".constants",
      ".exit",
    ]
    result = run_script(script)
    expected = [
      "db > Constants:",
      "ROW_SIZE: 291",
      "COMMON_NODE_HEADER_SIZE: 8", #  2 + 2 + 4
      "LEAF_NODE_HEADER_SIZE: 12", # 8(common header) + 4
      "LEAF_NODE_CELL_SIZE: 295", #  4 + 291(row_size)
      "LEAF_NODE_SPACE_FOR_CELLS: 4084", # 4096 - 8(common header)
      "LEAF_NODE_MAX_CELLS: 13",
      "db > ",
    ]

    expect(result).to eq(expected)
  end

  it 'allows printing out the structure of a one-node btree' do
    script = [3, 1, 2].map do |i|
      "insert #{i} user#{i} person#{i}@example.com"
    end
    result = run_script(script + [".btree", ".exit"])
    expected = [
      "db > Executed.",
      "db > Executed.",
      "db > Executed.",
      "db > Tree:",
      "- leaf (size 3)",
      "  - 1",
      "  - 2",
      "  - 3",
     "db > "
    ]
    expect(result).to eq(expected)
  end

  it 'allows printing out the structure of a 3-leaf-node btree' do
    script = (1..14).map do |i|
      "insert #{i} user#{i} person#{i}@example.com"
    end
    script << ".btree"
    script << "insert 15 user15 person15@example.com"
    script << ".exit"
    result = run_script(script)
    # puts result

    expected_array = [
      "db > Tree:",
      "- internal (size 1)",
      "  - leaf (size 7)",
      "    - 1",
      "    - 2",
      "    - 3",
      "    - 4",
      "    - 5",
      "    - 6",
      "    - 7",
      "  - key 7",
      "  - leaf (size 7)",
      "    - 8",
      "    - 9",
      "    - 10",
      "    - 11",
      "    - 12",
      "    - 13",
      "    - 14",
      "db > Executed.",
      "db > "
    ]
    expect(result[14...(result.length)]).to eq(expected_array)
  end
end
