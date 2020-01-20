r, w = IO.pipe

v = {
  w.fileno => w.fileno,
}

env = {
  'PASSED_ID' => w.fileno.to_s
}

Process.spawn(env, 'ruby ./test.rb', v)

p r.gets
