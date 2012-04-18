.PHONY: all clean install uninstall

WITH=gmp,mpfr,mpc

all clean install uninstall:

ifneq ($(findstring gmp,$(WITH)),)
	@echo "**** GMP ****"
	make -f makefile-gmp $@
endif
ifneq ($(findstring mpfr,$(WITH)),)
ifneq ($(wildcard makefile-mpfr),)
	@echo "**** MPFR ****"
	make -f makefile-mpfr $@
endif
endif
ifneq ($(findstring mpc,$(WITH)),)
ifneq ($(wildcard makefile-mpc),)
	@echo "**** MPC ****"
	make -f makefile-mpc $@
endif
endif
