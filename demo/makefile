BUILDDIR=build

ifneq ($(shell rlwrap --version),)
RLWRAP=rlwrap
endif

export CAML_LD_LIBRARY_PATH=$(BUILDDIR)/stublibs

.PHONY: all test_sig test_conv interactive clean

all: test_sig test_conv

test_sig: $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma $(BUILDDIR)/mpc.cma
	@echo "**** test for signature ****"
	ocaml -I $(BUILDDIR) gmp.cma mpfr.cma mpc.cma test_sig.ml
	ocamlc -c -o $(BUILDDIR)/test_sig.cmo -I $(BUILDDIR) test_sig.ml
	ocamlc -o $(BUILDDIR)/test_sig.byte.exe -I $(BUILDDIR) gmp.cma mpfr.cma mpc.cma test_sig.cmo
	$(BUILDDIR)/test_sig.byte.exe
	ocamlopt -c -o $(BUILDDIR)/test_sig.cmx -I $(BUILDDIR) test_sig.ml
	ocamlopt -o $(BUILDDIR)/test_sig.opt.exe -I $(BUILDDIR) gmp.cmxa mpfr.cmxa mpc.cmxa test_sig.cmx
	$(BUILDDIR)/test_sig.opt.exe

test_conv: $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma $(BUILDDIR)/mpc.cma
	@echo "**** test for conversions ****"
	ocaml -I $(BUILDDIR) gmp.cma mpfr.cma mpc.cma test_conv.ml

interactive: $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma $(BUILDDIR)/mpc.cma
	$(RLWRAP) ocaml -I $(BUILDDIR) gmp.cma mpfr.cma mpc.cma

$(BUILDDIR)/gmp.cma: $(wildcard ../source/gmp*)
	make -C ../source -f makefile-gmp install DESTDIR=$(abspath $(BUILDDIR))

$(BUILDDIR)/mpfr.cma: $(wildcard ../source/mpfr*) $(BUILDDIR)/gmp.cma
	make -C ../source -f makefile-mpfr install DESTDIR=$(abspath $(BUILDDIR))

$(BUILDDIR)/mpc.cma: $(wildcard ../source/mpc*) $(BUILDDIR)/mpfr.cma
	make -C ../source -f makefile-mpc install DESTDIR=$(abspath $(BUILDDIR))

clean:
	make -C ../source clean
	-rm -rf $(BUILDDIR)
