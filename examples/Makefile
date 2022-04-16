HOST:=$(shell $(CC) -dumpmachine)
TARGET=$(HOST)

ifneq ($(TARGET),$(HOST))
 PROGRAMPREFIX=$(TARGET)-
 BINLN=
else
 PROGRAMPREFIX=
 ifneq ($(findstring mingw,$(HOST))$(findstring msys,$(HOST)),)
  BINLN=
 else
  BINLN=bin
 endif
endif

OCAMLC=$(PROGRAMPREFIX)ocamlc
OCAMLOPT=$(if $(OCAMLC),$(OCAMLC:c=opt),$(PROGRAMPREFIX)ocamlopt)
RLWRAP?=

BUILDSUFFIX=.noindex
BUILDDIR=$(TARGET)$(BUILDSUFFIX)
GMP_BUILDDIR=$(BUILDDIR)/gmp$(BUILDSUFFIX)

EXAMPLES1=$(basename $(wildcard *.ml))
EXAMPLES=$(EXAMPLES1) essai test_creal test_mlgmp test_suite
TESTS=$(filter test_%,$(EXAMPLES1))

.PHONY: all check interacitve clean $(TESTS)

all: \
	$(if $(OCAMLC),$(patsubst %,$(BUILDDIR)/%.byte.exe,$(EXAMPLES))) \
	$(if $(OCAMLOPT),$(patsubst %,$(BUILDDIR)/%.opt.exe,$(EXAMPLES))) \
	$(BINLN)

$(BUILDDIR)/%.byte.exe: %.ml $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma $(BUILDDIR)/mpc.cma
	$(OCAMLC) -c -o $(BUILDDIR)/$*.cmo -I $(BUILDDIR) $(OCAMLCFLAGS) $<
	$(OCAMLC) -o $@ -I $(BUILDDIR) gmp.cma mpfr.cma mpc.cma $(BUILDDIR)/$*.cmo

$(BUILDDIR)/%.opt.exe: %.ml $(BUILDDIR)/gmp.cmxa $(BUILDDIR)/mpfr.cmxa $(BUILDDIR)/mpc.cmxa
	$(OCAMLOPT) -c -o $(BUILDDIR)/$*.cmx -I $(BUILDDIR) $(OCAMLCFLAGS) $<
	$(OCAMLOPT) -o $@ -I $(BUILDDIR) gmp.cmxa mpfr.cmxa mpc.cmxa $(BUILDDIR)/$*.cmx

$(BUILDDIR)/gmp2mlgmp.cmo: mlgmp/gmp2mlgmp.ml $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma
	$(OCAMLC) -c -o $@ -I $(BUILDDIR) $(OCAMLCFLAGS) $<

$(BUILDDIR)/gmp2mlgmp.cmx: mlgmp/gmp2mlgmp.ml $(BUILDDIR)/gmp.cmxa $(BUILDDIR)/mpfr.cmxa
	$(OCAMLOPT) -c -o $@ -I $(BUILDDIR) $(OCAMLCFLAGS) $<

$(BUILDDIR)/creal.cmi: \
		mlgmp/creal.mli $(if $(OCAMLC),$(BUILDDIR)/gmp.cma,$(BUILDDIR)/gmp.cmxa)
	$(or $(OCAMLC),$(OCAMLOPT)) -c -o $@ -I $(BUILDDIR) $(OCAMLCFLAGS) $<

$(BUILDDIR)/creal.cmo: mlgmp/creal.ml $(BUILDDIR)/creal.cmi $(BUILDDIR)/gmp2mlgmp.cmo
	$(OCAMLC) -c -o $@ -I $(BUILDDIR) $(OCAMLCFLAGS) $<

$(BUILDDIR)/creal.cmx: mlgmp/creal.ml $(BUILDDIR)/creal.cmi $(BUILDDIR)/gmp2mlgmp.cmx
	$(OCAMLOPT) -c -o $@ -I $(BUILDDIR) $(OCAMLCFLAGS) $<

$(BUILDDIR)/%.byte.exe: mlgmp/%.ml $(BUILDDIR)/creal.cmo
	$(OCAMLC) -c -o $(BUILDDIR)/$*.cmo -I $(BUILDDIR) $(OCAMLCFLAGS) $<
	$(OCAMLC) -o $@ -I $(BUILDDIR) gmp.cma mpfr.cma $(BUILDDIR)/gmp2mlgmp.cmo $(BUILDDIR)/creal.cmo $(BUILDDIR)/$*.cmo

$(BUILDDIR)/%.opt.exe: mlgmp/%.ml $(BUILDDIR)/creal.cmx
	$(OCAMLOPT) -c -o $(BUILDDIR)/$*.cmx -I $(BUILDDIR) $(OCAMLCFLAGS) $<
	$(OCAMLOPT) -o $@ -I $(BUILDDIR) gmp.cmxa mpfr.cmxa $(BUILDDIR)/gmp2mlgmp.cmx $(BUILDDIR)/creal.cmx $(BUILDDIR)/$*.cmx

check: all $(TESTS)

$(TESTS): %: \
		$(if $(OCAMLC),$(BUILDDIR)/%.byte.exe) $(if $(OCAMLOPT),$(BUILDDIR)/%.opt.exe)
ifneq ($(OCAMLC),)
	$<
endif
ifneq ($(OCAMLOPT),)
	$(patsubst %.byte.exe,%.opt.exe,$<)
endif

interactive: $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma $(BUILDDIR)/mpc.cma
	$(RLWRAP) ocaml -I $(BUILDDIR) $(OCAMLCFLAGS) gmp.cma mpfr.cma mpc.cma

$(BUILDDIR)/gmp.cma $(BUILDDIR)/gmp.cmxa&: $(wildcard ../source/gmp*)
	$(MAKE) -C ../source -f Makefile-gmp install \
		BUILDDIR=$(abspath $(GMP_BUILDDIR)) \
		INSTALLDIR=$(abspath $(BUILDDIR))

$(BUILDDIR)/mpfr.cma $(BUILDDIR)/mpfr.cmxa&: \
		$(wildcard ../source/mpfr*) \
		$(if $(OCAMLC),$(BUILDDIR)/gmp.cma) \
		$(if $(OCAMLOPT),$(BUILDDIR)/gmp.cmxa)
	$(MAKE) -C ../source -f Makefile-mpfr install \
		BUILDDIR=$(abspath $(GMP_BUILDDIR)) \
		INSTALLDIR=$(abspath $(BUILDDIR))

$(BUILDDIR)/mpc.cma $(BUILDDIR)/mpc.cmxa&: \
		$(wildcard ../source/mpc*) \
		$(if $(OCAMLC),$(BUILDDIR)/mpfr.cma) \
		$(if $(OCAMLOPT),$(BUILDDIR)/mpfr.cmxa)
	$(MAKE) -C ../source -f Makefile-mpc install \
		BUILDDIR=$(abspath $(GMP_BUILDDIR)) \
		INSTALLDIR=$(abspath $(BUILDDIR))

$(BINLN):
	ln -s $(BUILDDIR) $@

clean:
	-$(if $(BINLN),[ -h "$(BINLN)" ] && rm "$(BINLN)")
	-$(MAKE) -C ../source clean uninstall \
		BUILDDIR=$(abspath $(GMP_BUILDDIR)) \
		INSTALLDIR=$(abspath $(BUILDDIR))
	-rm $(BUILDDIR)/*.exe $(BUILDDIR)/*.cm? $(BUILDDIR)/*.o
	-rmdir $(BUILDDIR)/stublibs
	-rmdir $(BUILDDIR)
