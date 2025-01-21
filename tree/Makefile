# target : execution
# syntax -> make target
# ldflags for linking process


flags=-Wall -O2 -std=c2x
ldflags=


# Wall -> enable compiler warnings
#-02 flag is for optimization of code
# std=2x specifies the C standard version e.g 21,22,23


# make file for tree
all : tree

tree : tree.o
	cc ${flags} $^ -o $@ ${ldflags} 

tree.o : tree.c
	cc ${flags} -c $^

clean : 
	rm -f *.o tree