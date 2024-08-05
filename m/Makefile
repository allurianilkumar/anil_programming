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
SRCS = anil.c version.c
HDRS = version.h
# OBJS = anil.o version.o
OBJS = $(SRCS:.c=.o)

# Target executable name
PROGRAM = anil

# Sample example file details
BASE_NAME = main

# Default target
all: $(PROGRAM)

# # Rule to build the object file from the source file
.c.o:
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(DEFS) -I$(srcdir) -I$(srcdir)/lib $<


# %.o: %.c
# 	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(DEFS) -I$(srcdir) -I$(srcdir)/lib $<

# # Rule to build main.o from main.c
# anil.o: anil.c
# 	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(DEFS) -I$(srcdir) -I$(srcdir)/lib anil.c

# # Rule to build version.o from version.c
# version.o: version.c
# 	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(DEFS) -I$(srcdir) -I$(srcdir)/lib version.c


# Pattern rule to build object files from source files
# %.o: %.c
# 	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(DEFS) -I$(srcdir) -I$(srcdir)/lib $<

# Rule to link the object files into the final executable
$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJS)

# Rule to install the custom command
install: $(PROGRAM)
	install -d $(bindir)
	install -m 755 $(PROGRAM) $(bindir)/$(PROGRAM)
# install: $(PROGMAM)
# 	install -d $(bindir)
# 	install -m 755 $(PROGRAM) $(bindir)/$(PROGRAM)
# 	$(INSTALL_PROGRAM) $(PROGRAM) $(bindir)/$(PROGRAM)
# Rule to clean up
clean:
	rm -f $(PROGRAM) $(OBJS)
	sudo rm -f $(PROGRAM) $(bindir)/$(PROGRAM)

# # Rule to run the interpreter with a test .anil file
# run: $(PROGRAM)
# 	./$(PROGRAM) $(BASE_NAME).$(EXT)
