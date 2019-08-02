all:
	gcc -c compressor.c -o compressor.o
	gcc compressor.o -o compressor
	rm compressor.o

clean:
	rm compressor