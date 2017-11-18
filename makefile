all: serial

serial:
	gcc -w serial.cpp ppmFile.c -o serial.x
	
clean:
	rm serial.x