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
PCALL_SRCO=Pcall.ob07
PCALL_OBJO=$(LIBDIR)/Pcall.xo
BINDIR=bin
HELLO_EXE=$(BINDIR)/HelloLua
USERDATA_EXE=$(BINDIR)/Userdata
PCALL_EXE=$(BINDIR)/Pcall

all: hello userdata pcall


$(LIBDIR)/%.xo: %.ob07
	$(OBC) $^ linux32o -out $@ $(DEF) $(OPTS)

hello: $(HELLO_OBJO)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -nostartfiles -o $(HELLO_EXE) $^ $(LIBS) -lm

userdata: $(USERDATA_OBJO)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -nostartfiles -o $(USERDATA_EXE) $^ $(LIBS) -lm

pcall: $(PCALL_OBJO)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -nostartfiles -o $(PCALL_EXE) $^ $(LIBS) -lm

clean:
	$(RM) $(BINDIR)/* $(HELLO_OBJO) $(USERDATA_OBJO) $(PCALL_OBJO)
