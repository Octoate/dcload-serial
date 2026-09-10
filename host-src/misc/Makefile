include ../../Makefile.cfg

LZ4PATH = ../../lz4

CC	     = $(HOSTCC)
CFLAGS	 = $(HOSTCFLAGS)
INCLUDE	 = -I$(LZ4PATH)
LZ4FILES = $(LZ4PATH)/lz4.c $(LZ4PATH)/lz4.h $(LZ4PATH)/lz4hc.c $(LZ4PATH)/lz4hc.h

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

all: lz4

lz4: lz4.c lz4.o lz4hc.o
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^

lz4.o: $(LZ4PATH)/lz4.c $(LZ4PATH)/lz4.h
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

lz4hc.o: $(LZ4PATH)/lz4hc.c $(LZ4PATH)/lz4hc.h $(LZ4PATH)/lz4.h
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< 

.PHONY : clean
clean:
	-rm -f *.o

.PHONY : distclean
distclean: clean
	-rm -f lz4