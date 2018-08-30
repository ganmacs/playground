require 'mkmf'

have_library('stdc++')

$CXXFLAGS += ' -std=c++17 '

create_makefile('test')
