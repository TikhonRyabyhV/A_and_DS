OBJECTS=	browser.o browser_funcs.o list.o

.c.o:
	@ gcc -c -o $@ $<
build: $(OBJECTS)
	@ gcc -g -fsanitize=address -fsanitize=undefined -o out $(OBJECTS)
	@ rm -f *.o
	@ echo "Success"
.SUFFIXES: .c.o
