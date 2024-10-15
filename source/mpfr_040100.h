/* the additional entities from MPFR 4.0.2 to MPFR 4.1.0 */

static inline size_t mpfr_get_str_ndigits(int b, mpfr_prec_t p)
{
	return mlgmp_mpf_get_str_ndigits(b, p);
}
