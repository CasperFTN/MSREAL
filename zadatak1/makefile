.PHONY: all
all: zadatak_komp

zadatak_komp: zadatak_test.o
	gcc -o zadatak_komp zadatak_test.o

zadatak_test.o: zadatak_test.c
	gcc -c zadatak_test.c

.PHONY: clean
clean:
	rm zadatak_komp zadatak_test.o
