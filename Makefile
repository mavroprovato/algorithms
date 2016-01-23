SRCDIR = src
INCLUDEDIR = include
TESTDIR = tests
LIBDIR = lib
BINDIR = bin
BUILDDIR = build

CFLAGS = -Wall -g -std=gnu11 -I$(INCLUDEDIR)
LDFLAGS = -L$(LIBDIR)

all: $(LIBDIR)/libalgorithms.a

test: $(BINDIR)/test_sorting

$(LIBDIR)/libalgorithms.a: $(BUILDDIR)/sorting.o
	@mkdir -p $(LIBDIR)
	ar rcs $@ $^

$(BUILDDIR)/sorting.o: $(SRCDIR)/sorting.c $(INCLUDEDIR)/sorting.h
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BINDIR)/test_sorting: $(TESTDIR)/test_sorting.c $(LIBDIR)/libalgorithms.a
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ -lalgorithms

clean:
	@rm -Rf $(BUILDDIR) $(LIBDIR) $(BINDIR)
