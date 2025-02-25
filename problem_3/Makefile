OBJECTS=	main.o sort.o

.c.o:
	@ gcc -DDEBUG -c -o $@ $<
all: $(OBJECTS)
	@ gcc -g -fsanitize=address -fsanitize=undefined -o out $(OBJECTS)
	@ rm -f *.o
	@ echo "Success"
.SUFFIXES: .c.o

