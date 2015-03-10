P=tests
OBJECTS=../charring.o
CFLAGS=-Wall -Werror -std=c99 `pkg-config --cflags glib-2.0`
LDLIBS=`pkg-config --libs glib-2.0`
CC=gcc

$(P): $(OBJECTS)

run: $(P)
	./$(P)

clean:
	rm $(OBJECTS)
	rm $(P)
