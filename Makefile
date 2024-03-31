.PHONY: mrproper, clean, dox, install
# .PHONY: clean, doc, install, Prepare

.SUFFIXES:

CC=g++
AR=ar
CXXFLAGS = -fPIC -O2 -Wall -Wextra -Werror -I./

all: SCDF.o dox
	@MakeInfo dynamic SCDF
	@$(CC) -shared -fPIC $< -o libSCDF.$(A_SHLIB)
	@MakeInfo static SCDF
	@$(AR) rcs libSCDF.$(A_STLIB) $<

install:
	@MakeInfo install header
	@install -p -m 755 SCDF.h $(INCDIR)
	@MakeInfo install libs
	@install -p -m 755 libSCDF.$(A_SHLIB) $(LIBDIR)
	@install -p -m 755 libSCDF.$(A_STLIB) $(LIBDIR)
	@MakeInfo install doc
	@install -p -m 755 Doc/Latex/refman.pdf $(SHRDIR)

SCDF.o: SCDF.cpp SCDF.h
	@MakeInfo module SCDF
	@$(CC) $(CXXFLAGS) -c $< -o $@

dox:
	@MakeInfo doc API
	@doxygen Doc/Doxygen/Doxyfile > DocCompileFile.txt 2>&1
	@make -C Doc/Latex --no-print-directory > LatexCompileFile.txt 2>&1

clean:
	@MakeInfo clean objfiles
	@rm SCDF.o

mrproper:
	@MakeInfo clean libs
	@rm libSCDF.$(A_SHLIB)
	@rm libSCDF.$(A_STLIB)
	@MakeInfo clean doc
	@rm Doc/Latex/*
	@rm DocCompileFile.txt
	@rm LatexCompileFile.txt