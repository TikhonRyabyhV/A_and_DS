OBJECTS=	rd_sort_test.o radix_sort.o

.cpp.o:
	@ g++ -c -o $@ $<

build: $(OBJECTS)
	@ g++ -g -fsanitize=address -fsanitize=undefined -o out $(OBJECTS)
	@ rm -f *.o
	@ echo "Success"

.SUFFIXES: .cpp.o
