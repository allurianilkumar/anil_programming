SHELL = /bin/sh

# Compiler and flags
CC = gcc
CFLAGS = -g -Wall
CPPFLAGS =
DEFS =
srcdir = .
VPATH = .
EXT = anil

# Installing variables
INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = $(INSTALL)

prefix = /usr/local
exec_prefix = $(prefix)
bindir = $(exec_prefix)/bin

# Source files and object files
SRCS = main.c lexer.c parser.c interpreter.c variable.c
HDRS = lexer.h parser.h interpreter.h variable.h
OBJS = $(SRCS:.c=.o)

# Target executable name
PROGRAM = anil

# Default target
all: $(PROGRAM)

# Rule to build object files from source files
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $(CPPFLAGS) $(DEFS) -I$(srcdir) -I$(srcdir)/lib $< -o $@

# Rule to link the object files into the final executable
$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJS)

# Rule to install the custom command
install: $(PROGRAM)
	install -d $(bindir)
	install -m 755 $(PROGRAM) $(bindir)/$(PROGRAM)

# Rule to clean up
clean:
	rm -f $(PROGRAM) $(OBJS)
	sudo rm -f $(PROGRAM) $(bindir)/$(PROGRAM)

# Rule to run the interpreter with a test .anil file
run: $(PROGRAM)
	./$(PROGRAM) test.anil
