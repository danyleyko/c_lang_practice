PROJECT=keyfilter
TESTS=$(PROJECT) $(PROJECT)
TEST_OUTPUTS=$(PROJECT).out $(PROJECT).out
PROG=$(PROJECT)
CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror 

.PHONY: all run tests clean purge

all: $(PROG)

run: $(PROG)
	@./$(PROG) > $(PROG).out

clean:
	@rm -f *.o $(PROG) $(TESTS) $(PROG).out