# GCC complier 
CC=gcc

# GCC complier options
	# -pedantic		Issue all the warnings demanded by strict ISO C
	# -Wall			Turns on all optional warnings which are desirable for normal code.
	# -O3			turns on all optimizations
	# -g			turns on debugging information	
	# -pg			turns on profiling information (for gprof)
	# -w			ignore warning 
	# -fpermissive
	# -std=c++11		use c++ 2011 standard
	
CFLAGS= -pedantic -Wall -O3 -lm

all: main.c functions.c functions.h
	@$(CC) -o run main.c functions.c $(CFLAGS)  


clean:
	@rm -f run