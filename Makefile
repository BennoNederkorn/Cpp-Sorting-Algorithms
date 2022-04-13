.PHONY: all run

# compiler: 
CC = g++

# -Wall:		        Print warnings
# -Wextra:		        Enable additional warnings not covered by "-Wall"
# -Wpedantic:	        Reject everything that is not ISO C
# -g					Generates debug information to be used by GDB debugger
CFLAGS = -Wall -Wextra -Wpedantic -g -O3

# create new output executable if algorithms.o or main.o changes
output: algorithms.o main.o
	$(CC) $(CFLAGS) algorithms.o main.o -o output
	rm *.o

# create new main.o if mains.cpp or main.hpp changes
main.o: main.cpp main.hpp
	$(CC) $(CFLAGS) -c main.cpp

# create new algorithms.o if algorithms.cpp or algorithms.hpp changes
algorithms.o: algorithms.cpp algorithms.hpp
	$(CC) $(CFLAGS) -c algorithms.cpp

clean:
	rm *.o output

# Execute the compiled programm
run:
	./output

#target: dependencies
#	action