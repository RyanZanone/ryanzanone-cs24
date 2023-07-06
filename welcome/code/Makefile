# Makefile

# Compiler
CC := g++
# Compiler flags
CFLAGS := -Wall -Wextra -Werror -std=c++17

# Source file
SRCS := caprot.cpp
# Object files
OBJS := $(SRCS:.cpp=.o)
# Executable
EXEC := caprot

.PHONY: all clean

# Default target
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

# Rule to compile source files into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up the executable and object files
clean:
	rm -f $(OBJS) $(EXEC)
