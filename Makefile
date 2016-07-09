SRCDIR = src
INCLUDEDIR = include
TESTDIR = tests
LIBDIR = lib
BINDIR = bin
BUILDDIR = build

CFLAGS = -Wall -g -std=gnu11 -I$(INCLUDEDIR)
LDFLAGS = -L$(LIBDIR)
LDLIBS = -lalgorithms -largtable2

objects = $(BUILDDIR)/sorting.o $(BUILDDIR)/union_find.o \
	$(BUILDDIR)/array_dequeue.o

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
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ $(LDLIBS)

$(LIBDIR):
	mkdir $(LIBDIR)

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(BINDIR):
	mkdir $(BINDIR)
