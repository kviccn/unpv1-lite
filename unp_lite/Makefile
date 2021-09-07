CC=clang

objects=error.o

TARGET=libunp_lite.a

all: $(TARGET)

$(TARGET): $(objects)
	ar rcs $@ $(objects)
	ranlib $@

.PHONY: clean

clean:
	rm -f $(TARGET) $(objects)
