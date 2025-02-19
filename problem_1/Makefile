OBJECTS=	canon_form.o stack.o

.c.o:
	@ gcc -c -o $@ $<
build: $(OBJECTS)
	@ gcc -g -fsanitize=address -fsanitize=undefined -o out $(OBJECTS)
	@ rm -f *.o
	@ echo "Success"
test: 
	@ gcc -c -o stack.o stack.c
	@ gcc -DTEST -c -o canon_form.o canon_form.c
	@ gcc -g -fsanitize=address -fsanitize=undefined -o out $(OBJECTS)
	@ rm -f *.o
	@ echo "Success"
.SUFFIXES: .c.o
