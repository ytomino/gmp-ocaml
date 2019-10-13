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

.PHONY: all interactive clean

all: \
	$(BUILDDIR)/test_conv.opt.exe \
	$(BUILDDIR)/test_export.opt.exe \
	$(BUILDDIR)/test_marshal.opt.exe \
	$(BUILDDIR)/test_sig.opt.exe \
	$(BUILDDIR)/test_supplied.opt.exe \
	$(BUILDDIR)/essai.byte.exe $(BUILDDIR)/essai.opt.exe \
	$(BUILDDIR)/test_creal.byte.exe $(BUILDDIR)/test_creal.opt.exe \
	$(BUILDDIR)/test_mlgmp.byte.exe $(BUILDDIR)/test_mlgmp.opt.exe \
	$(BUILDDIR)/test_suite.byte.exe $(BUILDDIR)/test_suite.opt.exe \
	$(BINLN)

$(BUILDDIR)/%.opt.exe: %.ml $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma $(BUILDDIR)/mpc.cma
	@echo "**** $< ****"
	ocaml -I $(BUILDDIR) $(OCAMLCFLAGS) gmp.cma mpfr.cma mpc.cma $<
	ocamlc -c -o $(@:.opt.exe=.cmo) -I $(BUILDDIR) $(OCAMLCFLAGS) $<
	ocamlc -o $(@:.opt.exe=.byte.exe) -I $(BUILDDIR) $(OCAMLCFLAGS) gmp.cma mpfr.cma mpc.cma $(@:.opt.exe=.cmo)
	$(@:.opt.exe=.byte.exe)
	ocamlopt -c -o $(@:.opt.exe=.cmx) -I $(BUILDDIR) $(OCAMLCFLAGS) $<
	ocamlopt -o $@ -I $(BUILDDIR) $(OCAMLCFLAGS) gmp.cmxa mpfr.cmxa mpc.cmxa $(@:.opt.exe=.cmx)
	$@

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

interactive: $(BUILDDIR)/gmp.cma $(BUILDDIR)/mpfr.cma $(BUILDDIR)/mpc.cma
	$(RLWRAP) ocaml -I $(BUILDDIR) $(OCAMLCFLAGS) gmp.cma mpfr.cma mpc.cma

$(BUILDDIR)/gmp.cma: $(wildcard ../source/gmp*)
	$(MAKE) -C ../source -f Makefile-gmp install INSTALLDIR=$(abspath $(BUILDDIR))

$(BUILDDIR)/mpfr.cma: $(wildcard ../source/mpfr*) $(BUILDDIR)/gmp.cma
	$(MAKE) -C ../source -f Makefile-mpfr install INSTALLDIR=$(abspath $(BUILDDIR))

$(BUILDDIR)/mpc.cma: $(wildcard ../source/mpc*) $(BUILDDIR)/mpfr.cma
	$(MAKE) -C ../source -f Makefile-mpc install INSTALLDIR=$(abspath $(BUILDDIR))

$(BINLN):
	ln -s $(BUILDDIR) $@

clean:
	-$(MAKE) -C ../source clean uninstall INSTALLDIR=$(abspath $(BUILDDIR))
	-rm $(BUILDDIR)/*.exe $(BUILDDIR)/*.cm? $(BUILDDIR)/*.o
	-rm $(BINLN)
	-rmdir $(BUILDDIR)/stublibs
	-rmdir $(BUILDDIR)
