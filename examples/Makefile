BUILD:=$(shell $(CC) -dumpmachine)
HOST=$(BUILD)
TARGET=$(HOST)

PROGRAMPREFIX=$(addsuffix -,$(filter-out $(BUILD),$(TARGET)))

OCAMLC=$(PROGRAMPREFIX)ocamlc
OCAMLOPT=$(or $(filter-out $(OCAMLC),$(OCAMLC:c=opt)),$(PROGRAMPREFIX)ocamlopt)
RLWRAP?=

OCAMLCFLAGS=
OCAMLOPTFLAGS=$(OCAMLCFLAGS)

BUILDSUFFIX=.noindex
BUILDDIR=$(TARGET)$(BUILDSUFFIX)
GMP_BUILDDIR=$(BUILDDIR)/gmp$(BUILDSUFFIX)

BINLN=$(and $(filter $(BUILD),$(TARGET)), \
        $(if $(findstring mingw,$(BUILD))$(findstring msys,$(BUILD)),,bin))

EXAMPLES1=$(basename $(wildcard *.ml))
EXAMPLES=$(EXAMPLES1) essai test_creal test_mlgmp test_suite
TESTS=$(filter test_%,$(EXAMPLES1))

.PHONY: all check interacitve clean $(TESTS)

all: \
	$(and $(OCAMLC),$(patsubst %,$(BUILDDIR)/%.byte.exe,$(EXAMPLES))) \
	$(and $(OCAMLOPT),$(patsubst %,$(BUILDDIR)/%.opt.exe,$(EXAMPLES))) \
	$(BINLN)

$(BUILDDIR)/%.byte.exe: %.ml $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma $(BUILDDIR)/mpc.cma
	$(OCAMLC) -c $(OCAMLCFLAGS) -o $(BUILDDIR)/$*.cmo -I $(BUILDDIR) $<
	$(OCAMLC) -o $@ -I $(BUILDDIR) gmp.cma mpfr.cma mpc.cma $(BUILDDIR)/$*.cmo

$(BUILDDIR)/%.opt.exe: %.ml $(BUILDDIR)/gmp.cmxa $(BUILDDIR)/mpfr.cmxa $(BUILDDIR)/mpc.cmxa
	$(OCAMLOPT) -c $(OCAMLOPTFLAGS) -o $(BUILDDIR)/$*.cmx -I $(BUILDDIR) $<
	$(OCAMLOPT) -o $@ -I $(BUILDDIR) gmp.cmxa mpfr.cmxa mpc.cmxa $(BUILDDIR)/$*.cmx

$(BUILDDIR)/gmp2mlgmp.cmo: mlgmp/gmp2mlgmp.ml $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma
	$(OCAMLC) -c $(OCAMLCFLAGS) -o $@ -I $(BUILDDIR) $<

$(BUILDDIR)/gmp2mlgmp.cmx: mlgmp/gmp2mlgmp.ml $(BUILDDIR)/gmp.cmxa $(BUILDDIR)/mpfr.cmxa
	$(OCAMLOPT) -c $(OCAMLOPTFLAGS) -o $@ -I $(BUILDDIR) $<

$(BUILDDIR)/creal.cmi: \
		mlgmp/creal.mli \
		$(or \
			$(and $(OCAMLC),$(BUILDDIR)/gmp.cma), \
			$(and $(OCAMLOPT),$(BUILDDIR)/gmp.cmxa))
	$(or \
		$(and $(OCAMLC),$(OCAMLC) -c $(OCAMLCFLAGS) -o $@ -I $(BUILDDIR) $<), \
		$(and $(OCAMLOPT),$(OCAMLOPT) -c $(OCAMLOPTFLAGS) -o $@ -I $(BUILDDIR) $<))

$(BUILDDIR)/creal.cmo: mlgmp/creal.ml $(BUILDDIR)/creal.cmi $(BUILDDIR)/gmp2mlgmp.cmo
	$(OCAMLC) -c $(OCAMLCFLAGS) -o $@ -I $(BUILDDIR) $<

$(BUILDDIR)/creal.cmx: mlgmp/creal.ml $(BUILDDIR)/creal.cmi $(BUILDDIR)/gmp2mlgmp.cmx
	$(OCAMLOPT) -c $(OCAMLOPTFLAGS) -o $@ -I $(BUILDDIR) $<

$(BUILDDIR)/%.byte.exe: mlgmp/%.ml $(BUILDDIR)/creal.cmo
	$(OCAMLC) -c $(OCAMLCFLAGS) -I $(BUILDDIR) -o $(BUILDDIR)/$*.cmo $<
	$(OCAMLC) $(strip \
		-o $@ -I $(BUILDDIR) gmp.cma mpfr.cma \
		$(BUILDDIR)/gmp2mlgmp.cmo $(BUILDDIR)/creal.cmo $(BUILDDIR)/$*.cmo)

$(BUILDDIR)/%.opt.exe: mlgmp/%.ml $(BUILDDIR)/creal.cmx
	$(OCAMLOPT) -c $(OCAMLOPTFLAGS) -o $(BUILDDIR)/$*.cmx -I $(BUILDDIR) $<
	$(OCAMLOPT) $(strip \
		-o $@ -I $(BUILDDIR) gmp.cmxa mpfr.cmxa \
		$(BUILDDIR)/gmp2mlgmp.cmx $(BUILDDIR)/creal.cmx $(BUILDDIR)/$*.cmx)

check: all $(TESTS)

$(TESTS): %: \
		$(and $(OCAMLC),$(BUILDDIR)/%.byte.exe) \
		$(and $(OCAMLOPT),$(BUILDDIR)/%.opt.exe)
	$(and $(OCAMLC),$<)
	$(and $(OCAMLOPT),$(BUILDDIR)/$*.opt.exe)

interactive: $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma $(BUILDDIR)/mpc.cma
	$(RLWRAP) ocaml $(OCAMLCFLAGS) -I $(BUILDDIR) gmp.cma mpfr.cma mpc.cma

$(and $(OCAMLC),$(BUILDDIR)/gmp.cma) \
$(and $(OCAMLOPT),$(BUILDDIR)/gmp.cmxa)&: \
		../source/gmp*
	$(MAKE) $(strip \
		-C ../source -f Makefile.gmp install \
		BUILDDIR=$(abspath $(GMP_BUILDDIR)) \
		INSTALLDIR=$(abspath $(BUILDDIR)))

$(and $(OCAMLC),$(BUILDDIR)/mpfr.cma) \
$(and $(OCAMLOPT),$(BUILDDIR)/mpfr.cmxa)&: \
		../source/mpfr* \
		$(and $(OCAMLC),$(BUILDDIR)/gmp.cma) \
		$(and $(OCAMLOPT),$(BUILDDIR)/gmp.cmxa)
	$(MAKE) $(strip \
		-C ../source -f Makefile.mpfr install \
		BUILDDIR=$(abspath $(GMP_BUILDDIR)) \
		INSTALLDIR=$(abspath $(BUILDDIR)))

$(and $(OCAMLC),$(BUILDDIR)/mpc.cma) \
$(and $(OCAMLOPT),$(BUILDDIR)/mpc.cmxa)&: \
		../source/mpc* \
		$(and $(OCAMLC),$(BUILDDIR)/mpfr.cma) \
		$(and $(OCAMLOPT),$(BUILDDIR)/mpfr.cmxa)
	$(MAKE) $(strip \
		-C ../source -f Makefile.mpc install \
		BUILDDIR=$(abspath $(GMP_BUILDDIR)) \
		INSTALLDIR=$(abspath $(BUILDDIR)))

$(BINLN):
	ln -s $(BUILDDIR) $@

clean:
	-$(and $(BINLN),[ -h "$(BINLN)" ] && rm "$(BINLN)")
	-$(MAKE) $(strip \
		-C ../source clean uninstall \
		BUILDDIR=$(abspath $(GMP_BUILDDIR)) \
		INSTALLDIR=$(abspath $(BUILDDIR)))
	-rm $(BUILDDIR)/*.exe $(BUILDDIR)/*.cm? $(BUILDDIR)/*.o
	-rmdir $(BUILDDIR)/stublibs
	-rmdir $(BUILDDIR)
