all:	prog1 prog2 prog3

prog1: emailfilter.c
	gcc emailfilter.c -o emailfilter
prog2: calenderfilter.c
	gcc calenderfilter.c functions.c  -o calenderfilter
prog3: locationupdater.c
	gcc locationupdater.c -o locationupdater
clean:
	rm -rf emailfilter calenderfilter locationupdater
