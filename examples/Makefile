HOST:=$(shell $(CC) -dumpmachine)
TARGET=$(HOST)

ifeq ($(TARGET),$(HOST))
ifneq ($(findstring mingw,$(HOST))$(findstring msys,$(HOST)),)
BINLN=
else
BINLN=bin
endif
ifneq ($(shell rlwrap --version),)
RLWRAP=rlwrap
endif
else
BINLN=
endif

BUILDSUFFIX=.noindex
BUILDDIR=$(TARGET)$(BUILDSUFFIX)
GMP_BUILDDIR=$(BUILDDIR)/gmp$(BUILDSUFFIX)

EXAMPLES=$(basename $(wildcard *.ml))
TESTS=$(filter test_%,$(EXAMPLES))

.PHONY: all check interacitve clean $(TESTS)

all: \
	$(patsubst %,$(BUILDDIR)/%.byte.exe,$(EXAMPLES)) \
	$(patsubst %,$(BUILDDIR)/%.opt.exe,$(EXAMPLES)) \
	$(BUILDDIR)/essai.byte.exe $(BUILDDIR)/essai.opt.exe \
	$(BUILDDIR)/test_creal.byte.exe $(BUILDDIR)/test_creal.opt.exe \
	$(BUILDDIR)/test_mlgmp.byte.exe $(BUILDDIR)/test_mlgmp.opt.exe \
	$(BUILDDIR)/test_suite.byte.exe $(BUILDDIR)/test_suite.opt.exe \
	$(BINLN)

$(BUILDDIR)/%.byte.exe: %.ml $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma $(BUILDDIR)/mpc.cma
	ocamlc -c -o $(@:.byte.exe=.cmo) -I $(BUILDDIR) $(OCAMLCFLAGS) $<
	ocamlc -o $@ -I $(BUILDDIR) $(OCAMLCFLAGS) gmp.cma mpfr.cma mpc.cma $(@:.byte.exe=.cmo)

$(BUILDDIR)/%.opt.exe: %.ml $(BUILDDIR)/gmp.cmxa $(BUILDDIR)/mpfr.cmxa $(BUILDDIR)/mpc.cmxa
	ocamlopt -c -o $(@:.opt.exe=.cmx) -I $(BUILDDIR) $(OCAMLCFLAGS) $<
	ocamlopt -o $@ -I $(BUILDDIR) $(OCAMLCFLAGS) gmp.cmxa mpfr.cmxa mpc.cmxa $(@:.opt.exe=.cmx)

$(BUILDDIR)/gmp2mlgmp.cmo: mlgmp/gmp2mlgmp.ml $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma
	ocamlc -c -o $@ -I $(BUILDDIR) $(OCAMLCFLAGS) $<

$(BUILDDIR)/gmp2mlgmp.cmx: mlgmp/gmp2mlgmp.ml $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma
	ocamlopt -c -o $@ -I $(BUILDDIR) $(OCAMLCFLAGS) $<

$(BUILDDIR)/creal.cmo: mlgmp/creal.ml $(BUILDDIR)/gmp2mlgmp.cmo
	ocamlc -c -o $(@:.cmo=.cmi) -I $(BUILDDIR) $(OCAMLCFLAGS) $(<:.ml=.mli)
	ocamlc -c -o $@ -I $(BUILDDIR) $(OCAMLCFLAGS) $<

$(BUILDDIR)/creal.cmx: mlgmp/creal.ml $(BUILDDIR)/gmp2mlgmp.cmx
	ocamlopt -c -o $(@:.cmo=.cmi) -I $(BUILDDIR) $(OCAMLCFLAGS) $(<:.ml=.mli)
	ocamlopt -c -o $@ -I $(BUILDDIR) $(OCAMLCFLAGS) $<

$(BUILDDIR)/%.byte.exe: mlgmp/%.ml $(BUILDDIR)/creal.cmo
	ocamlc -c -o $(@:.byte.exe=.cmo) -I $(BUILDDIR) $(OCAMLCFLAGS) $<
	ocamlc -o $@ -I $(BUILDDIR) $(OCAMLCFLAGS) gmp.cma mpfr.cma $(BUILDDIR)/gmp2mlgmp.cmo $(BUILDDIR)/creal.cmo $(@:.byte.exe=.cmo)

$(BUILDDIR)/%.opt.exe: mlgmp/%.ml $(BUILDDIR)/creal.cmx
	ocamlopt -c -o $(@:.opt.exe=.cmx) -I $(BUILDDIR) $(OCAMLCFLAGS) $<
	ocamlopt -o $@ -I $(BUILDDIR) $(OCAMLCFLAGS) gmp.cmxa mpfr.cmxa $(BUILDDIR)/gmp2mlgmp.cmx $(BUILDDIR)/creal.cmx $(@:.opt.exe=.cmx)

check: all $(TESTS)

$(TESTS): %: $(BUILDDIR)/%.byte.exe $(BUILDDIR)/%.opt.exe
	$<
	$(patsubst %.byte.exe,%.opt.exe,$<)

interactive: $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma $(BUILDDIR)/mpc.cma
	$(RLWRAP) ocaml -I $(BUILDDIR) $(OCAMLCFLAGS) gmp.cma mpfr.cma mpc.cma

$(BUILDDIR)/gmp.cma $(BUILDDIR)/gmp.cmxa: $(wildcard ../source/gmp*)
	$(MAKE) -C ../source -f Makefile-gmp install \
		BUILDDIR=$(abspath $(GMP_BUILDDIR)) \
		INSTALLDIR=$(abspath $(BUILDDIR))

$(BUILDDIR)/mpfr.cma $(BUILDDIR)/mpfr.cmxa: $(wildcard ../source/mpfr*) $(BUILDDIR)/gmp.cma $(BUILDDIR)/gmp.cmxa
	$(MAKE) -C ../source -f Makefile-mpfr install \
		BUILDDIR=$(abspath $(GMP_BUILDDIR)) \
		INSTALLDIR=$(abspath $(BUILDDIR))

$(BUILDDIR)/mpc.cma $(BUILDDIR)/mpc.cmxa: $(wildcard ../source/mpc*) $(BUILDDIR)/mpfr.cma $(BUILDDIR)/mpfr.cmxa
	$(MAKE) -C ../source -f Makefile-mpc install \
		BUILDDIR=$(abspath $(GMP_BUILDDIR)) \
		INSTALLDIR=$(abspath $(BUILDDIR))

$(BINLN):
	ln -s $(BUILDDIR) $@

clean:
	-$(MAKE) -C ../source clean uninstall \
		BUILDDIR=$(abspath $(GMP_BUILDDIR)) \
		INSTALLDIR=$(abspath $(BUILDDIR))
	-rm $(BUILDDIR)/*.exe $(BUILDDIR)/*.cm? $(BUILDDIR)/*.o
	-[ -h "$(BINLN)" ] && rm "$(BINLN)"
	-rmdir $(BUILDDIR)/stublibs
	-rmdir $(BUILDDIR)
