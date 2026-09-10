include ../../Makefile.cfg

LZ4PATH = ../../lz4
LZ4	= ../../host-src/misc/lz4

CC	= $(TARGETCC)
CFLAGS	= $(TARGETCFLAGS) -ffunction-sections -fdata-sections -DDCLOAD_VERSION=\"$(VERSION)\"
INCLUDE	= -I$(LZ4PATH) -I../../target-inc

OBJCOPY	= $(TARGETOBJCOPY)

#DCLOBJECTS	= dcload-crt0.o syscalls.o memcpy.o memset.o memmove.o memcmp.o scif.o disable.o go.o video.o lz4.o dcload.o cdfs_redir.o cdfs_syscalls.o bswap.o
DCLOBJECTS	= dcload-crt0.o syscalls.o memcpy.o memset.o memmove.o memcmp.o scif.o disable.o go.o video.o lz4.o dcload.o cdfs_redir.o cdfs_syscalls.o
EXCOBJECTS	= exception.o
LZ4FILES = $(LZ4PATH)/lz4.c $(LZ4PATH)/lz4.h

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 
.s.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 
.S.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

all: dcload.lz4 exception.lz4

dcload.lz4: dcload.bin
	$(LZ4) $< $@	

dcload.bin: dcload
	$(OBJCOPY) -R .stack -O binary $< $@

dcload: $(DCLOBJECTS)
	$(CC) $(CFLAGS) -Wl,-Tdcload.x -Wl,--gc-sections -nostartfiles -nostdlib $^ -o $@ -lgcc

exception.lz4: exception.bin
	$(LZ4) $< $@	

exception.bin: exception
	$(OBJCOPY) -O binary $< $@	

exception: $(EXCOBJECTS)
	$(CC) $(CFLAGS) -Wl,-Ttext=0x8c00f400 -nostartfiles -nostdlib $^ -o $@

lz4.o: $(LZ4FILES)
	$(CC) $(CFLAGS) $(INCLUDE) -DLZ4_STATIC_LINKING_ONLY_DISABLE_MEMORY_ALLOCATION=1 -o $@ -c $<

.PHONY : clean
clean:
	-rm -f $(DCLOBJECTS) $(EXCOBJECTS) dcload exception dcload.bin exception.bin *.lz4

.PHONY : distclean
distclean: clean 
	-rm -f *.lz4
