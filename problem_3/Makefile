OBJECTS=	sorts_test.o sort.o

.c.o:
	@ gcc -c -o $@ $<
build: $(OBJECTS)
	@ gcc -g -fsanitize=address -fsanitize=undefined -o out $(OBJECTS)
	@ rm -f *.o
	@ echo "Success"
main: 
	@ gcc -c -o main.o main.c
	@ gcc -DDEBUG -c -o sort.o sort.c
	@ gcc -o out main.o sort.o
	@ rm -f *.o
	@ echo "Success" 
all:	build
	@ ./out
	@ python3 draw_plots.py
	@ mv *.txt results
	@ mv *png pictures
	@ echo "Pictures were updated"
.SUFFIXES: .c.o

