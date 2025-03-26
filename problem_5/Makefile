OBJECTS=	stack.o node_list.o edge_list.o graph.o run_graph.o

TESTOBJECTS=	stack.o node_list.o edge_list.o graph.o test.o

.c.o:
	@ gcc -c -o $@ $<

build: $(OBJECTS)
	@ gcc -g -fsanitize=address -fsanitize=undefined -o out $(OBJECTS)
	@ rm -f *.o
	@ echo "Success"

test: $(TESTOBJECTS)
	@ gcc -g -fsanitize=address -fsanitize=undefined -o out $(TESTOBJECTS)
	@ rm -f *.o
	@ echo "Success"

.SUFFIXES: .c.o
