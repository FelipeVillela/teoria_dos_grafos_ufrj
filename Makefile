# the compiler
CC = g++-10

# the build target executable:
TARGET  = tp2

# Flags
LDFLAGS = -pthread -std=c++20

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) -o $(TARGET).o $(TARGET).cpp $(LDFLAGS)

clean:
	rm -f $(TARGET).o