CC=ccpu-cc
CFLAGS=-I. -I../../ccpu-libc/include -I../../ccpu-libsys/include
LINK=../../ccpu/tools/link.py

CC_DIR=../../ccpu-cc

OBJS=main.o
APP_STARTUP=$(CC_DIR)/ccpu-runtime/app_startup.o
ROM_STARTUP=$(CC_DIR)/ccpu-runtime/rom_startup.o
C_RUNTIME=$(CC_DIR)/ccpu-runtime/runtime.o $(CC_DIR)/ccpu-runtime/divide32.o $(CC_DIR)/ccpu-runtime/memcpy.o

all: hello.app hello.bin

clean:
	rm -f *.app *.o *.map *.bin

emu: hello.bin
	rsim -c r --config ../../ccpu/app/stack.yaml hello.bin

hello.app: $(OBJS) $(APP_STARTUP) $(C_RUNTIME)
	$(LINK) -o $@ $^ -L../../ccpu-libc -L../../ccpu-libsys -lc -lsys --slim --layout=app.yaml

hello.bin: $(OBJS) $(ROM_STARTUP) $(C_RUNTIME)
	$(LINK) -o $@ $^ -L../../ccpu-libc -L../../ccpu-libsys -lc -lsys --layout=default-stack

%.o: %.asm
	../../ccpu/tools/asm.py -o $@ $^
