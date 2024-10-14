#include <caml/fail.h>
#include <caml/intext.h>
#include <limits.h>
#include <mpfr.h>

/* word size */

#define WSIZE_32_FR 16
	/* 4 byte int + 4 byte int + 4 byte int + 4 byte pointer */
#define WSIZE_64_FR 32
	/* 8 byte int + 4 byte int + 4 byte alignment + 8 byte int + 8 byte pointer */

/* conversions */

#if MPFR_VERSION_MAJOR < 3
#define MPFR_RNDN GMP_RNDN
#define MPFR_RNDZ GMP_RNDZ
#define MPFR_RNDU GMP_RNDU
#define MPFR_RNDD GMP_RNDD
#define MPFR_RNDNA GMP_RNDNA
#endif

static inline mpfr_ptr FR_val(value x)
{
	return Data_custom_val(x);
}

static inline mpfr_rnd_t Rnd_val(value x)
{
	switch(x){
	case 0x009d: return MPFR_RNDN;
	case 0x00b5: return MPFR_RNDZ;
	case 0x00ab: return MPFR_RNDU;
	case 0x0089: return MPFR_RNDD;
#if MPFR_VERSION_MAJOR >= 3
	case 0x0083: return MPFR_RNDA;
	case 0x008d: return MPFR_RNDF;
#endif
	case 0x8867: return MPFR_RNDNA;
	default: caml_failwith(__FUNCTION__);
	}
}

static inline value Val_rnd(mpfr_rnd_t x)
{
	switch(x){
	case MPFR_RNDN: return 0x009d;
	case MPFR_RNDZ: return 0x00b5;
	case MPFR_RNDU: return 0x00ab;
	case MPFR_RNDD: return 0x0089;
#if MPFR_VERSION_MAJOR >= 3
	case MPFR_RNDA: return 0x0083;
	case MPFR_RNDF: return 0x008d;
#endif
	case MPFR_RNDNA: return 0x8867;
	default: caml_failwith(__FUNCTION__);
	}
}

/* hash */

static inline long fr_hash(mpfr_ptr x)
{
	long exp;
	double fra = mpfr_get_d_2exp(&exp, x, MPFR_RNDN);
	long result = exp ^ (long)(fra * (double)LONG_MAX);
	return result;
}

/* supplied */

CAMLextern void mlmpfr_mpfr_si_pow_si(
	mpfr_ptr rop, long op1, long op2, mpfr_rnd_t rnd);

/* custom-operations */

CAMLextern void mlmpfr_caml_serialize_fr(mpfr_ptr x);
CAMLextern void mlmpfr_caml_deserialize_fr(mpfr_ptr x);

extern struct custom_operations mlmpfr_fr_ops;

/* allocators */

CAMLextern value mlmpfr_alloc_fr_init2(mpfr_prec_t prec);
