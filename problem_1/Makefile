OBJECTS=	canon_form.o stack.o
TESTOBJECTS=    test_path.o  stack.o

.c.o:
	@ gcc -c -o $@ $<
build: $(OBJECTS)
	@ gcc -g -fsanitize=address -fsanitize=undefined -o out $(OBJECTS)
	@ rm -f *.o
	@ echo "Success"
tests: $(TESTOBJECTS)
	@ gcc -g -fsanitize=address -fsanitize=undefined -o test_out $(TESTOBJECTS)
	@ rm -f *.o
	@ echo "Success"
.SUFFIXES: .c.o
