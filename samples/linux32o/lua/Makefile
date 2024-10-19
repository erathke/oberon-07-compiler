CC=cc
LIBDIR=lib
LIBS=$(LIBDIR)/liblua-i686-posix.a
CFLAGS=-m32 -no-pie
OBC=../../../compilerX
DEF=-def API_sys
OPTS=-entry _start -rtl RTL_sys
HELLO_SRCO=HelloLua.ob07
HELLO_OBJO=$(LIBDIR)/HelloLua.xo
USERDATA_SRCO=Userdata.ob07
USERDATA_OBJO=$(LIBDIR)/Userdata.xo
BINDIR=bin
HELLO_EXE=$(BINDIR)/HelloLua
USERDATA_EXE=$(BINDIR)/Userdata

all: hello userdata

hello: $(HELLO_OBJO)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -nostartfiles -o $(HELLO_EXE) $^ $(LIBS) -lm


$(LIBDIR)/HelloLua.xo: $(HELLO_SRCO)
	$(OBC) $^ linux32o -out $@ $(DEF) $(OPTS)


userdata: $(USERDATA_OBJO)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -nostartfiles -o $(USERDATA_EXE) $^ $(LIBS) -lm


$(LIBDIR)/Userdata.xo: $(USERDATA_SRCO)
	$(OBC) $^ linux32o -out $@ $(DEF) $(OPTS)


clean:
	$(RM) $(BINDIR)/* $(HELLO_OBJO) $(USERDATA_OBJO)
