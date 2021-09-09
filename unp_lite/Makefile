CC=clang

objects := $(patsubst %.c, %.o, $(wildcard *.c))

TARGET=libunp_lite.a

all: $(TARGET)

$(TARGET): $(objects)
	ar rcs $@ $(objects)
	ranlib $@

.PHONY: clean

clean:
	rm -f $(TARGET) $(objects)
