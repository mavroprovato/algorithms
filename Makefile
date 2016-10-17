SRCDIR = src
INCLUDEDIR = include
PROGDIR = programs
LIBDIR = lib
BINDIR = bin
BUILDDIR = build

CFLAGS = -Wall -g -std=gnu11 -I$(INCLUDEDIR)
LDFLAGS = -L$(LIBDIR)
LDLIBS = -lalgorithms -largtable2

objects = $(BUILDDIR)/sorting.o $(BUILDDIR)/union_find.o \
	$(BUILDDIR)/array_queue.o $(BUILDDIR)/array_stack.o

.PHONY: all test clean

all: $(LIBDIR)/libalgorithms.a

progs: $(BINDIR)/sorting $(BINDIR)/test_queue

clean:
	@rm -Rf $(BUILDDIR) $(LIBDIR) $(BINDIR)

$(LIBDIR)/libalgorithms.a: $(objects) | $(LIBDIR)
	ar rcs $@ $^

$(objects): $(BUILDDIR)/%.o: $(SRCDIR)/%.c $(INCLUDEDIR)/%.h | $(BUILDDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(BINDIR)/sorting: $(PROGDIR)/sorting.c $(LIBDIR)/libalgorithms.a | $(BINDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ $(LDLIBS)

$(BINDIR)/test_queue: $(PROGDIR)/test_queue.c $(LIBDIR)/libalgorithms.a | $(BINDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@ $(LDLIBS)

$(LIBDIR):
	mkdir $(LIBDIR)

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(BINDIR):
	mkdir $(BINDIR)
