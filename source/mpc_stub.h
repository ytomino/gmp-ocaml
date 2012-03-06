/* word size */

#define WSIZE_32_C (WSIZE_32_FR * 2)
#define WSIZE_64_C (WSIZE_64_FR * 2)

/* conversions */

static inline mpc_ptr C_val(value x)
{
	return Data_custom_val(x);
}

static inline mpc_rnd_t Crnd_val(value x)
{
	int re = Rnd_val(Field(x, 0));
	int im = Rnd_val(Field(x, 1));
	return RNDC(re, im);
}

/* hash */

static inline long c_hash(mpc_ptr x)
{
	return fr_hash(mpc_realref(x)) ^ fr_hash(mpc_imagref(x));
}

/* serialize */

static inline void c_serialize(mpc_ptr x)
{
	fr_serialize(mpc_realref(x));
	fr_serialize(mpc_imagref(x));
}

static inline void c_deserialize(mpc_ptr x)
{
	fr_deserialize(mpc_realref(x));
	fr_deserialize(mpc_imagref(x));
}

/* custom-operations */

extern struct custom_operations mlmpc_c_ops;

/* allocators */

CAMLextern value mlmpc_alloc_c_init3(mpfr_prec_t prec_r, mpfr_prec_t prec_i);
