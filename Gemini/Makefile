# Get all .cpp files in the current directory
SOURCES := $(wildcard *.cpp)

# Generate the names of the executable files
EXECUTABLES := $(patsubst %.cpp,%,$(SOURCES))

# Default target to build all executables
all: $(EXECUTABLES)

# Rule to build each executable
%: %.cpp
	g++ -o $@ $< -lboost_system -lboost_filesystem

# Clean target to remove all executables
clean:
	rm -f $(EXECUTABLES)