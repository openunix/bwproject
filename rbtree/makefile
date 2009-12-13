main:main.c rbtree.o test.o
	gcc -o main main.c rbtree.o test.o -g
rbtree.o:rbtree.c
	gcc -c rbtree.c -g
test.o:test.c
	gcc -c test.c -g
clean:
	rm *.o main
