all: maked

maked: maked.c
	gcc -Wall -Werror -o maked maked.c

clean:
	rm maked

run:
	./maked