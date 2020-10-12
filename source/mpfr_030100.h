/* the additional entities from MPFR 3.0.1 to MPFR 3.1.0 */

static inline void mpfr_frexp(
	mpfr_exp_t *exp,
	mpfr_t y,
	mpfr_t x,
	mpfr_rnd_t rnd)
{
	mpfr_exp_t exponent = mpfr_get_exp(x);
	*exp = exponent;
	if(exponent == 0){
		mpfr_set(y, x, rnd);
	}else if(exponent > 0){
		mpfr_div_2exp(y, x, exponent, rnd);
	}else{
		mpfr_mul_2exp(y, x, -exponent, rnd);
	}
}
