OBJECTS=	main.o stack.o

.cpp.o:
	@ gcc -c -o $@ $<
out: $(OBJECTS)
	@ gcc -o out $(OBJECTS)
	@ rm -f *.o
	@ echo "Success"
.SUFFIXES: .c.o
