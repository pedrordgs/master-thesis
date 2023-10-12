CC = gcc
CFLAGS = -ggdb -O2 -Wall `pkg-config --libs --cflags glib-2.0` `pkg-config --libs --cflags lttng-ctl`

lttng-trace: utils
	$(CC) lttng-trace.c $(CFLAGS) -o lttng-trace utils.o

utils:
	$(CC) $(CFLAGS) -c utils.c

install: lttng-trace
	cp lttng-trace /usr/bin

uninstall: clean
	rm /usr/bin/lttng-trace

clean:
	rm lttng-trace