#include <caml/fail.h>
#include <caml/intext.h>
#include <limits.h>
#include <gmp.h>

/* limits.h */

#ifndef LONG_BIT
#define LONG_BIT (SIZEOF_LONG * 8)
	/* defined in caml/config.h */
#endif

/* word size */

#define WSIZE_32_Z 12
	/* 4 byte int + 4 byte int + 4 byte pointer */
#define WSIZE_64_Z 16
	/* 4 byte int + 4 byte int + 8 byte pointer */

#define WSIZE_32_Q (WSIZE_32_Z * 2)
#define WSIZE_64_Q (WSIZE_64_Z * 2)

#define WSIZE_32_F 16
	/* 4 byte int + 4 byte int + 4 byte int + 4 byte pointer */
#define WSIZE_64_F 24
	/* 4 byte int + 4 byte int + 8 byte int + 8 byte pointer */

/* conversions */

static inline mpz_ptr Z_val(value x)
{
	return Data_custom_val(x);
}

static inline mpq_ptr Q_val(value x)
{
	return Data_custom_val(x);
}

static inline mpf_ptr F_val(value x)
{
	return Data_custom_val(x);
}

static inline __gmp_randstate_struct *Random_val(value x)
{
	return Data_custom_val(x);
}

static inline int Order_val(value x)
{
	switch(x){
	case 0x0085: return 1; /* most significant first */
	case 0x0099: return -1; /* least significant first */
	case 0x009d: /* native */
#if defined(__BYTE_ORDER__)
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		return -1;
#else
		return 1;
#endif
#endif
	default: caml_failwith(__FUNCTION__);
	}
}

/* hash */

#define HASH_MODULUS 4294967291UL
	/* compatibility for Caml-GMP */

static inline long z_hash(mpz_ptr x)
{
	return mpz_fdiv_ui(x, HASH_MODULUS);
}

static inline long q_hash(mpq_ptr x)
{
	return z_hash(mpq_numref(x)) ^ z_hash(mpq_denref(x));
}

static inline long f_hash(mpf_ptr x)
{
	long exp;
	double fra = mpf_get_d_2exp(&exp, x);
	long result = exp ^ (long)(fra * (double)LONG_MAX);
	return result;
}

#if __GNU_MP_RELEASE < 50000
typedef unsigned long int mp_bitcnt_t;
#endif

/* custom-operations */

extern struct custom_operations mlgmp_z_ops;
extern struct custom_operations mlgmp_q_ops;
extern struct custom_operations mlgmp_f_ops;

/* allocators */

CAMLextern value mlgmp_alloc_z_init(void);
CAMLextern value mlgmp_alloc_q_init(void);
CAMLextern value mlgmp_alloc_f_init2(mp_bitcnt_t prec);
