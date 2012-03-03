/* word size */

#define WSIZE_32_FR 16 /* 4 byte int + 4 byte int + 4 byte int + 4 byte pointer */
#define WSIZE_64_FR 32 /* 8 byte int + 4 byte int + 4 byte alignment + 8 byte int + 8 byte pointer */

/* conversions */

#if MPFR_VERSION_MAJOR < 3
#define MPFR_RNDNA GMP_RNDNA
#endif

static inline mpfr_ptr FR_val(value x)
{
	return Data_custom_val(x);
}

static inline mpfr_rnd_t Rnd_val(value x)
{
	switch(x){
	case 0x009d: return GMP_RNDN;
	case 0x00b5: return GMP_RNDZ;
	case 0x00ab: return GMP_RNDU;
	case 0x0089: return GMP_RNDD;
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
	case GMP_RNDN: return 0x009d;
	case GMP_RNDZ: return 0x00b5;
	case GMP_RNDU: return 0x00ab;
	case GMP_RNDD: return 0x0089;
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
	double fra = mpfr_get_d_2exp(&exp, x, GMP_RNDN);
	long result = exp ^ (long)(fra * (double)LONG_MAX);
	return result;
}

/* serialize */

static inline void fr_serialize(mpfr_ptr x)
{
	mp_prec_t prec = mpfr_get_prec(x);
	mp_exp_t exponent;
	char *image = mpfr_get_str (NULL, &exponent, 16, 0, x, GMP_RNDN);
	size_t i_length = strlen(image);
	char exponent_buf[sizeof(mp_exp_t) * 2 + 1];
	size_t e_length = gmp_sprintf(exponent_buf, "%lx", (long)exponent);
	size_t length = e_length + i_length + 3;
	serialize_int_4(prec);
	serialize_int_4(length);
	if(image[0] == '-'){
		serialize_block_1("-0.", 3);
		serialize_block_1(image + 1, i_length - 1);
	}else{
		serialize_block_1("0.", 2);
		serialize_block_1(image, i_length);
	}
	serialize_block_1("@", 1);
	serialize_block_1(exponent_buf, e_length);
	free(image);
}

static inline void fr_deserialize(mpfr_ptr x)
{
	mp_prec_t prec = deserialize_uint_4();
	size_t length = deserialize_uint_4();
	char image[length + 1];
	deserialize_block_1(image, length);
	image[length] = '\0';
	mpfr_init2(x, prec);
	int err = mpfr_set_str(x, image, 16, GMP_RNDN);
	if(err < 0) caml_failwith(__FUNCTION__);
}

/* custom-operations */

extern struct custom_operations mlmpfr_fr_ops;
