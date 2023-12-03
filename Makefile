CC=arm-linux-gnueabihf-gcc
CFLAGS=-Iexternal/libwebsockets/build/include
LDFLAGS=-Lexternal/libwebsockets/build/lib -lwebsockets
TARGET=main
SOURCE=main.c
HEADERS=

# Assuming libwebsockets does indeed place its built libraries in the 'lib' directory
# and the header files are in the 'include' directory relative to its root folder.

all: $(TARGET)

$(TARGET): $(SOURCE) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)

