OBJECTS=	main.o list.o

.c.o:
	@ gcc -c -o $@ $<
out: $(OBJECTS)
	@ gcc -g -fsanitize=address -o out $(OBJECTS)
	@ rm -f *.o
	@ echo "Success"
.SUFFIXES: .c.o
