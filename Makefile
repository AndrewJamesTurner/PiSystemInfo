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
LIBS= -lwiringPi -lwiringPiDev

all: main.c functions.c functions.h 
	@$(CC) -o LCD main.c functions.c $(CFLAGS) $(LIBS)  

install:
	sudo mkdir -p /opt/LCD
	sudo cp LCD /opt/LCD/LCD
	sudo ln -sf /opt/LCD/LCD /usr/local/bin/LCD
	sudo sed -i "/\b\(exit 0\)\b/d" /etc/rc.local
	sudo grep -q -F 'LCD' /etc/rc.local || echo 'LCD' >> /etc/rc.local
	sudo echo 'exit 0' >> /etc/rc.local


clean:
	@rm -f LCD
