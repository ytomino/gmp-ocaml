/* the additional entities from MPC 0.9 to MPC 1.0.0 */

//#define MPC_RND RNDC

static inline int mpc_div_2ui(
	mpc_t rop,
	mpc_t op1,
	unsigned long int op2,
	mpc_rnd_t rnd)
{
	return mpc_div_2exp(rop, op1, op2, rnd);
}

static inline int mpc_mul_2ui(
	mpc_t rop,
	mpc_t op1,
	unsigned long int op2,
	mpc_rnd_t rnd)
{
	return mpc_mul_2exp(rop, op1, op2, rnd);
}

static inline void mpc_log10(mpc_t rop, mpc_t op, mpc_rnd_t rnd)
{
	mpc_log(rop, op, rnd);
	mpfr_rnd_t real_rnd = MPC_RND_RE(rnd);
	mpfr_t b;
	mpfr_init2(b, mpfr_get_prec(mpc_realref(rop)));
	mpfr_set_ui(b, 10, real_rnd);
	mpfr_log(b, b, real_rnd);
	mpc_div_fr(rop, rop, b, rnd);
	mpfr_clear(b);
}
