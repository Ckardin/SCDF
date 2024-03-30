.PHONY: mrproper, clean, doc, install
# .PHONY: clean, doc, install, Prepare

.SUFFIXES:

CC=g++
AR=ar
CXXFLAGS = -fPIC -O2 -Wall -Wextra -Werror -I./

all: SCDF.o doc
	@MakeInfo dynamic SCDF
	$(CC) -shared -fPIC $< -o libSCDF.$(A_SHLIB)
	@MakeInfo static SCDF
	$(AR) rcs libSCDF.$(A_STLIB) $<

install:
	install -p -m 755 SCDF.h $(INCDIR)
	install -p -m 755 libSCDF.$(A_SHLIB) $(LIBDIR)
	install -p -m 755 libSCDF.$(A_STLIB) $(LIBDIR)
	install -p -m 755 Doc/Latex/refman.pdf $(SHRDIR)
	install -p -m 755 -d Doc/HTML/ $(SHRDIR)

SCDF.o: SCDF.cpp SCDF.h
	@MakeInfo module SCDF
	@$(CC) $(CXXFLAGS) -c $< -o $@

doc:
	@MakeInfo doc API
	@doxygen Doc/Doxygen/Doxyfile
	@make -C Doc/Latex --no-print-directory

clean:
	@rm SCDF.o

mrproper: clean
	rm $(BUILDDIR)\lib\libSCDF.$(A_SHLIB)
	rm $(BUILDDIR)\lib\libSCDF.$(A_STLIB)