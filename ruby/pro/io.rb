rd, wr = IO.pipe
wr.write "ping"
wr.close

p rd.read
rd.close
