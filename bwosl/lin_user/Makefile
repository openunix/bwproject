CFLAGS += -g  -Wall

TOP = ../..
LIBOBJS = rbtree.o
TARGETLIB = bwlib.a

.PHONY: all
all: $(TARGETLIB)

$(TARGETLIB): $(LIBOBJS) Makefile
	ar rcs $@ $(LIBOBJS)

rbtree.o: ${TOP}/rbtree/rbtree.c
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -o $@ -c $<

.PHONY: clean
clean:
	rm -rf $(LIBOBJS) bwlib.a

.PHONY: FORCE
.PHONY: test
test: $(TARGETLIB) FORCE
	$(MAKE) -C test
FORCE: