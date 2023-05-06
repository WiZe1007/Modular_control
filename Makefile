CC = clang
C_OPTS = -Wall -std=c99 -I/usr/local/include -Isrc
LAB_OPTS = -I./src src/lib.c
V_FLAGS = --tool=memcheck --leak-check=full --show-reachable=yes \
          --undef-value-errors=yes --track-origins=no --child-silent-after-fork=no \
          --trace-children=no --error-exitcode=1

DIST = dist
MAIN_BIN = main.bin
TEST_BIN = test.bin

.PHONY: clean prep compile test run leak-check check doxygen

clean:
	rm -rf $(DIST)

prep:
	mkdir -p $(DIST)

compile: $(MAIN_BIN) $(TEST_BIN)

$(TEST_BIN): test/test.c
	$(CC) $(C_OPTS) $(LAB_OPTS) $< -o $(DIST)/$@ -lcheck -lm -lsubunit

$(MAIN_BIN): src/main.c
	$(CC) $(C_OPTS) $(LAB_OPTS) -D_FILE_OFFSET_BITS=64 $< -o $(DIST)/$@ -lm

test: clean prep compile
	./$(DIST)/$(TEST_BIN)

run: clean prep compile
	./$(DIST)/$(MAIN_BIN)

leak-check: clean prep compile
	valgrind $(V_FLAGS) --log-file=$(DIST)/valgrind.log --xml-file=$(DIST)/valgrind.xml --xml=yes $(DIST)/$(MAIN_BIN)
	valgrind $(V_FLAGS) --log-file=$(DIST)/valgrind.log --xml-file=$(DIST)/valgrind.xml --xml=yes $(DIST)/$(TEST_BIN)

check:
	clang-format --verbose -dry-run --Werror src/*
	clang-tidy src/*.c -checks=-readability-uppercase-literal-suffix,-readability-magic-numbers,-clang-analyzer-deadcode.DeadStores,-clang-analyzer-security.insecureAPI.rand
	rm -rf src/*.dump

doxygen:
	doxygen


