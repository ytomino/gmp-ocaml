/* the additional entities from MPFR 3.1.6 to MPFR 4.0.0 */

static inline int mpfr_log_ui (mpfr_t rop, unsigned long op, mpfr_rnd_t rnd)
{
	mpfr_set_ui(rop, op, rnd);
	return mpfr_log(rop, rop, rnd);
}

static inline int mpfr_rootn_ui(
	mpfr_t rop,
	mpfr_t op,
	unsigned long int n,
	mpfr_rnd_t rnd)
{
	return mpfr_root(rop, op, n, rnd);
}
