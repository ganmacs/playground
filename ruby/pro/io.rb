c_read, p_write = IO.pipe
p_read, c_write = IO.pipe

pid = fork do
  p_read.close
  p_write.close

  if Time.to_i % 2 == 1
    c_write.write "aaaaaaaaaaaaa"
  else
    c_write.write "bbbbbbbbbbbbb"
  end

  v = c_read.read
  p v


  c_read.close
  c_write.close
end

c_write.close
c_read.close

while (c = p_read.gets)
  p c.chomp
end



# while (v = p_read.read).empty?
#   sleep 10

#   p v

# end

p_read.close
p_write.close




# rd, wr = IO.pipe
# rd, wr = IO.pipe

# wr.write "ping"
# wr.write "ping"
# wr.write "ping"
# wr.write "ping"
# wr.close

# p rd.read
# rd.close
