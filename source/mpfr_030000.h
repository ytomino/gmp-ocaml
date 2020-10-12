/* the additional entities from MPFR 2.4.1 to MPFR 3.0.0 */

#define MPFR_RNDN GMP_RNDN
//#define MPFR_RNDNA GMP_RNDNA

typedef mp_exp_t mpfr_exp_t;

static inline int mpfr_set_flt(mpfr_t rop, float op, mpfr_rnd_t rnd)
{
	return mpfr_set_d(rop, (double)op, rnd);
}

static inline void mpfr_set_zero(mpfr_t x, int sign)
{
	mpfr_set_ui(x, 0, GMP_RNDN);
	mpfr_set4(x, x, GMP_RNDN, sign ? -1 : 1);
}

static inline float mpfr_get_flt(mpfr_t op, mpfr_rnd_t rnd)
{
	return (float)mpfr_get_d(op, rnd);
}
