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
INSTALLDIR=$(BUILDDIR)

OCAML_BUILDDIR_FLAGS=$(addprefix -I , \
                       $(BUILDDIR) \
                       $(filter-out $(BUILDDIR),$(INSTALLDIR)))

GMP_BUILDDIR=$(BUILDDIR)/gmp$(BUILDSUFFIX)
GMP_WORLD=$(and $(OCAMLC),$(INSTALLDIR)/gmp.cma) \
          $(and $(OCAMLOPT),$(INSTALLDIR)/gmp.cmxa)
MPFR_WORLD=$(and $(OCAMLC),$(INSTALLDIR)/mpfr.cma) \
           $(and $(OCAMLOPT),$(INSTALLDIR)/mpfr.cmxa)
MPC_WORLD=$(and $(OCAMLC),$(INSTALLDIR)/mpc.cma) \
          $(and $(OCAMLOPT),$(INSTALLDIR)/mpc.cmxa)

BINLN=$(and $(filter $(BUILD),$(TARGET)), \
        $(if $(findstring mingw,$(BUILD))$(findstring msys,$(BUILD)),,bin))

EXAMPLES1=$(basename $(wildcard *.ml))
EXAMPLES=$(EXAMPLES1) essai test_creal test_mlgmp test_suite
TESTS=$(filter test_%,$(EXAMPLES1))

EXAMPLES_BYTE=$(and $(OCAMLC),$(patsubst %,$(BUILDDIR)/%.byte.exe,$(EXAMPLES)))
EXAMPLES_OPT=$(and $(OCAMLOPT),$(patsubst %,$(BUILDDIR)/%.opt.exe,$(EXAMPLES)))

.PHONY: all world check interactive clean $(TESTS)

all: $(EXAMPLES_BYTE) $(EXAMPLES_OPT) $(BINLN)

$(EXAMPLES_BYTE): $(BUILDDIR)/%.byte.exe:
	$(OCAMLC) $(strip \
		-c $(OCAMLCFLAGS) \
		-o $(BUILDDIR)/$*.cmo $(OCAML_BUILDDIR_FLAGS) $(OCAML_INCLUDE_FLAGS) \
		$<)
	$(OCAMLC) $(strip \
		$(OCAMLCFLAGS_EXE) -o $@ $(OCAML_BUILDDIR_FLAGS) $(OCAML_INCLUDE_FLAGS) \
		$(notdir $(filter-out $<,$^)) $*.cmo)

$(EXAMPLES_OPT): $(BUILDDIR)/%.opt.exe:
	$(OCAMLOPT) $(strip \
		-c $(OCAMLOPTFLAGS) \
		-o $(BUILDDIR)/$*.cmx $(OCAML_BUILDDIR_FLAGS) $(OCAML_INCLUDE_FLAGS) \
		$<)
	$(OCAMLOPT) $(strip \
		$(OCAMLOPTFLAGS_EXE) -o $@ $(OCAML_BUILDDIR_FLAGS) $(OCAML_INCLUDE_FLAGS) \
		$(notdir $(filter-out $<,$^)) $*.cmx)

$(patsubst %,$(BUILDDIR)/%.opt.exe,$(EXAMPLES1)): $(BUILDDIR)/%.opt.exe \
: %.ml $(INSTALLDIR)/gmp.cmxa $(INSTALLDIR)/mpfr.cmxa $(INSTALLDIR)/mpc.cmxa \
| $(BUILDDIR)
$(patsubst %,$(BUILDDIR)/%.byte.exe,$(EXAMPLES1)): $(BUILDDIR)/%.byte.exe \
: %.ml $(INSTALLDIR)/gmp.cma $(INSTALLDIR)/mpfr.cma $(INSTALLDIR)/mpc.cma \
| $(BUILDDIR)

$(BUILDDIR)/essai.byte.exe $(BUILDDIR)/test_creal.byte.exe \
$(BUILDDIR)/test_mlgmp.byte.exe $(BUILDDIR)/test_suite.byte.exe \
: $(BUILDDIR)/%.byte.exe \
: mlgmp/%.ml $(INSTALLDIR)/gmp.cma $(INSTALLDIR)/mpfr.cma \
  $(BUILDDIR)/gmp2mlgmp.cmo
$(BUILDDIR)/essai.opt.exe $(BUILDDIR)/test_creal.opt.exe \
$(BUILDDIR)/test_mlgmp.opt.exe $(BUILDDIR)/test_suite.opt.exe \
: $(BUILDDIR)/%.opt.exe \
: mlgmp/%.ml $(INSTALLDIR)/gmp.cmxa $(INSTALLDIR)/mpfr.cmxa \
  $(BUILDDIR)/gmp2mlgmp.cmx

$(BUILDDIR)/test_creal.byte.exe: $(BUILDDIR)/creal.cmo
$(BUILDDIR)/test_creal.opt.exe: $(BUILDDIR)/creal.cmx

$(BUILDDIR)/gmp2mlgmp.cmo $(BUILDDIR)/creal.cmo:
	$(OCAMLC) $(strip \
		-c $(OCAMLCFLAGS) -o $@ $(OCAML_BUILDDIR_FLAGS) $(OCAML_INCLUDE_FLAGS) $<)

$(BUILDDIR)/gmp2mlgmp.cmx $(BUILDDIR)/creal.cmx:
	$(OCAMLOPT) $(strip \
		-c $(OCAMLOPTFLAGS) -o $@ $(OCAML_BUILDDIR_FLAGS) $(OCAML_INCLUDE_FLAGS) $<)

$(BUILDDIR)/gmp2mlgmp.cmo \
: mlgmp/gmp2mlgmp.ml $(INSTALLDIR)/mpfr.cma | $(BUILDDIR)
$(BUILDDIR)/gmp2mlgmp.cmx \
: mlgmp/gmp2mlgmp.ml $(INSTALLDIR)/mpfr.cmxa | $(BUILDDIR)

$(BUILDDIR)/creal.cmo \
: mlgmp/creal.ml $(BUILDDIR)/creal.cmi $(BUILDDIR)/gmp2mlgmp.cmo
$(BUILDDIR)/creal.cmx \
: mlgmp/creal.ml $(BUILDDIR)/creal.cmi $(BUILDDIR)/gmp2mlgmp.cmx

$(BUILDDIR)/creal.cmi \
: mlgmp/creal.mli \
  $(or \
    $(and $(OCAMLC),$(INSTALLDIR)/gmp.cma), \
    $(and $(OCAMLOPT),$(INSTALLDIR)/gmp.cmxa)) \
| $(BUILDDIR)
	$(or \
		$(and $(OCAMLC), \
			$(OCAMLC) $(strip \
				-c $(OCAMLCFLAGS) -o $@ $(OCAML_BUILDDIR_FLAGS) $(OCAML_INCLUDE_FLAGS) $<)), \
		$(and $(OCAMLOPT), \
			$(OCAMLOPT) $(strip \
				-c $(OCAMLOPTFLAGS) -o $@ $(OCAML_BUILDDIR_FLAGS) $(OCAML_INCLUDE_FLAGS) $<)))

$(GMP_WORLD)&: ../source/gmp*
	$(MAKE) $(strip \
		-C ../source -f Makefile.gmp install \
		BUILDDIR=$(abspath $(GMP_BUILDDIR)) \
		INSTALLDIR=$(abspath $(INSTALLDIR)) \
		ASSERT=$(ASSERT))

$(MPFR_WORLD)&: ../source/mpfr* $(GMP_WORLD)
	$(MAKE) $(strip \
		-C ../source -f Makefile.mpfr install \
		BUILDDIR=$(abspath $(GMP_BUILDDIR)) \
		INSTALLDIR=$(abspath $(INSTALLDIR)) \
		ASSERT=$(ASSERT))

$(MPC_WORLD)&: ../source/mpc* $(MPFR_WORLD)
	$(MAKE) $(strip \
		-C ../source -f Makefile.mpc install \
		BUILDDIR=$(abspath $(GMP_BUILDDIR)) \
		INSTALLDIR=$(abspath $(INSTALLDIR)) \
		ASSERT=$(ASSERT))

$(BUILDDIR):
	mkdir -p $@

$(BINLN):
	ln -s $(BUILDDIR) $@

world: $(GMP_WORLD) $(MPFR_WORLD) $(MPC_WORLD)

check: all $(TESTS)

$(TESTS): % \
: $(and $(OCAMLC),$(BUILDDIR)/%.byte.exe) \
  $(and $(OCAMLOPT),$(BUILDDIR)/%.opt.exe)
	$(and $(OCAMLC),$<)
	$(and $(OCAMLOPT),$(BUILDDIR)/$*.opt.exe)

interactive: $(INSTALLDIR)/gmp.cma $(INSTALLDIR)/mpfr.cma $(INSTALLDIR)/mpc.cma
	$(RLWRAP) ocaml $(strip \
		$(OCAML_BUILDDIR_FLAGS) $(OCAML_INCLUDE_FLAGS) $(notdir $^))

clean:
	-$(and $(BINLN),[ -h "$(BINLN)" ] && rm "$(BINLN)")
	-$(MAKE) $(strip \
		-C ../source clean $(and $(filter $(BUILDDIR),$(INSTALLDIR)),uninstall) \
		BUILDDIR=$(abspath $(GMP_BUILDDIR)) \
		$(addprefix INSTALLDIR=,$(abspath $(filter $(BUILDDIR),$(INSTALLDIR)))))
	-rm $(BUILDDIR)/*.exe $(BUILDDIR)/*.cm? $(BUILDDIR)/*.o
	-$(patsubst %,rmdir %/stublibs,$(filter $(BUILDDIR),$(INSTALLDIR)))
	-rmdir $(BUILDDIR)
