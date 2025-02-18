OBJECTS=	main.o list.o

.c.o:
	@ gcc -g -fsanitize=address -c -o $@ $<
out: $(OBJECTS)
	@ gcc -o out $(OBJECTS)
	@ rm -f *.o
	@ echo "Success"
.SUFFIXES: .c.o
