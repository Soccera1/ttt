PROG=ttt
SRCS=ttt.c
LDADD+=-lX11
CFLAGS+=-O3 -pipe -funroll-loops -ffast-math -fomit-frame-pointer
CFLAGS+=-std=c89 -Wall -Wextra -Werror

all: $(PROG)

run: $(PROG)
	./$(PROG)

install: $(PROG)
	install -m 755 $(PROG) $(DESTDIR)/usr/local/bin

uninstall:
	rm -f $(DESTDIR)/usr/local/bin/$(PROG)

clean:
	rm -f $(PROG) $(PROG).o

.include <bsd.prog.mk>
