#include "mpfr_stub.h"

#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdint.h>
#include "gmp_stub.h"

/* for version < 4.0.0 */

#if MPFR_VERSION < 0x040000
#if MPFR_VERSION < 0x030100
#if MPFR_VERSION < 0x030000
#include "mpfr_030000.h"
#endif
#include "mpfr_030100.h"
#endif
#include "mpfr_040000.h"
#endif

/* supplied */

CAMLexport void mlmpfr_mpfr_si_pow_si(
	mpfr_ptr rop, long op1, long op2, mpfr_rnd_t rnd)
{
	if(op1 == 2){
		mpfr_set_si_2exp(rop, 1, op2, rnd);
	}else if(op1 < 0){
		if(op2 < 0){
			mpfr_ui_pow_ui(rop, -op1, -op2, rnd);
			mpfr_si_div(rop, (op2 % 2 != 0) ? -1 : 1, rop, rnd);
		}else{
			mpfr_ui_pow_ui(rop, -op1, op2, rnd);
			if(op2 % 2 != 0){
				mpfr_neg(rop, rop, rnd);
			}
		}
	}else{
		if(op2 < 0){
			mpfr_ui_pow_ui(rop, op1, -op2, rnd);
			mpfr_ui_div(rop, 1, rop, rnd);
		}else{
			mpfr_ui_pow_ui(rop, op1, op2, rnd);
		}
	}
}

/* version functions */

CAMLprim value mlmpfr_compiled_version(value unit)
{
	CAMLparam1(unit);
	CAMLlocal1(result);
	result = caml_alloc_tuple(3);
	Store_field(result, 0, Val_int(MPFR_VERSION_MAJOR));
	Store_field(result, 1, Val_int(MPFR_VERSION_MINOR));
	Store_field(result, 2, Val_int(MPFR_VERSION_PATCHLEVEL));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_compiled_version_string(value unit)
{
	CAMLparam1(unit);
	CAMLlocal1(result);
	result = caml_copy_string(MPFR_VERSION_STRING);
	CAMLreturn(result);
}

CAMLprim value mlmpfr_get_version_string(value unit)
{
	CAMLparam1(unit);
	CAMLlocal1(result);
	result = caml_copy_string(mpfr_get_version());
	CAMLreturn(result);
}

/**** FR ****/

/* custom data */

static void mlmpfr_fr_finalize(value x)
{
	mpfr_clear(FR_val(x));
}

static int mlmpfr_fr_custom_compare(value left, value right)
{
	CAMLparam2(left, right);
	int result = mpfr_cmp(FR_val(left), FR_val(right));
	CAMLreturnT(int, result);
}

static long mlmpfr_fr_hash(value x)
{
	CAMLparam1(x);
	long result = fr_hash(FR_val(x));
	CAMLreturnT(long, result);
}

static void mlmpfr_fr_serialize(value x,
	unsigned long *wsize_32, unsigned long *wsize_64)
{
	CAMLparam1(x);
	*wsize_32 = WSIZE_32_FR;
	*wsize_64 = WSIZE_64_FR;
	fr_serialize(FR_val(x));
	CAMLreturn0;
}

static unsigned long mlmpfr_fr_deserialize(void *dst)
{
	CAMLparam0();
	fr_deserialize((mpfr_ptr)dst);
	CAMLreturnT(unsigned long, sizeof(mpfr_t));
}

struct custom_operations mlmpfr_fr_ops = {
	.identifier = "jp.halfmoon.panathenaia.mpfr.fr",
	.finalize = mlmpfr_fr_finalize,
	.compare = mlmpfr_fr_custom_compare,
	.hash = mlmpfr_fr_hash,
	.serialize = mlmpfr_fr_serialize,
	.deserialize = mlmpfr_fr_deserialize};

CAMLexport value mlmpfr_alloc_fr_init2(mpfr_prec_t prec)
{
	CAMLparam0();
	CAMLlocal1(result);
	result = caml_alloc_custom(&mlmpfr_fr_ops, sizeof(mpfr_t), 0, 1);
	mpfr_init2(FR_val(result), prec);
	CAMLreturn(result);
}

/* functions */

CAMLprim value mlmpfr_fr_compare(value left, value right)
{
	CAMLparam2(left, right);
	int result = mpfr_cmp(FR_val(left), FR_val(right));
	CAMLreturn(Val_int(result));
}

CAMLprim value mlmpfr_fr_compare_int(value left, value right)
{
	CAMLparam2(left, right);
	int result = mpfr_cmp_si(FR_val(left), Long_val(right));
	CAMLreturn(Val_int(result));
}

CAMLprim value mlmpfr_fr_neg(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_neg(FR_val(result), FR_val(x), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_abs(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_abs(FR_val(result), FR_val(x), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_add(value prec, value mode, value left, value right)
{
	CAMLparam4(prec, mode, left, right);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_add(FR_val(result), FR_val(left), FR_val(right), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_add_int(
	value prec,
	value mode,
	value left,
	value right)
{
	CAMLparam4(prec, mode, left, right);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_add_si(FR_val(result), FR_val(left), Long_val(right), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_sub(value prec, value mode, value left, value right)
{
	CAMLparam4(prec, mode, left, right);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_sub(FR_val(result), FR_val(left), FR_val(right), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_sub_int(
	value prec,
	value mode,
	value left,
	value right)
{
	CAMLparam4(prec, mode, left, right);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_sub_si(FR_val(result), FR_val(left), Long_val(right), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_mul(value prec, value mode, value left, value right)
{
	CAMLparam4(prec, mode, left, right);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_mul(FR_val(result), FR_val(left), FR_val(right), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_mul_int(
	value prec,
	value mode,
	value left,
	value right)
{
	CAMLparam4(prec, mode, left, right);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_mul_si(FR_val(result), FR_val(left), Long_val(right), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_div(value prec, value mode, value left, value right)
{
	CAMLparam4(prec, mode, left, right);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_div(FR_val(result), FR_val(left), FR_val(right), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_fma(
	value val_prec,
	value val_mode,
	value val_x,
	value val_y,
	value val_z)
{
	CAMLparam5(val_prec, val_mode, val_x, val_y, val_z);
	CAMLlocal1(val_result);
	val_result = mlmpfr_alloc_fr_init2(Long_val(val_prec));
	mpfr_fma(
		FR_val(val_result),
		FR_val(val_x),
		FR_val(val_y),
		FR_val(val_z),
		Rnd_val(val_mode));
	CAMLreturn(val_result);
}

CAMLprim value mlmpfr_fr_pow_int(
	value prec,
	value mode,
	value base,
	value exponent)
{
	CAMLparam4(prec, mode, base, exponent);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_pow_si(FR_val(result), FR_val(base), Long_val(exponent), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_int_pow_int(
	value prec,
	value mode,
	value base,
	value exponent)
{
	CAMLparam4(prec, mode, base, exponent);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mlmpfr_mpfr_si_pow_si(
		FR_val(result), Long_val(base), Long_val(exponent), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_scale(
	value prec,
	value mode,
	value fraction,
	value base,
	value exponent)
{
	CAMLparam5(prec, mode, fraction, base, exponent);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_ptr result_value = FR_val(result);
	mpfr_rnd_t m = Rnd_val(mode);
	mpfr_ptr f = FR_val(fraction);
	long b = Long_val(base);
	long e = Long_val(exponent);
	if(b == 2){
		if(e >= 0){
			mpfr_mul_2exp(result_value, f, e, m);
		}else{
			mpfr_div_2exp(result_value, f, -e, m);
		}
	}else{
		mpz_t a;
		mpz_init(a);
		if(e >= 0){
			mpz_ui_pow_ui(a, b, e);
			mpfr_mul_z(result_value, f, a, m);
		}else{
			mpz_ui_pow_ui(a, b, -e);
			mpfr_div_z(result_value, f, a, m);
		}
		mpz_clear(a);
	}
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_root(value prec, value mode, value nth, value x)
{
	CAMLparam4(prec, mode, nth, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_rootn_ui(FR_val(result), FR_val(x), Long_val(nth), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_sqrt(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_sqrt(FR_val(result), FR_val(x), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_nearly_equal(value bits, value left, value right)
{
	CAMLparam2(left, right);
	bool result = mpfr_eq(FR_val(left), FR_val(right), Long_val(bits));
	CAMLreturn(Val_bool(result));
}

CAMLprim value mlmpfr_fr_frexp(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal2(result, result_fraction);
	mpfr_exp_t exponent;
	result_fraction = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_frexp(&exponent, FR_val(result_fraction), FR_val(x), Rnd_val(mode));
	result = caml_alloc_tuple(2);
	Store_field(result, 0, result_fraction);
	Store_field(result, 1, Val_long(exponent));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_trunc(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_trunc(FR_val(result), FR_val(x));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_ceil(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_ceil(FR_val(result), FR_val(x));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_floor(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_floor(FR_val(result), FR_val(x));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_is_infinite(value prec, value x)
{
	CAMLparam2(prec, x);
	bool result = mpfr_inf_p(FR_val(x));
	CAMLreturn(Val_bool(result));
}

CAMLprim value mlmpfr_fr_pi(value prec, value mode)
{
	CAMLparam2(prec, mode);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_const_pi(FR_val(result), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_log(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_log(FR_val(result), FR_val(x), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_based_log(value prec, value mode, value base, value x)
{
	CAMLparam4(prec, mode, base, x);
	CAMLlocal1(result);
	mpfr_exp_t p = Long_val(prec);
	result = mlmpfr_alloc_fr_init2(p);
	mpfr_ptr result_value = FR_val(result);
	mpfr_rnd_t m = Rnd_val(mode);
	long b = Long_val(base);
	mpfr_ptr x_value = FR_val(x);
	if(b == 2){
		mpfr_log2(result_value, x_value, m);
	}else if(b == 10){
		mpfr_log10(result_value, x_value, m);
	}else if(b == 16){
		mpfr_log2(result_value, x_value, m);
		mpfr_div_ui(result_value, result_value, 4, m);
	}else{
		mpfr_log(result_value, x_value, m);
		mpfr_t base_value;
		mpfr_init2(base_value, p);
		mpfr_log_ui(base_value, b, m);
		mpfr_div(result_value, result_value, base_value, m);
		mpfr_clear(base_value);
	}
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_pow(
	value prec,
	value mode,
	value base,
	value exponent)
{
	CAMLparam4(prec, mode, base, exponent);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_pow(FR_val(result), FR_val(base), FR_val(exponent), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_exp(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_exp(FR_val(result), FR_val(x), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_sin(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_sin(FR_val(result), FR_val(x), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_cos(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_cos(FR_val(result), FR_val(x), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_tan(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_tan(FR_val(result), FR_val(x), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_atan(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_atan(FR_val(result), FR_val(x), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_atan2(value prec, value mode, value y, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_atan2(FR_val(result), FR_val(y), FR_val(x), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_acosh(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_acosh(FR_val(result), FR_val(x), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_of_based_string(
	value prec,
	value mode,
	value base,
	value x)
{
	CAMLparam4(prec, mode, base, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	int err = mpfr_set_str(
		FR_val(result),
		String_val(x),
		Int_val(base),
		Rnd_val(mode));
	if(err < 0) caml_failwith(__FUNCTION__);
	CAMLreturn(result);
}

CAMLprim value mlmpfr_based_string_of_fr(value mode, value base, value x)
{
	CAMLparam3(mode, base, x);
	CAMLlocal1(result);
	mpfr_ptr x_value = FR_val(x);
	if(mpfr_nan_p(x_value)){
		result = caml_copy_string("nan");
	}else if(mpfr_inf_p(x_value)){
		result = caml_copy_string((char const *)"-inf" + 1 - mpfr_signbit(x_value));
	}else{
		mp_exp_t exponent;
		char *image = mpfr_get_str(
			NULL,
			&exponent,
			Int_val(base),
			0,
			x_value,
			Rnd_val(mode));
		ssize_t length = strlen(image);
		int sign_width = image[0] == '-'; /* 0 or 1 */
		mp_exp_t exponent_p = exponent + sign_width;
		if(length == 0){
			result = caml_copy_string("0.");
		}else if(exponent_p >= length){
			char buf[exponent_p + 2];
			memcpy(buf, image, length);
			memset(buf + length, '0', exponent_p - length);
			buf[exponent_p] = '.';
			buf[exponent_p + 1] = '\0';
			result = caml_copy_string(buf);
		}else if(exponent_p > 0){
			char buf[length + 2];
			memcpy(buf, image, exponent_p);
			buf[exponent_p] = '.';
			memcpy(buf + exponent_p + 1, image + exponent_p, length - exponent_p);
			buf[length + 1] = '\0';
			result = caml_copy_string(buf);
		}else{
			char buf[length - exponent + 3];
			if(sign_width > 0) buf[0] = '-';
			buf[sign_width] = '0';
			buf[sign_width + 1] = '.';
			memset(buf + sign_width + 2, '0', -exponent);
			memcpy(
				buf + sign_width + 2 - exponent,
				image + sign_width,
				length - sign_width);
			buf[length - exponent + 2] = '\0';
			result = caml_copy_string(buf);
		}
		mpfr_free_str(image);
	}
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_get_str(value mode, value base, value digits, value x)
{
	CAMLparam4(mode, base, digits, x);
	CAMLlocal1(result);
	mp_exp_t exponent;
	char *image = mpfr_get_str(
		NULL,
		&exponent,
		Int_val(base),
		Long_val(digits),
		FR_val(x),
		Rnd_val(mode));
	result = caml_alloc_tuple(2);
	Store_field(result, 0, caml_copy_string(image));
	Store_field(result, 1, Val_long(exponent));
	mpfr_free_str(image);
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_of_int(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_set_si(FR_val(result), Long_val(x), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_of_float(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_set_d(FR_val(result), Double_val(x), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_float_of_fr(value mode, value x)
{
	CAMLparam2(mode, x);
	CAMLlocal1(result);
	result = caml_copy_double(mpfr_get_d(FR_val(x), Rnd_val(mode)));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_of_z(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_set_z(FR_val(result), Z_val(x), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_z_of_fr(value mode, value x)
{
	CAMLparam2(mode, x);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpfr_get_z(Z_val(result), FR_val(x), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_of_fr(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpfr_set(FR_val(result), FR_val(x), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_default_prec(value unit)
{
	CAMLparam1(unit);
	long result = mpfr_get_default_prec();
	CAMLreturn(Val_long(result));
}

CAMLprim value mlmpfr_fr_default_rounding_mode(value unit)
{
	CAMLparam1(unit);
	mpfr_rnd_t result = mpfr_get_default_rounding_mode();
	CAMLreturn(Val_rnd(result));
}

CAMLprim value mlmpfr_fr_bits_of_single(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	uint32_t i32;
#if __FLT_MANT_DIG__ == 24
	union {
		uint32_t i32;
		float s;
	} conv;
	conv.s = mpfr_get_flt(FR_val(x), MPFR_RNDN);
	i32 = conv.i32;
#else
	mpfr_ptr x_value = FR_val(x);
	if(mpfr_nan_p(x_value)){
		i32 = 0x7fc00000UL;
	}else{
		uint32_t sgn = mpfr_signbit(x_value);
		if(mpfr_inf_p(x_value)){
			i32 = (sgn << 31) | 0x7f800000UL;
		}else if(mpfr_zero_p(x_value)){
			i32 = (sgn << 31);
		}else{
			mpfr_exp_t exponent = mpfr_get_exp(x_value);
			mpfr_t a;
			mpfr_init2(a, 24);
			mpfr_abs(a, x_value, MPFR_RNDN);
			mpfr_mul_2exp(a, a, 24 - exponent, MPFR_RNDN);
			i32 = (sgn << 31)
				| ((uint32_t)(exponent + 0x7eU) << 23)
				| (mpfr_get_uj(a, MPFR_RNDN) & 0x007fffffUL);
			mpfr_clear(a);
		}
	}
#endif
	result = caml_copy_int32(i32);
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_bits_of_double(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	uint64_t i64;
#if __DBL_MANT_DIG__ == 53
	union {
		uint64_t i64;
		double d;
	} conv;
	conv.d = mpfr_get_d(FR_val(x), MPFR_RNDN);
	i64 = conv.i64;
#else
	mpfr_ptr x_value = FR_val(x);
	if(mpfr_nan_p(x_value)){
		i64 = 0x7ff8000000000000ULL;
	}else{
		uint64_t sgn = mpfr_signbit(x_value);
		if(mpfr_inf_p(x_value)){
			i64 = (sgn << 63) | 0x7ff0000000000000ULL;
		}else if(mpfr_zero_p(x_value)){
			i64 = (sgn << 63);
		}else{
			mpfr_exp_t exponent = mpfr_get_exp(x_value);
			mpfr_t a;
			mpfr_init2(a, 53);
			mpfr_abs(a, x_value, MPFR_RNDN);
			mpfr_mul_2exp(a, a, 53 - exponent, MPFR_RNDN);
			i64 = (sgn << 63)
				| ((uint64_t)(exponent + 0x3feU) << 52)
				| (mpfr_get_uj(a, MPFR_RNDN) & 0x000fffffffffffffULL);
			mpfr_clear(a);
		}
	}
#endif
	result = caml_copy_int64(i64);
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_bits_of_extended(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	uint64_t i64;
	uint16_t i16;
#if __LDBL_MANT_DIG__ == 64 && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	union {
		struct {
			uint64_t i64;
			uint16_t i16;
		} s;
		long double ld;
	} conv;
	conv.ld = mpfr_get_ld(FR_val(x), MPFR_RNDN);
	i64 = conv.s.i64;
	i16 = conv.s.i16;
#else
	mpfr_ptr x_value = FR_val(x);
	if(mpfr_nan_p(x_value)){
		i64 = 0xc000000000000000ULL;
		i16 = 0x7fff;
	}else{
		uint16_t sgn = mpfr_signbit(x_value);
		if(mpfr_inf_p(x_value)){
			i64 = 0x8000000000000000ULL;
			i16 = (sgn << 15) | 0x7fffU;
		}else if(mpfr_zero_p(x_value)){
			i64 = 0;
			i16 = (sgn << 15);
		}else{
			mpfr_exp_t exponent = mpfr_get_exp(x_value);
			mpfr_t a;
			mpfr_init2(a, 64);
			mpfr_abs(a, x_value, MPFR_RNDN);
			mpfr_mul_2exp(a, a, 64 - exponent, MPFR_RNDN);
			i64 = mpfr_get_uj(a, MPFR_RNDN);
			i16 = (sgn << 15) | (exponent + 0x3ffeU);
			mpfr_clear(a);
		}
	}
#endif
	result = caml_alloc_tuple(2);
	Store_field(result, 0, caml_copy_int64(i64));
	Store_field(result, 1, Val_int(i16));
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_single_of_bits(value i32)
{
	CAMLparam1(i32);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(24);
#if __FLT_MANT_DIG__ == 24
	union {
		uint32_t i32;
		float s;
	} conv;
	conv.i32 = Int32_val(i32);
	mpfr_set_flt(FR_val(result), conv.s, MPFR_RNDN);
#else
	mpfr_ptr result_value = FR_val(result);
	uint32_t i32_value = Int32_val(i32);
	if(i32_value == 0x7fc00000UL || i32_value == 0xffc00000UL){
		mpfr_set_nan(result_value);
	}else{
		uint32_t sgn = i32_value >> 31;
		if((i32_value & 0x7fffffffUL) == 0x7f800000UL){
			mpfr_set_inf(result_value, sgn ? -1 : +1);
		}else if((i32_value & 0x7fffffffUL) == 0x00000000L){
			mpfr_set_zero(result_value, sgn ? -1 : +1);
		}else{
			mpfr_exp_t exponent = ((i32_value >> 23) & 0xffU) - 0x7eU;
			mpfr_t a;
			mpfr_init2(a, 24);
			mpfr_set_uj(a, ((i32_value & 0x007fffffUL) | 0x00800000UL), MPFR_RNDN);
			mpfr_div_2exp(a, a, 24 - exponent, MPFR_RNDN);
			if(sgn){
				mpfr_neg(result_value, a, MPFR_RNDN);
			}else{
				mpfr_set(result_value, a, MPFR_RNDN);
			}
			mpfr_clear(a);
		}
	}
#endif
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_double_of_bits(value i64)
{
	CAMLparam1(i64);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(53);
#if __DBL_MANT_DIG__ == 53
	union {
		uint64_t i64;
		double d;
	} conv;
	conv.i64 = Int64_val(i64);
	mpfr_set_d(FR_val(result), conv.d, MPFR_RNDN);
#else
	mpfr_ptr result_value = FR_val(result);
	uint64_t i64_value = Int64_val(i64);
	if(i64_value == 0x7ff8000000000000ULL || i64_value == 0xfff8000000000000ULL){
		mpfr_set_nan(result_value);
	}else{
		uint64_t sgn = i64_value >> 63;
		if((i64_value & 0x7fffffffffffffffULL) == 0x7ff0000000000000ULL){
			mpfr_set_inf(result_value, sgn ? -1 : +1);
		}else if((i64_value & 0x7fffffffffffffffULL) == 0x0000000000000000ULL){
			mpfr_set_zero(result_value, sgn ? -1 : +1);
		}else{
			mpfr_exp_t exponent = ((i64_value >> 52) & 0x7ffU) - 0x3feU;
			mpfr_t a;
			mpfr_init2(a, 53);
			mpfr_set_uj(
				a,
				((i64_value & 0x000fffffffffffffULL) | 0x0010000000000000ULL),
				MPFR_RNDN);
			mpfr_div_2exp(a, a, 53 - exponent, MPFR_RNDN);
			if(sgn){
				mpfr_neg(result_value, a, MPFR_RNDN);
			}else{
				mpfr_set(result_value, a, MPFR_RNDN);
			}
			mpfr_clear(a);
		}
	}
#endif
	CAMLreturn(result);
}

CAMLprim value mlmpfr_fr_extended_of_bits(value i80)
{
	CAMLparam1(i80);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(64);
#if __LDBL_MANT_DIG__ == 64 && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	union {
		struct {
			uint64_t i64;
			uint16_t i16;
		} s;
		long double ld;
	} conv;
	conv.s.i64 = Int64_val(Field(i80, 0));
	conv.s.i16 = Int_val(Field(i80, 1));
	mpfr_set_ld(FR_val(result), conv.ld, MPFR_RNDN);
#else
	mpfr_ptr result_value = FR_val(result);
	uint64_t i64 = Int64_val(Field(i80, 0));
	uint16_t i16 = Int_val(Field(i80, 1));
	if(i64 == 0xc000000000000000ULL && (i16 == 0x7fffU || i16 == 0xffffU)){
		mpfr_set_nan(result_value);
	}else{
		uint64_t sgn = ((i16 >> 15) & 1U);
		if(i64 == 0x8000000000000000ULL && (i16 & 0x7fffU) == 0x7fffU){
			mpfr_set_inf(result_value, sgn ? -1 : +1);
		}else if(i64 == 0x0000000000000000ULL && (i16 & 0x7fffU) == 0x0000U){
			mpfr_set_zero(result_value, sgn ? -1 : +1);
		}else{
			mpfr_exp_t exponent = (i16 & 0x7fffU) - 0x3ffeU;
			mpfr_t a;
			mpfr_init2(a, 64);
			mpfr_set_uj(a, i64, MPFR_RNDN);
			mpfr_div_2exp(a, a, 64 - exponent, MPFR_RNDN);
			if(sgn){
				mpfr_neg(result_value, a, MPFR_RNDN);
			}else{
				mpfr_set(result_value, a, MPFR_RNDN);
			}
			mpfr_clear(a);
		}
	}
#endif
	CAMLreturn(result);
}

/* setup */

CAMLprim value mlmpfr_setup(value unit)
{
	CAMLparam1(unit);
	caml_register_custom_operations(&mlmpfr_fr_ops);
	CAMLreturn(Val_unit);
}
