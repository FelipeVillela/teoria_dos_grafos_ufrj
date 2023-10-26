# the compiler
CC = g++-10

# Flags
LDFLAGS = -pthread -std=c++20

# List of targets (executables)
TARGETS = t1_tests t2_tests

all: $(TARGETS)

t1_tests: t1_tests.cpp
	$(CC) -o t1_tests.o $< $(LDFLAGS)

t2_tests: t2_tests.cpp
	$(CC) -o t2_tests.o $< $(LDFLAGS)

clean:
	rm -f $(TARGETS) $(TARGETS:=.o)