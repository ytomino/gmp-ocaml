#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/fail.h>
#include <caml/intext.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>
#include <sys/types.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
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

CAMLprim value mlgmp_z_compare_int(value left, value right)
{
	CAMLparam2(left, right);
	int result = mpz_cmp_si(Z_val(left), Long_val(right));
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

CAMLprim value mlgmp_z_abs(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_abs(result_value, Z_val(x));
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
	long r = Long_val(right);
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

CAMLprim value mlgmp_z_pow_int(value base, value exponent)
{
	CAMLparam2(base, exponent);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	long e = Long_val(exponent);
	if(e >= 0){
		mpz_pow_ui(result_value, Z_val(base), e);
	}else{
		mpz_set_si(result_value, 0);
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_pow_q(value base, value exponent)
{
	CAMLparam2(base, exponent);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_ptr b = Z_val(base);
	mpq_ptr e = Q_val(exponent);
	mpz_ptr e_num = mpq_numref(e);
	mpz_ptr e_den = mpq_denref(e);
	if(mpq_cmp_ui(e, 0, 0) >= 0){
		mpz_t a;
		mpz_init(a);
		mpz_pow_ui(a, b, mpz_get_ui(e_num));
		mpz_root(result_value, a, mpz_get_ui(e_den));
		mpz_clear(a);
	}else{
		/* b^-e = 1/b^e */
		int c = mpz_cmp_ui(b, 1);
		if(c > 0){
			/* if b > 1 then b^e > 1 therefore 1/b^e < 1, truncate(1/b^e) = 0 */
			mpz_set_si(result_value, 0);
		}else if(c < 0){
			/* if b < 1 then b = 0 therefore b^e = 0 */
			caml_raise_zero_divide();
		}else{
			/* if b = 1 then b^e = 1 therefore 1/b^e = 1 */
			mpz_set_si(result_value, 1);
		}
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_int_pow_int(value base, value exponent)
{
	CAMLparam2(base, exponent);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	long e = Long_val(exponent);
	if(e >= 0){
		mpz_ui_pow_ui(result_value, Long_val(base), e);
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
	long b = Long_val(base);
	long e = Long_val(exponent);
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

CAMLprim value mlgmp_z_sqrt(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_sqrt(result_value, Z_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_tdiv(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal3(result, q, r);
	q = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	r = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr q_value = Z_val(q);
	mpz_init(q_value);
	mpz_ptr r_value = Z_val(r);
	mpz_init(r_value);
	mpz_tdiv_qr(q_value, r_value, Z_val(left), Z_val(right));
	result = caml_alloc_tuple(2);
	Field(result, 0) = q;
	Field(result, 1) = r;
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_cdiv(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal3(result, q, r);
	q = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	r = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr q_value = Z_val(q);
	mpz_init(q_value);
	mpz_ptr r_value = Z_val(r);
	mpz_init(r_value);
	mpz_cdiv_qr(q_value, r_value, Z_val(left), Z_val(right));
	result = caml_alloc_tuple(2);
	Field(result, 0) = q;
	Field(result, 1) = r;
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_fdiv(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal3(result, q, r);
	q = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	r = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr q_value = Z_val(q);
	mpz_init(q_value);
	mpz_ptr r_value = Z_val(r);
	mpz_init(r_value);
	mpz_fdiv_qr(q_value, r_value, Z_val(left), Z_val(right));
	result = caml_alloc_tuple(2);
	Field(result, 0) = q;
	Field(result, 1) = r;
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_modulo(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_mod(result_value, Z_val(left), Z_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_pow_mod(value base, value exponent, value mod)
{
	CAMLparam3(base, exponent, mod);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_powm(result_value, Z_val(base), Z_val(exponent), Z_val(mod));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_tsqrt(value x)
{
	CAMLparam1(x);
	CAMLlocal3(result, s, r);
	s = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	r = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr s_value = Z_val(s);
	mpz_init(s_value);
	mpz_ptr r_value = Z_val(r);
	mpz_init(r_value);
	mpz_sqrtrem(s_value, r_value, Z_val(x));
	result = caml_alloc_tuple(2);
	Field(result, 0) = s;
	Field(result, 1) = r;
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_is_perfect_power(value x)
{
	CAMLparam1(x);
	bool result = mpz_perfect_power_p(Z_val(x));
	CAMLreturn(Val_bool(result));
}

CAMLprim value mlgmp_z_is_perfect_square(value x)
{
	CAMLparam1(x);
	bool result = mpz_perfect_square_p(Z_val(x));
	CAMLreturn(Val_bool(result));
}

CAMLprim value mlgmp_z_is_probably_prime(value n, value reps)
{
	CAMLparam2(n, reps);
	int result = mpz_probab_prime_p(Z_val(n), Int_val(reps));
	CAMLreturn(Val_int(result));
}

CAMLprim value mlgmp_z_next_prime(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_nextprime(result_value, Z_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_gcdext(value a, value b)
{
	CAMLparam2(a, b);
	CAMLlocal4(result, g, s, t);
	g = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	s = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	t = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr g_value = Z_val(g);
	mpz_init(g_value);
	mpz_ptr s_value = Z_val(s);
	mpz_init(s_value);
	mpz_ptr t_value = Z_val(t);
	mpz_init(t_value);
	mpz_gcdext(g_value, s_value, t_value, Z_val(a), Z_val(b));
	result = caml_alloc_tuple(3);
	Field(result, 0) = g;
	Field(result, 1) = s;
	Field(result, 2) = t;
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_invert(value x, value y)
{
	CAMLparam2(x, y);
	CAMLlocal2(result, i);
	i = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr i_value = Z_val(i);
	mpz_init(i_value);
	if(mpz_invert(i_value, Z_val(x), Z_val(y))){
		result = caml_alloc(1, Int_val(Val_true)); /* Some i */
		Field(result, 0) = i;
	}else{
		result = Val_false; /* None */
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_legendre(value a, value p)
{
	CAMLparam2(a, p);
	int result = mpz_legendre(Z_val(a), Z_val(p));
	CAMLreturn(Val_int(result));
}

CAMLprim value mlgmp_z_remove(value x, value f)
{
	CAMLparam2(x, f);
	CAMLlocal2(result, rop);
	rop = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr rop_value = Z_val(rop);
	mpz_init(rop_value);
	mp_bitcnt_t removed = mpz_remove(rop_value, Z_val(x), Z_val(f));
	result = alloc_tuple(2);
	Field(result, 0) = rop;
	Field(result, 1) = Val_long(removed);
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_fac_int(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_fac_ui(result_value, Long_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_bin_int(value n, value k)
{
	CAMLparam2(n, k);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_bin_ui(result_value, Z_val(n), Long_val(k));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_fib_int(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_fib_ui(result_value, Long_val(x));
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
	mpz_mul_2exp(result_value, Z_val(left), Long_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_shift_right(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_ptr result_value = Z_val(result);
	mpz_init(result_value);
	mpz_fdiv_q_2exp(result_value, Z_val(left), Long_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_scan0(value x, value starting_bit)
{
	CAMLparam2(x, starting_bit);
	mp_bitcnt_t result = mpz_scan0(Z_val(x), Long_val(starting_bit));
	CAMLreturn(Val_long(result));
}

CAMLprim value mlgmp_z_scan1(value x, value starting_bit)
{
	CAMLparam2(x, starting_bit);
	mp_bitcnt_t result = mpz_scan1(Z_val(x), Long_val(starting_bit));
	CAMLreturn(Val_long(result));
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
	mpz_init_set_si(Z_val(result), Long_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_int_of_z(value x)
{
	CAMLparam1(x);
	long result = mpz_get_si(Z_val(x));
	CAMLreturn(Val_long(result));
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

CAMLprim value mlgmp_z_of_truncated_float(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_init_set_d(Z_val(result), Double_val(x));
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

CAMLprim value mlgmp_q_compare_int(value left, value right)
{
	CAMLparam2(left, right);
	int result = mpq_cmp_si(Q_val(left), Long_val(right), 1);
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

CAMLprim value mlgmp_q_abs(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_q_ops, sizeof(mpq_t), 0, 1);
	mpq_ptr result_value = Q_val(result);
	mpq_init(result_value);
	mpq_abs(result_value, Q_val(x));
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
	mpq_set_si(r, Long_val(right), 1);
	mpq_canonicalize(r); /* ? */
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

CAMLprim value mlgmp_q_pow_int(value base, value exponent)
{
	CAMLparam2(base, exponent);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_q_ops, sizeof(mpq_t), 0, 1);
	mpq_ptr result_value = Q_val(result);
	mpq_init(result_value);
	mpq_ptr b = Q_val(base);
	long e = Long_val(exponent);
	if(e >= 0){
		mpz_pow_ui(mpq_numref(result_value), mpq_numref(b), e);
		mpz_pow_ui(mpq_denref(result_value), mpq_denref(b), e);
	}else{
		mpz_pow_ui(mpq_numref(result_value), mpq_denref(b), -e);
		mpz_pow_ui(mpq_denref(result_value), mpq_numref(b), -e);
	}
	mpq_canonicalize(result_value);
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_int_pow_int(value base, value exponent)
{
	CAMLparam2(base, exponent);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_q_ops, sizeof(mpq_t), 0, 1);
	mpq_ptr result_value = Q_val(result);
	mpq_init(result_value);
	long b = Long_val(base);
	long e = Long_val(exponent);
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
	long b = Long_val(base);
	long e = Long_val(exponent);
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

CAMLprim value mlgmp_q_sqrt(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_q_ops, sizeof(mpq_t), 0, 1);
	mpq_ptr result_value = Q_val(result);
	mpq_init(result_value);
	mpq_ptr x_value = Q_val(x);
	mpz_t a;
	mpz_init(a);
	mpz_pow_ui(a, mpq_numref(x_value), 2);
	mpz_sqrt(mpq_numref(result_value), a);
	mpz_set(mpq_denref(result_value), mpq_denref(x_value));
	mpq_canonicalize(result_value);
	mpz_clear(a);
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
	mpq_set_si(result_value, Long_val(x), 1);
	mpq_canonicalize(result_value); /* ? */
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
	mpq_canonicalize(result_value); /* ? */
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
	mpq_canonicalize(result_value); /* ? */
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

CAMLprim value mlgmp_q_make_int(value x, value y)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_q_ops, sizeof(mpq_t), 0, 1);
	mpq_ptr result_value = Q_val(result);
	mpq_init(result_value);
	mpq_set_si(result_value, Long_val(x), Long_val(y));
	mpq_canonicalize(result_value);
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_make_z(value x, value y)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_q_ops, sizeof(mpq_t), 0, 1);
	mpq_ptr result_value = Q_val(result);
	mpq_init(result_value);
	mpz_set(mpq_numref(result_value), Z_val(x));
	mpz_set(mpq_denref(result_value), Z_val(y));
	mpq_canonicalize(result_value);
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

CAMLprim value mlgmp_f_compare_int(value left, value right)
{
	CAMLparam2(left, right);
	int result = mpf_cmp_si(F_val(left), Long_val(right));
	CAMLreturn(Val_int(result));
}

CAMLprim value mlgmp_f_nearly_equal(value bits, value left, value right)
{
	CAMLparam3(bits, left, right);
	bool result = mpf_eq(F_val(left), F_val(right), Long_val(bits));
	CAMLreturn(Val_bool(result));
}

CAMLprim value mlgmp_f_neg(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Long_val(prec));
	mpf_neg(result_value, F_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_abs(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Long_val(prec));
	mpf_abs(result_value, F_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_add(value prec, value left, value right)
{
	CAMLparam3(prec, left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Long_val(prec));
	mpf_add(result_value, F_val(left), F_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_add_int(value prec, value left, value right)
{
	CAMLparam3(prec, left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Long_val(prec));
	mpf_ptr l = F_val(left);
	long r = Long_val(right);
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
	mpf_init2(result_value, Long_val(prec));
	mpf_mul(result_value, F_val(left), F_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_div(value prec, value left, value right)
{
	CAMLparam3(prec, left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Long_val(prec));
	mpf_div(result_value, F_val(left), F_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_sub(value prec, value left, value right)
{
	CAMLparam3(prec, left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Long_val(prec));
	mpf_sub(result_value, F_val(left), F_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_pow_int(value prec, value base, value exponent)
{
	CAMLparam3(prec, base, exponent);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mp_bitcnt_t p = Long_val(prec);
	mpf_init2(result_value, p);
	mpf_ptr b = F_val(base);
	long e = Long_val(exponent);
	if(e >= 0){
		mpf_pow_ui(result_value, b, Long_val(exponent));
	}else{
		mpf_t a;
		mpf_init2(a, p);
		mpf_pow_ui(a, b, -e);
		mpf_ui_div(result_value, 1, a);
		mpf_clear(a);
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_int_pow_int(value prec, value base, value exponent)
{
	CAMLparam3(prec, base, exponent);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mp_bitcnt_t p = Long_val(prec);
	mpf_init2(result_value, p);
	long b = Long_val(base);
	long e = Long_val(exponent);
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
	mp_bitcnt_t p = Long_val(prec);
	mpf_init2(result_value, p);
	long b = Long_val(base);
	long e = Long_val(exponent);
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

CAMLprim value mlgmp_f_sqrt(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Long_val(prec));
	mpf_sqrt(result_value, F_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_frexp(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal3(result, result_fraction, result_exponent);
	mp_bitcnt_t p = Long_val(prec);
	mpf_ptr x_value = F_val(x);
	long exponent;
	mpf_get_d_2exp(&exponent, x_value);
	result_exponent = Val_long(exponent);
	if(exponent == 0){
		result_fraction = x;
	}else{
		result_fraction = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
		mpf_ptr rf_value = F_val(result_fraction);
		mpf_init2(rf_value, p);
		x_value = F_val(x); /* if gc was invoked by alloc_custom */
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

CAMLprim value mlgmp_f_ceil(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Long_val(prec));
	mpf_ceil(result_value, F_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_floor(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Long_val(prec));
	mpf_floor(result_value, F_val(x));
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
	mpf_init2(result_value, Long_val(prec));
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
	mp_bitcnt_t p = Long_val(prec);
	mpf_init2(result_value, p);
	long b = Long_val(base);
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

CAMLprim value mlgmp_f_of_based_string(value prec, value base, value x)
{
	CAMLparam3(prec, base, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mpf_init2(result_value, Long_val(prec));
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
	mpf_init2(result_value, Long_val(prec));
	mpf_set_si(result_value, Long_val(x));
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
	mpf_init2(result_value, Long_val(prec));
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
	mpf_init2(result_value, Long_val(prec));
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
	mpf_init2(result_value, Long_val(prec));
	mpf_set(result_value, F_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_get_default_prec(value unit)
{
	CAMLparam1(unit);
	long result = mpf_get_default_prec();
	CAMLreturn(Val_long(result));
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

CAMLprim value mlgmp_random_create(value unit)
{
	CAMLparam1(unit);
	CAMLlocal1(result);
	result = alloc_custom(&random_ops, sizeof(gmp_randstate_t), 0, 1);
	__gmp_randstate_struct *result_value = Random_val(result);
	gmp_randinit_default(result_value);
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_create_lc_2exp(value a, value c, value m2exp)
{
	CAMLparam3(a, c, m2exp);
	CAMLlocal1(result);
	result = alloc_custom(&random_ops, sizeof(gmp_randstate_t), 0, 1);
	__gmp_randstate_struct *result_value = Random_val(result);
	gmp_randinit_lc_2exp(result_value, Z_val(a), Long_val(c), Long_val(m2exp));
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_create_lc_2exp_size(value size)
{
	CAMLparam1(size);
	CAMLlocal1(result);
	result = alloc_custom(&random_ops, sizeof(gmp_randstate_t), 0, 1);
	__gmp_randstate_struct *result_value = Random_val(result);
	gmp_randinit_lc_2exp_size(result_value, Long_val(size));
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_create_mt(value unit)
{
	CAMLparam1(unit);
	CAMLlocal1(result);
	result = alloc_custom(&random_ops, sizeof(gmp_randstate_t), 0, 1);
	__gmp_randstate_struct *result_value = Random_val(result);
	gmp_randinit_mt(result_value);
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_seed_int(value state, value seed)
{
	CAMLparam2(state, seed);
	gmp_randseed_ui(Random_val(state), Long_val(seed));
	CAMLreturn(Val_unit);
}

CAMLprim value mlgmp_random_seed_z(value state, value seed)
{
	CAMLparam2(state, seed);
	gmp_randseed(Random_val(state), Z_val(seed));
	CAMLreturn(Val_unit);
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
	long result = gmp_urandomb_ui(Random_val(state), sizeof(value) * 8 - 2);
	CAMLreturn(Val_long(result));
}

CAMLprim value mlgmp_random_int(value state, value n)
{
	CAMLparam2(state, n);
	long result = gmp_urandomm_ui(Random_val(state), Long_val(n));
	CAMLreturn(Val_long(result));
}

CAMLprim value mlgmp_random_int32(value state, value n)
{
	CAMLparam2(state, n);
	CAMLlocal1(result);
	result = caml_copy_int32(gmp_urandomm_ui(Random_val(state), Int32_val(n)));
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
	bool result = gmp_urandomb_ui(Random_val(state), 1);
	CAMLreturn(Val_bool(result));
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

CAMLprim value mlgmp_random_f_bits(value state, value bits)
{
	CAMLparam2(state, bits);
	CAMLlocal1(result);
	result = alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_ptr result_value = F_val(result);
	mp_bitcnt_t b = Long_val(bits);
	mpf_init2(result_value, b);
	mpf_urandomb(result_value, Random_val(state), b);
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_f(value state, value prec, value n)
{
	CAMLparam3(state, prec, n);
	CAMLlocal1(result);
	mp_bitcnt_t b = Long_val(prec);
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
