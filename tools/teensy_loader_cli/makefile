CC ?= gcc
CFLAGS ?= -O2 -Wall
teensy_loader_cli: teensy_loader_cli.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -s -DUSE_LIBUSB -o teensy_loader_cli teensy_loader_cli.c -lusb $(LDFLAGS)
