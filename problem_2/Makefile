OBJECTS=	browser.o browser_funcs.o list.o

.c.o:
	@ gcc -c -o $@ $<
build: $(OBJECTS)
	@ gcc -g -fsanitize=address -fsanitize=undefined -o out $(OBJECTS)
	@ rm -f *.o
	@ echo "Success"
test: 
	@ gcc -c -o list.o list.c
	@ gcc -c -o browser_funcs.o browser_funcs.c
	@ gcc -DTEST -c -o browser.o browser.c
	@ gcc -g -fsanitize=address -fsanitize=undefined -o out $(OBJECTS)
	@ rm -f *.o
	@ echo "Success"
.SUFFIXES: .c.o
