# OSX Makefile

CXXFLAGS=\
-m64 \
-Wall \
-g \
-pg \
-I/usr/include \

CFLAGS=$(CXXFLAGS)
LDFLAGS=-m64 -arch x86_64

objects   = $(patsubst %,build/%, $(patsubst %.c,%.o, $(wildcard *.c)))

build/drop: build/drop_tables
	build/drop_tables 1:very-rare 2:not-so-rare 10:very-common

build/drop_tables: build $(objects)
	$(CC) $(LDFLAGS) -o build/drop_tables $(objects)

build/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	touch build && rm -R build
