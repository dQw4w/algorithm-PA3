# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
OPTFLAGS = -O3
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version


all	: bin/cb
	@echo -n ""


# optimized version
bin/cb	:  main.o lib | bin
			$(CC) $(OPTFLAGS)  main.o -ltm_usage -Llib -o bin/cb
main.o 	: src/main.cpp src/data.h lib/tm_usage.h | bin
			$(CC) $(CFLAGS) $< -Ilib -o $@
bin :
	mkdir -p bin

lib: lib/libtm_usage.a

lib/libtm_usage.a: tm_usage.o
	$(AR) $(ARFLAGS) $@ $<
tm_usage.o: lib/tm_usage.cpp lib/tm_usage.h
	$(CC) $(CFLAGS) $<
	
# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/*

