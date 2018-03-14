.PHONY: all clean

#CC:=arm-hisi-linux-gcc
CC:=gcc
#CFLAGS:=-Wall -g3 -ggdb
CFLAGS:=-Wall -O3 -fstrict-aliasing -Wstrict-aliasing=2
#CFLAGS+=-I../include
#CFLAGS+=-Wl,-rpath,/media/sdb1/LIBPCAP/test/lib
#LDFLAGS:=-L../lib 
#LDLIBS:=/media/sdb1/LIBPCAP/test/lib/libpcap.a
#LDLIBS:=/usr/local/lib/libpcap.a

srcs:=bcast_client.c  bcast_server.c
objsdir:=objdir
objs:=$(srcs:%.c=$(objsdir)/%.o)

exe1:=bcast_client 
exe2:=bcast_server

all: $(exe1) $(exe2)

$(exe1): $(objs)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(exe2): $(objs)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(objs): | $(objsdir)
$(objsdir):
	@mkdir -p $@

$(objsdir)/%.o: %.c
	$(CC) $(CFLAGS) -E -o $@.i $<
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -rf $(exe) $(objsdir)
