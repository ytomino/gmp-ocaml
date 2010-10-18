.PHONY: all clean install uninstall

all clean install uninstall:
	@echo "**** GMP ****"
	make -f makefile-gmp $@
ifneq ($(wildcard makefile-mpfr),)
	@echo "**** MPFR ****"
	make -f makefile-mpfr $@
endif
ifneq ($(wildcard makefile-mpc),)
	@echo "**** MPC ****"
	make -f makefile-mpc $@
endif
