#
# Makefile
#

SRC= syntax.ml parser.mly lexer.mll eval.ml main.ml
COMPONENT= syntax.ml parser.mli parser.ml lexer.ml eval.ml main.ml
TARGET= miniocaml

all:	$(TARGET)

$(TARGET): 	$(COMPONENT)
	ocamlmktop $(COMPONENT) -o $(TARGET)

parser.mli:	parser.mly
	ocamlyacc parser.mly

parser.ml:	parser.mly
	ocamlyacc parser.mly

lexer.ml:	lexer.mll
	ocamllex lexer.mll

backup:
	/bin/cp -f Makefile $(SRC) back

clean:
	/bin/rm -f parser.ml parser.mli lexer.ml $(TARGET) *.cmi *.cmo *.mli
