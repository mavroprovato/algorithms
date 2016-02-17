SRCDIR = src
INCLUDEDIR = include
TESTDIR = tests
LIBDIR = lib
BINDIR = bin
BUILDDIR = build

CFLAGS = -Wall -g -std=gnu11 -I$(INCLUDEDIR)
LDFLAGS = -L$(LIBDIR)

objects = $(BUILDDIR)/sorting.o

.PHONY: all test clean

all: $(LIBDIR)/libalgorithms.a
test: $(BINDIR)/test_sorting
clean:
	@rm -Rf $(BUILDDIR) $(LIBDIR) $(BINDIR)

$(LIBDIR)/libalgorithms.a: $(objects) | $(LIBDIR)
	ar rcs $@ $^

$(objects): $(BUILDDIR)/%.o: $(SRCDIR)/%.c $(INCLUDEDIR)/%.h | $(BUILDDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(BINDIR)/test_sorting: $(TESTDIR)/test_sorting.c $(LIBDIR)/libalgorithms.a | $(BINDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ -lalgorithms

$(LIBDIR):
	mkdir $(LIBDIR)

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(BINDIR):
	mkdir $(BINDIR)
