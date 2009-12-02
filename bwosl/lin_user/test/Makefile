
TARGET_PROG = run_bwlib_test_cases

.PHONY: all
all: $(TARGET_PROG)

$(TARGET_PROG): main.c ../bwlib.a
	$(CC) -o $(TARGET_PROG) $^

.PHONY: FORCE
.PHONY: test
test: $(TARGET_PROG) FORCE
	./run_bwlib_test_cases
FORCE:
.PHONY: clean
	rm -rf $(TARGET_PROG) *.o
