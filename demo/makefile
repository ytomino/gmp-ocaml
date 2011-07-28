BUILDDIR=build

ifneq ($(shell rlwrap --version),)
RLWRAP=rlwrap
endif

export CAML_LD_LIBRARY_PATH=$(BUILDDIR)/stublibs

.PHONY: all test_conv test_marshal test_sig interactive clean

all: test_conv test_marshal test_sig

test_conv: test_conv.ml $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma $(BUILDDIR)/mpc.cma
	@echo "**** test for conversions ****"
	ocaml -I $(BUILDDIR) gmp.cma mpfr.cma mpc.cma $<

test_marshal: test_marshal.ml $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma $(BUILDDIR)/mpc.cma
	@echo "**** test for marshaling ****"
	ocaml -I $(BUILDDIR) gmp.cma mpfr.cma mpc.cma $<
	ocamlc -c -o $(BUILDDIR)/test_marshal.cmo -I $(BUILDDIR) $<
	ocamlc -o $(BUILDDIR)/test_marshal.byte.exe -I $(BUILDDIR) gmp.cma mpfr.cma mpc.cma test_marshal.cmo
	$(BUILDDIR)/test_marshal.byte.exe
	ocamlopt -c -o $(BUILDDIR)/test_marshal.cmx -I $(BUILDDIR) $<
	ocamlopt -o $(BUILDDIR)/test_marshal.opt.exe -I $(BUILDDIR) gmp.cmxa mpfr.cmxa mpc.cmxa test_marshal.cmx
	$(BUILDDIR)/test_marshal.opt.exe

test_sig: test_sig.ml $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma $(BUILDDIR)/mpc.cma
	@echo "**** test for signature ****"
	ocaml -I $(BUILDDIR) gmp.cma mpfr.cma mpc.cma $<
	ocamlc -c -o $(BUILDDIR)/test_sig.cmo -I $(BUILDDIR) $<
	ocamlc -o $(BUILDDIR)/test_sig.byte.exe -I $(BUILDDIR) gmp.cma mpfr.cma mpc.cma test_sig.cmo
	$(BUILDDIR)/test_sig.byte.exe
	ocamlopt -c -o $(BUILDDIR)/test_sig.cmx -I $(BUILDDIR) $<
	ocamlopt -o $(BUILDDIR)/test_sig.opt.exe -I $(BUILDDIR) gmp.cmxa mpfr.cmxa mpc.cmxa test_sig.cmx
	$(BUILDDIR)/test_sig.opt.exe

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
