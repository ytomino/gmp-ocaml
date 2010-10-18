#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/fail.h>
#include <caml/intext.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>
#include <sys/types.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <gmp.h>
#include "gmp_stub.h"

#ifndef LONG_BIT
#define LONG_BIT (__SIZEOF_LONG__ * 8)
#endif

/**** Z ****/

/* custom data */

static void mlgmp_z_finalize(value x)
{
	mpz_clear(Z_val(x));
}

static int mlgmp_z_custom_compare(value left, value right)
{
	CAMLparam2(left, right);
	int result = mpz_cmp(Z_val(left), Z_val(right));
	CAMLreturnT(int, result);
}

static long mlgmp_z_hash(value x)
{
	CAMLparam1(x);
	long result = z_hash(Z_val(x));
	CAMLreturnT(long, result);
}

static void mlgmp_z_serialize(value x,
	unsigned long *wsize_32, unsigned long *wsize_64)
{
	CAMLparam1(x);
	*wsize_32 = WSIZE_32_Z;
	*wsize_64 = WSIZE_64_Z;
	z_serialize(Z_val(x));
	CAMLreturn0;
}

static unsigned long mlgmp_z_deserialize(void *dst)
{
	CAMLparam0();
	z_deserialize((mpz_ptr)dst);
	CAMLreturnT(unsigned long, sizeof(mpz_t));
}

struct custom_operations mlgmp_z_ops = {
	.identifier = "jp.halfmoon.panathenaia.gmp.z",
	.finalize = mlgmp_z_finalize,
	.compare = mlgmp_z_custom_compare,
	.hash = mlgmp_z_hash,
	.serialize = mlgmp_z_serialize,
	.deserialize = mlgmp_z_deserialize};

/* functions */

CAMLprim value mlgmp_z_compare(value left, value right)
{
	CAMLparam2(left, right);
	int result = mpz_cmp(Z_val(left), Z_val(right));
	CAMLreturn(Val_int(result));
}

CAMLprim value mlgmp_z_neg(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_neg(result_value, Z_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_add(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_add(result_value, Z_val(left), Z_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_add_int(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_ptr l = Z_val(left);
	int r = Int_val(right);
	if(r >= 0){
		mpz_add_ui(result_value, l, r);
	}else{
		mpz_sub_ui(result_value, l, -r);
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_sub(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_sub(result_value, Z_val(left), Z_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_mul(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_mul(result_value, Z_val(left), Z_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_div(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_tdiv_q(result_value, Z_val(left), Z_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_rem(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_tdiv_r(result_value, Z_val(left), Z_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_int_pow_int(value base, value exponent)
{
	CAMLparam2(base, exponent);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	int e = Int_val(exponent);
	if(e >= 0){
		mpz_ui_pow_ui(result_value, Int_val(base), e);
	}else{
		mpz_set_si(result_value, 0);
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_scale(value fraction, value base, value exponent)
{
	CAMLparam3(fraction, base, exponent);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_ptr f = Z_val(fraction);
	int b = Int_val(base);
	int e = Int_val(exponent);
	if(b == 2){
		if(e >= 0){
			mpz_mul_2exp(result_value, f, e);
		}else{
			mpz_fdiv_q_2exp(result_value, f, -e); /* arithmetic right shift */
		}
	}else{
		mpz_t a;
		mpz_init(a);
		if(e >= 0){
			mpz_ui_pow_ui(a, b, e);
			mpz_mul(result_value, f, a);
		}else{
			mpz_ui_pow_ui(a, b, -e);
			mpz_fdiv_q(result_value, f, a);
		}
		mpz_clear(a);
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_logand(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_and(result_value, Z_val(left), Z_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_logor(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_ior(result_value, Z_val(left), Z_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_logxor(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_xor(result_value, Z_val(left), Z_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_lognot(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_com(result_value, Z_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_shift_left(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_mul_2exp(result_value, Z_val(left), Int_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_shift_right(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_fdiv_q_2exp(result_value, Z_val(left), Int_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_of_based_string(value base, value x)
{
	CAMLparam2(base, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	int err = mpz_init_set_str(Z_val(result), String_val(x), Int_val(base));
	if(err < 0) caml_failwith(__FUNCTION__);
	CAMLreturn(result);
}

CAMLprim value mlgmp_based_string_of_z(value base, value x)
{
	CAMLparam2(base, x);
	CAMLlocal1(result);
	char *image = mpz_get_str(NULL, Int_val(base), Z_val(x));
	result = caml_copy_string(image);
	free(image);
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_of_int(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_init_set_si(Z_val(result), Int_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_int_of_z(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = Val_int(mpz_get_si(Z_val(x)));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_of_int32(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_init_set_si(Z_val(result), Int32_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_int32_of_z(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = caml_copy_int32(mpz_get_si(Z_val(x)));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_of_nativeint(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_init_set_si(Z_val(result), Nativeint_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_nativeint_of_z(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = caml_copy_nativeint(mpz_get_si(Z_val(x)));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_of_int64(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
#if LONG_BIT >= 64
	mpz_init_set_si(Z_val(result), Int64_val(x));
#elif LONG_BIT >= 32
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	long long x_value = Int64_val(x);
	long hi = x_value >> 32; /* arithmetic right shift */
	unsigned long lo = x_value & 0xffffffffL;
	mpz_t hi1;
	mpz_init_set_si(hi1, hi);
	mpz_t hi2;
	mpz_init(hi2);
	mpz_mul_2exp(hi2, hi1, 32);
	mpz_add_ui(result_value, hi2, lo);
	mpz_clear(hi2);
	mpz_clear(hi1);
#else
#error "sizeof(long) < 4"
#endif
	CAMLreturn(result);
}

CAMLprim value mlgmp_int64_of_z(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
#if LONG_BIT >= 64
	result = caml_copy_int64(mpz_get_si(Z_val(x)));
#elif LONG_BIT >= 32
	mpz_ptr x_value = Z_val(x);
	mpz_t lo_mask;
	mpz_init_set_ui(lo_mask, 0xffffffff);
	mpz_t lo;
	mpz_init(lo);
	mpz_and(lo, x_value, lo_mask);
	mpz_t hi;
	mpz_init(hi);
	mpz_fdiv_q_2exp(hi, x_value, 32);
	result = caml_copy_int64(((long long)mpz_get_si(hi) << 32LL) | mpz_get_ui(lo));
	mpz_clear(hi);
	mpz_clear(lo);
	mpz_clear(lo_mask);
#else
#error "sizeof(long) < 4"
#endif
	CAMLreturn(result);
}

CAMLprim value mlgmp_float_of_z(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = caml_copy_double(mpz_get_d(Z_val(x)));
	CAMLreturn(result);
}

/**** Q ****/

/* custom data */

static void mlgmp_q_finalize(value x)
{
	mpq_clear(Q_val(x));
}

static int mlgmp_q_custom_compare(value left, value right)
{
	CAMLparam2(left, right);
	int result = mpq_cmp(Q_val(left), Q_val(right));
	CAMLreturnT(int, result);
}

static long mlgmp_q_hash(value x)
{
	CAMLparam1(x);
	long result = q_hash(Q_val(x));
	CAMLreturnT(long, result);
}

static void mlgmp_q_serialize(value x,
	unsigned long *wsize_32, unsigned long *wsize_64)
{
	CAMLparam1(x);
	*wsize_32 = WSIZE_32_Q;
	*wsize_64 = WSIZE_64_Q;
	q_serialize(Q_val(x));
	CAMLreturn0;
}

static unsigned long mlgmp_q_deserialize(void *dst)
{
	CAMLparam0();
	q_deserialize((mpq_ptr)dst);
	CAMLreturnT(unsigned long, sizeof(mpq_t));
}

struct custom_operations mlgmp_q_ops = {
	.identifier = "jp.halfmoon.panathenaia.gmp.q",
	.finalize = mlgmp_q_finalize,
	.compare = mlgmp_q_custom_compare,
	.hash = mlgmp_q_hash,
	.serialize = mlgmp_q_serialize,
	.deserialize = mlgmp_q_deserialize};

/* functions */

CAMLprim value mlgmp_q_compare(value left, value right)
{
	CAMLparam2(left, right);
	int result = mpq_cmp(Q_val(left), Q_val(right));
	CAMLreturn(Val_int(result));
}

CAMLprim value mlgmp_q_neg(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_q_ops, sizeof(mpq_t), 0, 1);
	mpq_ptr result_value = Q_val(result);
	mpq_init(result_value);
	mpq_neg(result_value, Q_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_add(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_q_ops, sizeof(mpq_t), 0, 1);
	mpq_ptr result_value = Q_val(result);
	mpq_init(result_value);
	mpq_add(result_value, Q_val(left), Q_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_add_int(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_q_ops, sizeof(mpq_t), 0, 1);
	mpq_ptr result_value = Q_val(result);
	mpq_init(result_value);
	mpq_t r;
	mpq_init(r);
	mpq_set_si(r, Int_val(right), 1);
	mpq_canonicalize(r);
	mpq_add(result_value, Q_val(left), r);
	mpq_clear(r);
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_sub(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_q_ops, sizeof(mpq_t), 0, 1);
	mpq_ptr result_value = Q_val(result);
	mpq_init(result_value);
	mpq_sub(result_value, Q_val(left), Q_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_mul(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_q_ops, sizeof(mpq_t), 0, 1);
	mpq_ptr result_value = Q_val(result);
	mpq_init(result_value);
	mpq_mul(result_value, Q_val(left), Q_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_div(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_q_ops, sizeof(mpq_t), 0, 1);
	mpq_ptr result_value = Q_val(result);
	mpq_init(result_value);
	mpq_div(result_value, Q_val(left), Q_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_int_pow_int(value base, value exponent)
{
	CAMLparam2(base, exponent);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_q_ops, sizeof(mpq_t), 0, 1);
	mpq_ptr result_value = Q_val(result);
	mpq_init(result_value);
	int b = Int_val(base);
	int e = Int_val(exponent);
	if(e >= 0){
		mpz_ui_pow_ui(mpq_numref(result_value), b, e);
		mpz_set_ui(mpq_denref(result_value), 1);
	}else{
		mpz_set_ui(mpq_numref(result_value), 1);
		mpz_ui_pow_ui(mpq_denref(result_value), b, -e);
	}
	mpq_canonicalize(result_value);
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_scale(value fraction, value base, value exponent)
{
	CAMLparam3(fraction, base, exponent);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_q_ops, sizeof(mpq_t), 0, 1);
	mpq_ptr result_value = Q_val(result);
	mpq_init(result_value);
	mpq_ptr f = Q_val(fraction);
	int b = Int_val(base);
	int e = Int_val(exponent);
	if(b == 2){
		if(e >= 0){
			mpq_mul_2exp(result_value, f, e);
		}else{
			mpq_div_2exp(result_value, f, -e);
		}
	}else{
		mpq_t a;
		mpq_init(a);
		if(e >= 0){
			mpz_ui_pow_ui(mpq_numref(a), b, e);
			mpz_set_ui(mpq_denref(a), 1);
		}else{
			mpz_set_ui(mpq_numref(a), 1);
			mpz_ui_pow_ui(mpq_denref(a), b, -e);
		}
		mpq_canonicalize(a);
		mpq_mul(result_value, f, a);
		mpq_clear(a);
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_num(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpq_get_num(result_value, Q_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_den(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpq_get_den(result_value, Q_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_of_based_string(value base, value x)
{
	CAMLparam2(base, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_q_ops, sizeof(mpq_t), 0, 1);
	mpq_ptr result_value = Q_val(result);
	mpq_init(result_value);
	int b = Int_val(base);
	char *x_value = String_val(x);
	char *period = strchr(x_value, '.');
	if(period == NULL){
		int err = mpq_set_str(result_value, x_value, b);
		if(err < 0) caml_failwith(__FUNCTION__);
		if(mpz_cmp_ui(mpq_denref(result_value), 0) == 0) caml_raise_zero_divide();
	}else{
		int length = strlen(x_value);
		char buf[length]; /* length + 1(NUL) - 1('.') */
		int period_index = period - x_value;
		int next_index = period_index + 1;
		int decimal_length = length - next_index;
		memcpy(buf, x_value, period_index);
		memcpy(buf + period_index, x_value + next_index, decimal_length);
		buf[length - 1] = '\0';
		int err = mpz_set_str(mpq_numref(result_value), buf, b);
		if(err < 0) caml_failwith(__FUNCTION__);
		mpz_ui_pow_ui(mpq_denref(result_value), b, decimal_length);
	}
	mpq_canonicalize(result_value);
	CAMLreturn(result);
}

CAMLprim value mlgmp_based_string_of_q(value base, value x)
{
	CAMLparam2(base, x);
	CAMLlocal1(result);
	char *image = mpq_get_str(NULL, Int_val(base), Q_val(x));
	result = caml_copy_string(image);
	free(image);
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_of_int(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_q_ops, sizeof(mpq_t), 0, 1);
	mpq_ptr result_value = Q_val(result);
	mpq_init(result_value);
	mpq_set_si(result_value, Int_val(x), 1);
	mpq_canonicalize(result_value);
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_of_float(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	double x_value = Double_val(x);
	if(! isfinite(x_value)){
		caml_failwith(__FUNCTION__);
	}
	result = alloc_custom(&mlgmp_q_ops, sizeof(mpq_t), 0, 1);
	mpq_ptr result_value = Q_val(result);
	mpq_init(result_value);
	mpq_set_d(result_value, x_value);
	mpq_canonicalize(result_value);
	CAMLreturn(result);
}

CAMLprim value mlgmp_float_of_q(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = caml_copy_double(mpq_get_d(Q_val(x)));
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_of_z(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_q_ops, sizeof(mpq_t), 0, 1);
	mpq_ptr result_value = Q_val(result);
	mpq_init(result_value);
	mpq_set_z(result_value, Z_val(x));
	mpq_canonicalize(result_value);
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_of_truncated_q(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_set_q(result_value, Q_val(x));
	CAMLreturn(result);
}

/**** F ****/

/* custom data */

static void mlgmp_f_finalize(value x)
{
	mpf_clear(F_val(x));
}

static int mlgmp_f_custom_compare(value left, value right)
{
	CAMLparam2(left, right);
	int result = mpf_cmp(F_val(left), F_val(right));
	CAMLreturnT(int, result);
}

static long mlgmp_f_hash(value x)
{
	CAMLparam1(x);
	long result = f_hash(F_val(x));
	CAMLreturnT(long, result);
}

static void mlgmp_f_serialize(value x,
	unsigned long *wsize_32, unsigned long *wsize_64)
{
	CAMLparam1(x);
	*wsize_32 = WSIZE_32_F;
	*wsize_64 = WSIZE_64_F;
	f_serialize(F_val(x));
	CAMLreturn0;
}

static unsigned long mlgmp_f_deserialize(void *dst)
{
	CAMLparam0();
	f_deserialize((mpf_ptr)dst);
	CAMLreturnT(unsigned long, sizeof(mpf_t));
}

struct custom_operations mlgmp_f_ops = {
	.identifier = "jp.halfmoon.panathenaia.gmp.f",
	.finalize = mlgmp_f_finalize,
	.compare = mlgmp_f_custom_compare,
	.hash = mlgmp_f_hash,
	.serialize = mlgmp_f_serialize,
	.deserialize = mlgmp_f_deserialize};

/* functions */

CAMLprim value mlgmp_f_compare(value left, value right)
{
	CAMLparam2(left, right);
	int result = mpf_cmp(F_val(left), F_val(right));
	CAMLreturn(Val_int(result));
}

CAMLprim value mlgmp_f_neg(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Int_val(prec));
	mpf_neg(result_value, F_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_add(value prec, value left, value right)
{
	CAMLparam3(prec, left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Int_val(prec));
	mpf_add(result_value, F_val(left), F_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_add_int(value prec, value left, value right)
{
	CAMLparam3(prec, left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Int_val(prec));
	mpf_ptr l = F_val(left);
	int r = Int_val(right);
	if(r >= 0){
		mpf_add_ui(result_value, l, r);
	}else{
		mpf_sub_ui(result_value, l, -r);
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_mul(value prec, value left, value right)
{
	CAMLparam3(prec, left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Int_val(prec));
	mpf_mul(result_value, F_val(left), F_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_div(value prec, value left, value right)
{
	CAMLparam3(prec, left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Int_val(prec));
	mpf_div(result_value, F_val(left), F_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_sub(value prec, value left, value right)
{
	CAMLparam3(prec, left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Int_val(prec));
	mpf_sub(result_value, F_val(left), F_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_int_pow_int(value prec, value base, value exponent)
{
	CAMLparam3(prec, base, exponent);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	int p = Int_val(prec);
	mpf_init2(result_value, p);
	int b = Int_val(base);
	int e = Int_val(exponent);
	mpz_t a;
	mpz_init(a);
	if(e >= 0){
		mpz_ui_pow_ui(a, b, e);
		mpf_set_z(result_value, a);
	}else{
		mpz_ui_pow_ui(a, b, -e);
		mpf_t af;
		mpf_init2(af, p);
		mpf_set_z(af, a);
		mpf_ui_div(result_value, 1, af);
		mpf_clear(af);
	}
	mpz_clear(a);
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_scale(value prec, value fraction, value base, value exponent)
{
	CAMLparam4(prec, fraction, base, exponent);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	int p = Int_val(prec);
	mpf_init2(result_value, p);
	int b = Int_val(base);
	int e = Int_val(exponent);
	mpf_ptr f = F_val(fraction);
	if(b == 2){
		if(e >= 0){
			mpf_mul_2exp(result_value, f, e);
		}else{
			mpf_div_2exp(result_value, f, -e);
		}
	}else{
		mpz_t a;
		mpz_init(a);
		mpf_t af;
		mpf_init2(af, p);
		if(e >= 0){
			mpz_ui_pow_ui(a, b, e);
			mpf_set_z(af, a);
			mpf_mul(result_value, f, af);
		}else{
			mpz_ui_pow_ui(a, b, -e);
			mpf_set_z(af, a);
			mpf_div(result_value, f, af);
		}
		mpf_clear(af);
		mpz_clear(a);
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_log(value prec, value x)
{
	/* log x = log (m * 2^e)
	 *       = log m + log (2^e)
	 *       = log m + e * log 2 */
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Int_val(prec));
	long exponent;
	double mantissa = mpf_get_d_2exp(&exponent, F_val(x));
	mpf_set_d(result_value, log(mantissa) + (double)exponent * M_LN2);
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_based_log(value prec, value base, value x)
{
	CAMLparam3(prec, base, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	int p = Int_val(prec);
	mpf_init2(result_value, p);
	int b = Int_val(base);
	long exponent;
	double mantissa = mpf_get_d_2exp(&exponent, F_val(x));
	if(b == 2){
		mpf_set_d(result_value, log(mantissa) / M_LN2 + (double)exponent);
	}else if(b == 16){
		mpf_set_d(result_value, (log(mantissa) / M_LN2 + (double)exponent) / 4.0);
	}else{
		mpf_t logex;
		mpf_init2(logex, p);
		mpf_set_d(logex, log(mantissa) + (double)exponent * M_LN2);
		mpf_t base_value;
		mpf_init2(base_value, p);
		mpf_set_ui(base_value, b);
		long base_exponent;
		double base_mantissa = mpf_get_d_2exp(&base_exponent, base_value);
		mpf_t logeb;
		mpf_init2(logeb, p);
		mpf_set_d(logeb, log(base_mantissa) + (double)base_exponent * M_LN2);
		mpf_div(result_value, logex, logeb);
		mpf_clear(logeb);
		mpf_clear(base_value);
		mpf_clear(logex);
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_frexp(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal3(result, result_fraction, result_exponent);
	int p = Int_val(prec);
	mpf_ptr x_value = F_val(x);
	long exponent;
	mpf_get_d_2exp(&exponent, x_value);
	result_exponent = Val_int(exponent);
	if(exponent == 0){
		result_fraction = x;
	}else{
		result_fraction = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
		mpf_ptr rf_value = F_val(result_fraction);
		mpf_init2(rf_value, p);
		if(exponent > 0){
			mpf_div_2exp(rf_value, x_value, exponent);
		}else{
			mpf_mul_2exp(rf_value, x_value, - exponent);
		}
	}
	result = caml_alloc_tuple(2);
	Field(result, 0) = result_fraction;
	Field(result, 1) = result_exponent;
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_of_based_string(value prec, value base, value x)
{
	CAMLparam3(prec, base, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Int_val(prec));
	int err = mpf_set_str(result_value, String_val(x), Int_val(base));
	if(err < 0) caml_failwith(__FUNCTION__);
	CAMLreturn(result);
}

CAMLprim value mlgmp_based_string_of_f(value base, value x)
{
	CAMLparam2(base, x);
	CAMLlocal1(result);
	mp_exp_t exponent;
	char *image = mpf_get_str(NULL, &exponent, Int_val(base), 0, F_val(x));
	ssize_t length = strlen(image);
	int sign_width = image[0] == '-'; /* 0 or 1 */
	mp_exp_t exponent_p = exponent + sign_width;
	if(length == 0){
		result = caml_copy_string("0");
	}else if(exponent_p > length){
		char buf[exponent_p + 1];
		memcpy(buf, image, length);
		memset(buf + length, '0', exponent_p - length);
		buf[exponent_p] = '\0';
		result = caml_copy_string(buf);
	}else if(exponent_p == length){
		result = caml_copy_string(image);
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
		memcpy(buf + sign_width + 2 - exponent, image + sign_width, length - sign_width);
		buf[length - exponent + 2] = '\0';
		result = caml_copy_string(buf);
	}
	free(image);
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_of_int(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Int_val(prec));
	mpf_set_si(result_value, Int_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_of_float(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	double x_value = Double_val(x);
	if(! isfinite(x_value)){
		caml_failwith(__FUNCTION__);
	}
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Int_val(prec));
	mpf_set_d(result_value, x_value);
	CAMLreturn(result);
}

CAMLprim value mlgmp_float_of_f(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = caml_copy_double(mpf_get_d(F_val(x)));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_of_z(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Int_val(prec));
	mpf_set_z(result_value, Z_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_of_truncated_f(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_set_f(result_value, F_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_of_f(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Int_val(prec));
	mpf_set(result_value, F_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_get_default_prec(value unit)
{
	CAMLparam1(unit);
	CAMLlocal1(result);
	result = Val_int(mpf_get_default_prec());
	CAMLreturn(result);
}

/**** Random ****/

/* custom data */

static void mlgmp_random_finalize(value x)
{
	gmp_randclear(Random_val(x));
}

static struct custom_operations random_ops = {
	.identifier = "jp.halfmoon.panathenaia.gmp.random",
	.finalize = mlgmp_random_finalize,
	.compare = custom_compare_default,
	.hash = custom_hash_default,
	.serialize = custom_serialize_default,
	.deserialize = custom_deserialize_default};

/* functions */

CAMLprim value mlgmp_random_make_z(value seed)
{
	CAMLparam1(seed);
	CAMLlocal1(result);
	result = alloc_custom(&random_ops, sizeof(gmp_randstate_t), 0, 1);
	__gmp_randstate_struct *result_value = Random_val(result);
	gmp_randinit_default(result_value);
	gmp_randseed(result_value, Z_val(seed));
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_make_int(value seed)
{
	CAMLparam1(seed);
	CAMLlocal1(result);
	result = alloc_custom(&random_ops, sizeof(gmp_randstate_t), 0, 1);
	__gmp_randstate_struct *result_value = Random_val(result);
	gmp_randinit_default(result_value);
	gmp_randseed_ui(result_value, Int_val(seed));
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_copy(value source)
{
	CAMLparam1(source);
	CAMLlocal1(result);
	result = alloc_custom(&random_ops, sizeof(gmp_randstate_t), 0, 1);
	__gmp_randstate_struct *result_value = Random_val(result);
	gmp_randinit_set(result_value, Random_val(source));
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_bits(value state)
{
	CAMLparam1(state);
	CAMLlocal1(result);
	result = Val_int(gmp_urandomb_ui(Random_val(state), sizeof(value) * 8 - 2));
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_int(value state, value n)
{
	CAMLparam2(state, n);
	CAMLlocal1(result);
	result = Val_int(gmp_urandomm_ui(Random_val(state), Int_val(n)));
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_int32(value state, value n)
{
	CAMLparam2(state, n);
	CAMLlocal1(result);
	result = caml_copy_int32(gmp_urandomm_ui(Random_val(state), Int32_val(n)));
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_nativeint(value state, value n)
{
	CAMLparam2(state, n);
	CAMLlocal1(result);
	result = caml_copy_nativeint(gmp_urandomm_ui(Random_val(state), Nativeint_val(n)));
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_bool(value state)
{
	CAMLparam1(state);
	CAMLlocal1(result);
	result = Val_bool(gmp_urandomb_ui(Random_val(state), 1));
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_z(value state, value n)
{
	CAMLparam2(state, n);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_urandomm(result_value, Random_val(state), Z_val(n));
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_int64(value state, value n)
{
	CAMLparam2(state, n);
#if LONG_BIT >= 64
	CAMLlocal1(result);
	result = caml_copy_int64(gmp_urandomm_ui(Random_val(state), Int64_val(n)));
#elif LONG_BIT >= 32
	CAMLlocal3(result, nz, rz);
	nz = mlgmp_z_of_int64(n);
	rz = mlgmp_random_z(state, nz);
	result = mlgmp_int64_of_z(rz);
#else
#error "sizeof(long) < 4"
#endif
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_f_bits(value state, value bits)
{
	CAMLparam2(state, bits);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	int b = Int_val(bits);
	mpf_init2(result_value, b);
	mpf_urandomb(result_value, Random_val(state), b);
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_f(value state, value prec, value n)
{
	CAMLparam3(state, prec, n);
	CAMLlocal1(result);
	int b = Int_val(prec);
	mpf_t u;
	mpf_init2(u, b);
	mpf_urandomb(u, Random_val(state), b);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, b);
	mpf_mul(result_value, u, F_val(n));
	mpf_clear(u);
	CAMLreturn(result);
}

/* setup */

CAMLprim value mlgmp_setup(value unit)
{
  CAMLparam1(unit);
  register_custom_operations(&mlgmp_z_ops);
  register_custom_operations(&mlgmp_q_ops);
  register_custom_operations(&mlgmp_f_ops);
  CAMLreturn(Val_unit);
}
