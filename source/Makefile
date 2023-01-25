.PHONY: all clean install uninstall

WITH=gmp,mpfr,mpc

all clean install uninstall:

ifneq ($(findstring gmp,$(WITH)),)
	@echo "**** GMP ****"
	$(MAKE) -f Makefile.gmp $@
endif
ifneq ($(findstring mpfr,$(WITH)),)
ifneq ($(wildcard Makefile.mpfr),)
	@echo "**** MPFR ****"
	$(MAKE) -f Makefile.mpfr $@
endif
endif
ifneq ($(findstring mpc,$(WITH)),)
ifneq ($(wildcard Makefile.mpc),)
	@echo "**** MPC ****"
	$(MAKE) -f Makefile.mpc $@
endif
endif
