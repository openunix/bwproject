CFLAGS += -g  -Wall

TOP = ../..
LIBOBJS = rbtree.o

.PHONY: all
all: bwlib.a

bwlib.a: $(LIBOBJS) Makefile
	ar rcs $@ $(LIBOBJS)

rbtree.o: ${TOP}/rbtree/rbtree.c
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -o $@ -c $<

