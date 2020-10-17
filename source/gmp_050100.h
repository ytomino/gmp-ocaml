/* the additional entities from MPFR 5.0.0 to MPFR 5.1.0 */

static inline void mpz_2fac_ui(mpz_t rop, unsigned long int n);

static inline void mpz_mfac_uiui(
	mpz_t rop,
	unsigned long int n,
	unsigned long int m)
{
	mpz_set_ui(rop, 1);
	while(n >= m){
		mpz_mul_ui(rop, rop, n);
		n -= m;
	}
}

static inline void mpz_2fac_ui(mpz_t rop, unsigned long int n)
{
	mpz_mfac_uiui(rop, n, 2);
}

static inline void mpz_primorial_ui(mpz_t rop, unsigned long int n)
{
	mpz_set_ui(rop, 1);
	if(n >= 2){
		mpz_t a;
		mpz_init_set_ui(a, 2);
		while(mpz_cmp_ui(a, n) <= 0){
			mpz_mul(rop, rop, a);
			mpz_nextprime(a, a);
		}
		mpz_clear(a);
	}
}
