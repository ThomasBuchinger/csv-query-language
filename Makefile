PREFIX   = /usr/local
SHELL    = /bin/sh
INCLUDE  = include,/usr/include
LIBS     = lib
LINKED_LIBS = boost_program_options

CFLAGS   = -Wall -g
CC       = g++ -I ${INCLUDE} -l ${LINKED_LIBS} ${CFLAGS}
LDFLAGS  = 

.PHONY: clean install uninstall prep engine

all: prep engine.a cql

############################################################
# Modules
############################################################
cql: src/bootstrap.cpp src/cli/cli.o 
	$(CC) $? -L ${LIBS} -l engine -o $@

engine.a: src/engine/cmd_file.o
	ar rvs ${LIBS}/lib$@ $?

prep:
	-mkdir -p ${LIBS}

install:
	@echo "There is nothing worth installing"

uninstall:
	@echo "Since nothing got installed, there is no point in uninstalling..."

clean:
	-rm cql
	-rm -f $(wildcard src/**/*.h.gch) 
	-rm -f $(wildcard src/**/*.o) 
	-rm -f $(wildcard lib/*.a) 

