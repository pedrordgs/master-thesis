CC = gcc
CFLAGS = -ggdb -O2 -Wall `pkg-config --libs --cflags glib-2.0` `pkg-config --libs --cflags lttng-ctl`

lttng-noty:
	$(CC) lttng-noty.c $(CFLAGS) -o lttng-noty

install: lttng-noty
	cp lttng-noty /usr/bin

uninstall: clean
	rm /usr/bin/lttng-noty

clean:
	rm lttng-noty