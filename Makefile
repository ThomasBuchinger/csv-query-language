PREFIX   = /usr/local
SHELL    = /bin/sh
INCLUDE  = -Iinclude -I/usr/include
LIBS     = lib
LINKED_LIBS = -lboost_program_options

CXXFLAGS   = -Wall -g -std=c++11
CC       = g++ ${INCLUDE} ${LINKED_LIBS}
LDFLAGS  =
GMOCK    = -L/usr/lib -L/usr/lib64 -lgmock -lgtest -pthread

.PHONY: clean install uninstall prep engine test

all: prep engine.a cql

############################################################
# Modules
############################################################
cql: src/bootstrap.cpp src/cli/cli.o 
	$(CC) $? -L ${LIBS} -l engine -o $@

engine.a: src/engine/cmd_file.o src/lib/csv.o
	ar rvs ${LIBS}/lib$@ $?

test: src/cli/cli.o test/cli/cli_test.cc
	$(CC) $? -L ${LIBS} -l engine $(GMOCK) -o run-tests


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
	-rm -f lib/libengine.a  
#	-rm -f $(wildcard lib/*.a) 

