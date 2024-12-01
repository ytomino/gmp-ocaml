BUILD:=$(shell $(CC) -dumpmachine)
HOST=$(BUILD)
TARGET=$(HOST)

PROGRAMPREFIX=$(addsuffix -,$(filter-out $(BUILD),$(TARGET)))

OCAMLC=$(PROGRAMPREFIX)ocamlc
OCAMLOPT=$(or $(filter-out $(OCAMLC),$(OCAMLC:c=opt)),$(PROGRAMPREFIX)ocamlopt)
RLWRAP?=

DEBUG=
ASSERT=1

OCAMLCFLAGS=$(and $(filter-out 0,$(DEBUG)),-g)
OCAMLOPTFLAGS=$(OCAMLCFLAGS)
OCAMLCFLAGS_EXE=$(and $(filter-out 0,$(DEBUG)),-g)
OCAMLOPTFLAGS_EXE=$(OCAMLCFLAGS_EXE) $(addprefix -ccopt ,$(LDFLAGS))
OCAML_INCLUDE_FLAGS=
LDFLAGS?=

BUILDSUFFIX=.noindex
BUILDDIR=$(TARGET)$(BUILDSUFFIX)
GMP_BUILDDIR=$(BUILDDIR)/gmp$(BUILDSUFFIX)

BINLN=$(and $(filter $(BUILD),$(TARGET)), \
        $(if $(findstring mingw,$(BUILD))$(findstring msys,$(BUILD)),,bin))

EXAMPLES1=$(basename $(wildcard *.ml))
EXAMPLES=$(EXAMPLES1) essai test_creal test_mlgmp test_suite
TESTS=$(filter test_%,$(EXAMPLES1))

.PHONY: all check interactive clean $(TESTS)

all \
: $(and $(OCAMLC),$(patsubst %,$(BUILDDIR)/%.byte.exe,$(EXAMPLES))) \
  $(and $(OCAMLOPT),$(patsubst %,$(BUILDDIR)/%.opt.exe,$(EXAMPLES))) $(BINLN)

$(BUILDDIR)/%.byte.exe \
: %.ml $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma $(BUILDDIR)/mpc.cma
	$(OCAMLC) $(strip \
		-c $(OCAMLCFLAGS) \
		-o $(BUILDDIR)/$*.cmo $(OCAML_INCLUDE_FLAGS) -I $(BUILDDIR) $<)
	$(OCAMLC) $(strip \
		$(OCAMLCFLAGS_EXE) \
		-o $@ $(OCAML_INCLUDE_FLAGS) -I $(BUILDDIR) gmp.cma mpfr.cma mpc.cma \
		$(BUILDDIR)/$*.cmo)

$(BUILDDIR)/%.opt.exe \
: %.ml $(BUILDDIR)/gmp.cmxa $(BUILDDIR)/mpfr.cmxa $(BUILDDIR)/mpc.cmxa
	$(OCAMLOPT) $(strip \
		-c $(OCAMLOPTFLAGS) \
		-o $(BUILDDIR)/$*.cmx $(OCAML_INCLUDE_FLAGS) -I $(BUILDDIR) $<)
	$(OCAMLOPT) $(strip \
		$(OCAMLOPTFLAGS_EXE) \
		-o $@ $(OCAML_INCLUDE_FLAGS) -I $(BUILDDIR) gmp.cmxa mpfr.cmxa mpc.cmxa \
		$(BUILDDIR)/$*.cmx)

$(BUILDDIR)/gmp2mlgmp.cmo \
: mlgmp/gmp2mlgmp.ml $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma
	$(OCAMLC) $(strip \
		-c $(OCAMLCFLAGS) -o $@ $(OCAML_INCLUDE_FLAGS) -I $(BUILDDIR) $<)

$(BUILDDIR)/gmp2mlgmp.cmx \
: mlgmp/gmp2mlgmp.ml $(BUILDDIR)/gmp.cmxa $(BUILDDIR)/mpfr.cmxa
	$(OCAMLOPT) $(strip \
		-c $(OCAMLOPTFLAGS) -o $@ $(OCAML_INCLUDE_FLAGS) -I $(BUILDDIR) $<)

$(BUILDDIR)/creal.cmi \
: mlgmp/creal.mli \
  $(or \
    $(and $(OCAMLC),$(BUILDDIR)/gmp.cma), \
    $(and $(OCAMLOPT),$(BUILDDIR)/gmp.cmxa))
	$(or \
		$(and $(OCAMLC), \
			$(OCAMLC) $(strip \
				-c $(OCAMLCFLAGS) -o $@ $(OCAML_INCLUDE_FLAGS) -I $(BUILDDIR) $<)), \
		$(and $(OCAMLOPT),\
			$(OCAMLOPT) $(strip \
				-c $(OCAMLOPTFLAGS) -o $@ $(OCAML_INCLUDE_FLAGS) -I $(BUILDDIR) $<)))

$(BUILDDIR)/creal.cmo \
: mlgmp/creal.ml $(BUILDDIR)/creal.cmi $(BUILDDIR)/gmp2mlgmp.cmo
	$(OCAMLC) $(strip \
		-c $(OCAMLCFLAGS) -o $@ $(OCAML_INCLUDE_FLAGS) -I $(BUILDDIR) $<)

$(BUILDDIR)/creal.cmx \
: mlgmp/creal.ml $(BUILDDIR)/creal.cmi $(BUILDDIR)/gmp2mlgmp.cmx
	$(OCAMLOPT) $(strip \
		-c $(OCAMLOPTFLAGS) -o $@ $(OCAML_INCLUDE_FLAGS) -I $(BUILDDIR) $<)

$(BUILDDIR)/%.byte.exe: mlgmp/%.ml $(BUILDDIR)/creal.cmo
	$(OCAMLC) $(strip \
		-c $(OCAMLCFLAGS) \
		$(OCAML_INCLUDE_FLAGS) -I $(BUILDDIR) -o $(BUILDDIR)/$*.cmo $<)
	$(OCAMLC) $(strip \
		$(OCAMLCFLAGS_EXE) \
		-o $@ $(OCAML_INCLUDE_FLAGS) -I $(BUILDDIR) gmp.cma mpfr.cma \
		$(BUILDDIR)/gmp2mlgmp.cmo $(BUILDDIR)/creal.cmo $(BUILDDIR)/$*.cmo)

$(BUILDDIR)/%.opt.exe: mlgmp/%.ml $(BUILDDIR)/creal.cmx
	$(OCAMLOPT) $(strip \
		-c $(OCAMLOPTFLAGS) \
		-o $(BUILDDIR)/$*.cmx $(OCAML_INCLUDE_FLAGS) -I $(BUILDDIR) $<)
	$(OCAMLOPT) $(strip \
		$(OCAMLOPTFLAGS_EXE) \
		-o $@ $(OCAML_INCLUDE_FLAGS) -I $(BUILDDIR) gmp.cmxa mpfr.cmxa \
		$(BUILDDIR)/gmp2mlgmp.cmx $(BUILDDIR)/creal.cmx $(BUILDDIR)/$*.cmx)

check: all $(TESTS)

$(TESTS): % \
: $(and $(OCAMLC),$(BUILDDIR)/%.byte.exe) \
  $(and $(OCAMLOPT),$(BUILDDIR)/%.opt.exe)
	$(and $(OCAMLC),$<)
	$(and $(OCAMLOPT),$(BUILDDIR)/$*.opt.exe)

interactive: $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma $(BUILDDIR)/mpc.cma
	$(RLWRAP) ocaml $(strip \
		$(OCAMLCFLAGS) $(OCAML_INCLUDE_FLAGS) -I $(BUILDDIR) gmp.cma mpfr.cma mpc.cma)

$(and $(OCAMLC),$(BUILDDIR)/gmp.cma) $(and $(OCAMLOPT),$(BUILDDIR)/gmp.cmxa) \
&: ../source/gmp*
	$(MAKE) $(strip \
		-C ../source -f Makefile.gmp install \
		BUILDDIR=$(abspath $(GMP_BUILDDIR)) \
		INSTALLDIR=$(abspath $(BUILDDIR)) \
		ASSERT=$(ASSERT))

$(and $(OCAMLC),$(BUILDDIR)/mpfr.cma) \
$(and $(OCAMLOPT),$(BUILDDIR)/mpfr.cmxa) \
&: ../source/mpfr* \
   $(and $(OCAMLC),$(BUILDDIR)/gmp.cma) $(and $(OCAMLOPT),$(BUILDDIR)/gmp.cmxa)
	$(MAKE) $(strip \
		-C ../source -f Makefile.mpfr install \
		BUILDDIR=$(abspath $(GMP_BUILDDIR)) \
		INSTALLDIR=$(abspath $(BUILDDIR)) \
		ASSERT=$(ASSERT))

$(and $(OCAMLC),$(BUILDDIR)/mpc.cma) $(and $(OCAMLOPT),$(BUILDDIR)/mpc.cmxa) \
&: ../source/mpc* \
   $(and $(OCAMLC),$(BUILDDIR)/mpfr.cma) \
   $(and $(OCAMLOPT),$(BUILDDIR)/mpfr.cmxa)
	$(MAKE) $(strip \
		-C ../source -f Makefile.mpc install \
		BUILDDIR=$(abspath $(GMP_BUILDDIR)) \
		INSTALLDIR=$(abspath $(BUILDDIR)) \
		ASSERT=$(ASSERT))

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
