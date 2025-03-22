.PHONY: mrproper, clean, dox, install
# .PHONY: clean, doc, install, Prepare

.SUFFIXES:

CC=g++
AR=ar
CXXFLAGS = -fPIC -O2 -Wall -Wextra -Werror -I./

A_SHLIB=so
A_STLIB=a
A_EXT=
SHRDIR=$(ASHES_DIR)/share
LIBDIR=$(ASHES_DIR)/lib
INCDIR=$(ASHES_DIR)/inc

all: SCDF.o dox
	@MakeInfo fr dynamic SCDF
	@$(CC) -shared -fPIC $< -o libSCDF.$(A_SHLIB)
	@MakeInfo fr static SCDF
	@$(AR) rcs libSCDF.$(A_STLIB) $<

install:
	@MakeInfo fr install header
	@install -p -m 755 SCDF.h $(INCDIR)
	@MakeInfo fr install libs
	@install -p -m 755 libSCDF.$(A_SHLIB) $(LIBDIR)
	@install -p -m 755 libSCDF.$(A_STLIB) $(LIBDIR)
	@MakeInfo fr install doc
	@install -p -m 755 Doc/Latex/refman.pdf $(SHRDIR)/SCDF.pdf

SCDF.o: SCDF.cpp SCDF.h
	@MakeInfo fr module SCDF
	@$(CC) $(CXXFLAGS) -c $< -o $@

dox:
	@MakeInfo fr doc API
	@doxygen Doc/Doxygen/Doxyfile > DocCompileFile.txt 2>&1
	@make -C Doc/Latex --no-print-directory > LatexCompileFile.txt 2>&1

clean:
	@MakeInfo fr clean objfiles
	@rm SCDF.o

mrproper:
	@MakeInfo fr clean libs
	@rm libSCDF.$(A_SHLIB)
	@rm libSCDF.$(A_STLIB)
	@MakeInfo fr clean doc
	@rm Doc/Latex/*
	@rm DocCompileFile.txt
	@rm LatexCompileFile.txt