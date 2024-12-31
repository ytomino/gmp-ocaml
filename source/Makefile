.PHONY: all clean install uninstall

define DO=
@echo "**** $1 ****"
$(MAKE) -f $2 $@
endef

WITH=gmp,mpfr,mpc

all clean install uninstall:
	$(and $(findstring gmp,$(WITH)),$(call DO,GMP,Makefile.gmp))
	$(and $(findstring mpfr,$(WITH)),$(wildcard Makefile.mpfr), \
		$(call DO,MPFR,Makefile.mpfr))
	$(and $(findstring mpc,$(WITH)),$(wildcard Makefile.mpc), \
		$(call DO,MPC,Makefile.mpc))
