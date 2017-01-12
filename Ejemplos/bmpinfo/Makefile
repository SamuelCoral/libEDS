PREFIX = /mingw64/
OUT = bmpinfo.exe


all: $(OUT)


$(OUT): main.o
	gcc main.o -o $(OUT) -lEDS -lm

main.o: main.c
	gcc -c main.c


clean:
	rm -f *.o $(OUT)

install:
	cp $(OUT) $(PREFIX)bin/

uninstall:
	rm -f $(PREFIX)bin/$(OUT)

