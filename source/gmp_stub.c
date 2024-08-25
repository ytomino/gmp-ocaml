#include "gmp_stub.h"

#include <caml/alloc.h>
#include <caml/config.h>
#include <caml/custom.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>
#include <sys/types.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

/* Tag_some/Val_none are added since OCaml 4.12 */

#if !defined(Tag_some)
#define Tag_some 0
#endif
#if !defined(Val_none)
#define Val_none Val_int(0)
#endif

/* for version < 5.1.0 */

#if __GNU_MP_RELEASE < 50100
#include "gmp_050100.h"
#endif

/* version functions */

CAMLprim value mlgmp_compiled_version(value unit)
{
	CAMLparam1(unit);
	CAMLlocal1(result);
	result = caml_alloc_tuple(3);
	Store_field(result, 0, Val_int(__GNU_MP_VERSION));
	Store_field(result, 1, Val_int(__GNU_MP_VERSION_MINOR));
	Store_field(result, 2, Val_int(__GNU_MP_VERSION_PATCHLEVEL));
	CAMLreturn(result);
}

CAMLprim value mlgmp_compiled_version_string(value unit)
{
	CAMLparam1(unit);
	CAMLlocal1(result);
#define S_(s) #s
#define S(s) S_(s)
#define MP_VERSION_STRING \
	S(__GNU_MP_VERSION) "." S(__GNU_MP_VERSION_MINOR) "." \
	S(__GNU_MP_VERSION_PATCHLEVEL)
	result = caml_copy_string(MP_VERSION_STRING);
#undef MP_VERSION_STRING
#undef S
#undef S_
	CAMLreturn(result);
}

CAMLprim value mlgmp_get_version_string(value unit)
{
	CAMLparam1(unit);
	CAMLlocal1(result);
	result = caml_copy_string(gmp_version);
	CAMLreturn(result);
}

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

CAMLexport value mlgmp_alloc_z_init(void)
{
	CAMLparam0();
	CAMLlocal1(result);
	result = caml_alloc_custom(&mlgmp_z_ops, sizeof(mpz_t), 0, 1);
	mpz_init(Z_val(result));
	CAMLreturn(result);
}

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
	result = mlgmp_alloc_z_init();
	mpz_neg(Z_val(result), Z_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_abs(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_abs(Z_val(result), Z_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_add(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_add(Z_val(result), Z_val(left), Z_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_add_int(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_ptr result_value = Z_val(result);
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
	result = mlgmp_alloc_z_init();
	mpz_sub(Z_val(result), Z_val(left), Z_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_sub_int(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_ptr result_value = Z_val(result);
	mpz_ptr l = Z_val(left);
	long r = Long_val(right);
	if(r >= 0){
		mpz_sub_ui(result_value, l, r);
	}else{
		mpz_add_ui(result_value, l, -r);
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_mul(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_mul(Z_val(result), Z_val(left), Z_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_mul_int(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_mul_si(Z_val(result), Z_val(left), Long_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_div(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_tdiv_q(Z_val(result), Z_val(left), Z_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_fma(value val_x, value val_y, value val_z)
{
	CAMLparam3(val_x, val_y, val_z);
	CAMLlocal1(val_result);
	val_result = mlgmp_alloc_z_init();
	mpz_ptr result = Z_val(val_result);
	mpz_set(result, Z_val(val_z));
	mpz_addmul(result, Z_val(val_x), Z_val(val_y));
	CAMLreturn(val_result);
}

CAMLprim value mlgmp_z_pow_int(value base, value exponent)
{
	CAMLparam2(base, exponent);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_ptr result_value = Z_val(result);
	long e = Long_val(exponent);
	if(e >= 0){
		mpz_pow_ui(result_value, Z_val(base), e);
	}else{
		mpz_set_si(result_value, 0);
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_int_pow_int(value base, value exponent)
{
	CAMLparam2(base, exponent);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_ptr result_value = Z_val(result);
	long e = Long_val(exponent);
	if(e < 0){
		mpz_set_si(result_value, 0);
	}else{
		long b = Long_val(base);
		if(b < 0){
			mpz_ui_pow_ui(result_value, -b, e);
			if(e % 2 != 0){
				mpz_neg(result_value, result_value);
			}
		}else{
			mpz_ui_pow_ui(result_value, b, e);
		}
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_scale(value fraction, value base, value exponent)
{
	CAMLparam3(fraction, base, exponent);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_ptr result_value = Z_val(result);
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
		if(e >= 0){
			mpz_ui_pow_ui(result_value, b, e);
			mpz_mul(result_value, f, result_value);
		}else{
			mpz_ui_pow_ui(result_value, b, -e);
			mpz_fdiv_q(result_value, f, result_value);
		}
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_root(value nth, value x)
{
	CAMLparam2(nth, x);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_root(Z_val(result), Z_val(x), Long_val(nth));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_sqrt(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_sqrt(Z_val(result), Z_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_rem(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_tdiv_r(Z_val(result), Z_val(left), Z_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_modulo(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_mod(Z_val(result), Z_val(left), Z_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_pow_mod(value base, value exponent, value mod)
{
	CAMLparam3(base, exponent, mod);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_powm(Z_val(result), Z_val(base), Z_val(exponent), Z_val(mod));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_tdiv(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal3(result, q, r);
	q = mlgmp_alloc_z_init();
	r = mlgmp_alloc_z_init();
	mpz_tdiv_qr(Z_val(q), Z_val(r), Z_val(left), Z_val(right));
	result = caml_alloc_tuple(2);
	Store_field(result, 0, q);
	Store_field(result, 1, r);
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_tdiv_int(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal2(result, q);
	q = mlgmp_alloc_z_init();
	mpz_ptr q_value = Z_val(q);
	mpz_ptr l = Z_val(left);
	long d = Long_val(right);
	long r = mpz_tdiv_q_ui(q_value, l, labs(d));
	if(d < 0){
		mpz_neg(q_value, q_value);
	}
	if(mpz_sgn(l) < 0){
		r = -r;
	}
	result = caml_alloc_tuple(2);
	Store_field(result, 0, q);
	Store_field(result, 1, Val_long(r));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_cdiv(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal3(result, q, r);
	q = mlgmp_alloc_z_init();
	r = mlgmp_alloc_z_init();
	mpz_cdiv_qr(Z_val(q), Z_val(r), Z_val(left), Z_val(right));
	result = caml_alloc_tuple(2);
	Store_field(result, 0, q);
	Store_field(result, 1, r);
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_cdiv_int(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal2(result, q);
	q = mlgmp_alloc_z_init();
	mpz_ptr q_value = Z_val(q);
	long d = Long_val(right);
	long r = mpz_cdiv_q_ui(q_value, Z_val(left), labs(d));
	if(d < 0){
		mpz_neg(q_value, q_value);
		if(r != 0){
			mpz_add_ui(q_value, q_value, 1);
			r += d;
		}
	}
	r = -r;
	result = caml_alloc_tuple(2);
	Store_field(result, 0, q);
	Store_field(result, 1, Val_long(r));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_fdiv(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal3(result, q, r);
	q = mlgmp_alloc_z_init();
	r = mlgmp_alloc_z_init();
	mpz_fdiv_qr(Z_val(q), Z_val(r), Z_val(left), Z_val(right));
	result = caml_alloc_tuple(2);
	Store_field(result, 0, q);
	Store_field(result, 1, r);
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_fdiv_int(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal2(result, q);
	q = mlgmp_alloc_z_init();
	mpz_ptr q_value = Z_val(q);
	long d = Long_val(right);
	long r = mpz_fdiv_q_ui(q_value, Z_val(left), labs(d));
	if(d < 0){
		mpz_neg(q_value, q_value);
		if(r != 0){
			mpz_sub_ui(q_value, q_value, 1);
			r += d;
		}
	}
	result = caml_alloc_tuple(2);
	Store_field(result, 0, q);
	Store_field(result, 1, Val_long(r));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_tsqrt(value x)
{
	CAMLparam1(x);
	CAMLlocal3(result, s, r);
	s = mlgmp_alloc_z_init();
	r = mlgmp_alloc_z_init();
	mpz_sqrtrem(Z_val(s), Z_val(r), Z_val(x));
	result = caml_alloc_tuple(2);
	Store_field(result, 0, s);
	Store_field(result, 1, r);
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
	result = mlgmp_alloc_z_init();
	mpz_nextprime(Z_val(result), Z_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_gcd(value a, value b)
{
	CAMLparam2(a, b);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_gcd(Z_val(result), Z_val(a), Z_val(b));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_gcdext(value a, value b)
{
	CAMLparam2(a, b);
	CAMLlocal4(result, g, s, t);
	g = mlgmp_alloc_z_init();
	s = mlgmp_alloc_z_init();
	t = mlgmp_alloc_z_init();
	mpz_gcdext(Z_val(g), Z_val(s), Z_val(t), Z_val(a), Z_val(b));
	result = caml_alloc_tuple(3);
	Store_field(result, 0, g);
	Store_field(result, 1, s);
	Store_field(result, 2, t);
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_lcm(value a, value b)
{
	CAMLparam2(a, b);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_lcm(Z_val(result), Z_val(a), Z_val(b));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_invert(value x, value y)
{
	CAMLparam2(x, y);
	CAMLlocal2(result, i);
	i = mlgmp_alloc_z_init();
	mpz_ptr i_value = Z_val(i);
	if(mpz_invert(i_value, Z_val(x), Z_val(y))){
		result = caml_alloc_small(1, Tag_some);
		Store_field(result, 0, i);
	}else{
		result = Val_none;
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_jacobi(value a, value p)
{
	CAMLparam2(a, p);
	int result = mpz_jacobi(Z_val(a), Z_val(p));
	CAMLreturn(Val_int(result));
}

CAMLprim value mlgmp_z_remove(value x, value f)
{
	CAMLparam2(x, f);
	CAMLlocal2(result, rop);
	rop = mlgmp_alloc_z_init();
	mp_bitcnt_t removed = mpz_remove(Z_val(rop), Z_val(x), Z_val(f));
	result = caml_alloc_tuple(2);
	Store_field(result, 0, rop);
	Store_field(result, 1, Val_long(removed));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_fac_int(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_fac_ui(Z_val(result), Long_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_dfac_int(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_2fac_ui(Z_val(result), Long_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_int_mfac_int(value step, value x)
{
	CAMLparam2(step, x);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_mfac_uiui(Z_val(result), Long_val(x), Long_val(step));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_primorial_int(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_primorial_ui(Z_val(result), Long_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_bin_int(value n, value k)
{
	CAMLparam2(n, k);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_bin_ui(Z_val(result), Z_val(n), Long_val(k));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_fib_int(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_fib_ui(Z_val(result), Long_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_lucnum_int(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_lucnum_ui(Z_val(result), Long_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_logand(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_and(Z_val(result), Z_val(left), Z_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_logand_int(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_ptr result_value = Z_val(result);
	mpz_set_si(result_value, Long_val(right));
	mpz_and(result_value, Z_val(left), result_value);
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_logor(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_ior(Z_val(result), Z_val(left), Z_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_logor_int(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_ptr result_value = Z_val(result);
	mpz_set_si(result_value, Long_val(right));
	mpz_ior(result_value, Z_val(left), result_value);
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_logxor(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_xor(Z_val(result), Z_val(left), Z_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_logxor_int(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_ptr result_value = Z_val(result);
	mpz_set_si(result_value, Long_val(right));
	mpz_xor(result_value, Z_val(left), result_value);
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_lognot(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_com(Z_val(result), Z_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_shift_left(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_mul_2exp(Z_val(result), Z_val(left), Long_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_shift_right(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_fdiv_q_2exp(Z_val(result), Z_val(left), Long_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_population_count(value x)
{
	CAMLparam1(x);
	mp_bitcnt_t result = mpz_popcount(Z_val(x));
	if(result >= Max_long) result = Max_long;
	CAMLreturn(Val_long(result));
}

CAMLprim value mlgmp_z_hamming_distance(value x, value y)
{
	CAMLparam2(x, y);
	mp_bitcnt_t result = mpz_hamdist(Z_val(x), Z_val(y));
	if(result >= Max_long) result = Max_long;
	CAMLreturn(Val_long(result));
}

CAMLprim value mlgmp_z_scan0(value x, value starting_bit)
{
	CAMLparam2(x, starting_bit);
	mp_bitcnt_t result = mpz_scan0(Z_val(x), Long_val(starting_bit));
	if(result >= Max_long) result = Max_long;
	CAMLreturn(Val_long(result));
}

CAMLprim value mlgmp_z_scan1(value x, value starting_bit)
{
	CAMLparam2(x, starting_bit);
	mp_bitcnt_t result = mpz_scan1(Z_val(x), Long_val(starting_bit));
	if(result >= Max_long) result = Max_long;
	CAMLreturn(Val_long(result));
}

CAMLprim value mlgmp_z_set_bit(value x, value bit_index)
{
	CAMLparam2(x, bit_index);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_ptr result_value = Z_val(result);
	mpz_set(result_value, Z_val(x));
	mpz_setbit(result_value, Long_val(bit_index));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_clear_bit(value x, value bit_index)
{
	CAMLparam2(x, bit_index);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_ptr result_value = Z_val(result);
	mpz_set(result_value, Z_val(x));
	mpz_clrbit(result_value, Long_val(bit_index));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_test_bit(value x, value bit_index)
{
	CAMLparam2(x, bit_index);
	int result = mpz_tstbit(Z_val(x), Long_val(bit_index));
	CAMLreturn(Val_int(result));
}

CAMLprim value mlgmp_z_of_based_string(value base, value x)
{
	CAMLparam2(base, x);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	int err = mpz_set_str(Z_val(result), String_val(x), Int_val(base));
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
	result = mlgmp_alloc_z_init();
	mpz_set_si(Z_val(result), Long_val(x));
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
	result = mlgmp_alloc_z_init();
	mpz_set_si(Z_val(result), Int32_val(x));
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
	result = mlgmp_alloc_z_init();
#if LONG_BIT >= 64
	mpz_set_si(Z_val(result), Int64_val(x));
#elif LONG_BIT >= 32
	mpz_ptr result_value = Z_val(result);
	int64_t x_value = Int64_val(x);
	int32_t hi = x_value >> 32; /* arithmetic right shift */
	uint32_t lo = x_value & 0xffffffffUL;
	mpz_set_si(result_value, hi);
	mpz_mul_2exp(result_value, result_value, 32);
	mpz_add_ui(result_value, result_value, lo);
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
	mpz_t lo;
	mpz_init_set_ui(lo, 0xffffffffU);
	mpz_and(lo, x_value, lo);
	mpz_t hi;
	mpz_init(hi);
	mpz_fdiv_q_2exp(hi, x_value, 32);
	result = caml_copy_int64(((int64_t)mpz_get_si(hi) << 32) | mpz_get_ui(lo));
	mpz_clear(hi);
	mpz_clear(lo);
#else
#error "sizeof(long) < 4"
#endif
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_of_nativeint(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_set_si(Z_val(result), Nativeint_val(x));
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
	result = mlgmp_alloc_z_init();
	mpz_set_d(Z_val(result), Double_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_float_of_z(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = caml_copy_double(mpz_get_d(Z_val(x)));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_export_length(value x)
{
	CAMLparam1(x);
	mpz_srcptr x_value = Z_val(x);
	bool is_neg = mpz_sgn(x_value) < 0;
	mpz_t neg;
	mpz_srcptr from;
	if(is_neg){
		/* adjust to use complement on two */
		mpz_init(neg);
		mpz_add_ui(neg, x_value, 1);
		from = neg;
	}else{
		from = x_value;
	}
	int result = mpz_sizeinbase(from, 2) / 8 + 1; /* keeping MSB */
	if(is_neg){
		mpz_clear(neg);
	}
	CAMLreturn(Val_int(result));
}

CAMLprim value mlgmp_z_unsafe_export(
	value order,
	value x,
	value buf,
	value pos,
	value len)
{
	CAMLparam5(order, x, buf, pos, len);
	int order_value = Order_val(order);
	mpz_srcptr x_value = Z_val(x);
	size_t count;
	bool is_neg = mpz_sgn(x_value) < 0;
	mpz_t neg;
	mpz_srcptr from;
	if(is_neg){
		/* this adding one is a part of making complement on two */
		mpz_init(neg);
		mpz_add_ui(neg, x_value, 1);
		from = neg;
	}else{
		from = x_value;
	}
	uint8_t *s = mpz_export(NULL, &count, order_value, 1, 0, 0, from);
	if(is_neg){
		mpz_clear(neg);
	}
	ssize_t len_value = Long_val(len);
	ssize_t remains = len_value - count;
	uint8_t *d = Bytes_val(buf) + Long_val(pos);
	if(order_value > 0){
		/* most significant first */
		if(remains >= 0){
			memcpy(d + remains, s, count);
			memset(d, 0, remains);
		}else{
			memcpy(d, s - remains, count + remains);
		}
	}else{
		/* least significant first */
		if(remains >= 0){
			memcpy(d, s, count);
			memset(d + count, 0, remains);
		}else{
			memcpy(d, s, count + remains);
		}
	}
	free(s);
	if(is_neg){
		/* this bitwise-not is a part of making complement on two */
		for(ssize_t i = 0; i < len_value; ++i){
			d[i] = ~d[i];
		}
	}
	CAMLreturn(Val_unit);
}

CAMLprim value mlgmp_z_unsafe_import(
	value order,
	value signed_,
	value buf,
	value pos,
	value len)
{
	CAMLparam5(order, signed_, buf, pos, len);
	CAMLlocal1(result);
	int order_value = Order_val(order);
	result = mlgmp_alloc_z_init();
	mpz_ptr result_value = Z_val(result);
	uint8_t const *s = Bytes_val(buf) + Long_val(pos);
	ssize_t len_value = Long_val(len);
	mpz_import(result_value, len_value, order_value, 1, 0, 0, s);
	if(len_value > 0 && Bool_val(signed_)){
		bool is_neg;
		if(order_value > 0){
			/* most significant first */
			is_neg = (s[0] & 0x80) != 0;
		}else{
			/* least significant first */
			is_neg = (s[len_value - 1] & 0x80) != 0;
		}
		if(is_neg){
			mpz_t shifted;
			mpz_init_set_si(shifted, -1);
			mpz_mul_2exp(shifted, shifted, len_value * 8);
			mpz_ior(result_value, result_value, shifted);
			mpz_clear(shifted);
		}
	}
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

CAMLexport value mlgmp_alloc_q_init(void)
{
	CAMLparam0();
	CAMLlocal1(result);
	result = caml_alloc_custom(&mlgmp_q_ops, sizeof(mpq_t), 0, 1);
	mpq_init(Q_val(result));
	CAMLreturn(result);
}

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
	result = mlgmp_alloc_q_init();
	mpq_neg(Q_val(result), Q_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_abs(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = mlgmp_alloc_q_init();
	mpq_abs(Q_val(result), Q_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_add(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_q_init();
	mpq_add(Q_val(result), Q_val(left), Q_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_add_int(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_q_init();
	mpq_ptr result_value = Q_val(result);
	mpq_set_si(result_value, Long_val(right), 1);
	mpq_canonicalize(result_value); /* ? */
	mpq_add(result_value, Q_val(left), result_value);
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_sub(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_q_init();
	mpq_sub(Q_val(result), Q_val(left), Q_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_sub_int(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_q_init();
	mpq_ptr result_value = Q_val(result);
	mpq_set_si(result_value, Long_val(right), 1);
	mpq_canonicalize(result_value); /* ? */
	mpq_sub(result_value, Q_val(left), result_value);
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_mul(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_q_init();
	mpq_mul(Q_val(result), Q_val(left), Q_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_mul_int(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_q_init();
	mpq_ptr result_value = Q_val(result);
	mpq_set_si(result_value, Long_val(right), 1);
	mpq_canonicalize(result_value); /* ? */
	mpq_mul(result_value, Q_val(left), result_value);
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_div(value left, value right)
{
	CAMLparam2(left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_q_init();
	mpq_div(Q_val(result), Q_val(left), Q_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_fma(value val_x, value val_y, value val_z)
{
	CAMLparam3(val_x, val_y, val_z);
	CAMLlocal1(val_result);
	val_result = mlgmp_alloc_q_init();
	mpq_ptr result = Q_val(val_result);
	mpq_mul(result, Q_val(val_x), Q_val(val_y));
	mpq_add(result, result, Q_val(val_z));
	CAMLreturn(val_result);
}

CAMLprim value mlgmp_q_pow_int(value base, value exponent)
{
	CAMLparam2(base, exponent);
	CAMLlocal1(result);
	result = mlgmp_alloc_q_init();
	mpq_ptr result_value = Q_val(result);
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
	result = mlgmp_alloc_q_init();
	mpq_ptr result_value = Q_val(result);
	long b = Long_val(base);
	long e = Long_val(exponent);
	if(e < 0){
		if(b < 0){
			if(e % 2 != 0){
				mpz_set_si(mpq_numref(result_value), -1);
			}else{
				mpz_set_ui(mpq_numref(result_value), 1);
			}
			mpz_ui_pow_ui(mpq_denref(result_value), -b, -e);
		}else{
			mpz_set_ui(mpq_numref(result_value), 1);
			mpz_ui_pow_ui(mpq_denref(result_value), b, -e);
		}
	}else{
		if(b < 0){
			mpz_ptr result_num = mpq_numref(result_value);
			mpz_ui_pow_ui(result_num, -b, e);
			if(e % 2 != 0){
				mpz_neg(result_num, result_num);
			}
		}else{
			mpz_ui_pow_ui(mpq_numref(result_value), b, e);
		}
		mpz_set_ui(mpq_denref(result_value), 1);
	}
	mpq_canonicalize(result_value);
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_scale(value fraction, value base, value exponent)
{
	CAMLparam3(fraction, base, exponent);
	CAMLlocal1(result);
	result = mlgmp_alloc_q_init();
	mpq_ptr result_value = Q_val(result);
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
		if(e >= 0){
			mpz_ui_pow_ui(mpq_numref(result_value), b, e);
			mpz_set_ui(mpq_denref(result_value), 1);
		}else{
			mpz_set_ui(mpq_numref(result_value), 1);
			mpz_ui_pow_ui(mpq_denref(result_value), b, -e);
		}
		mpq_canonicalize(result_value);
		mpq_mul(result_value, f, result_value);
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_root(value nth, value x)
{
	CAMLparam2(nth, x);
	CAMLlocal1(result);
	result = mlgmp_alloc_q_init();
	mpq_ptr result_value = Q_val(result);
	long n = Long_val(nth);
	mpq_ptr x_value = Q_val(x);
	if(n == 1){
		mpq_set(result_value, x_value);
	}else{
		/* (d/n)^(1/nth) = ((d*n^(nth-1)) / (n^nth))^(1/nth) */
		/*               = (d*n^(nth-1))^(1/nth) / n */
		int i;
		mpz_ptr result_num = mpq_numref(result_value);
		mpz_mul(result_num, mpq_numref(x_value), mpq_denref(x_value));
		for(i = 3; i <= n; ++i){
			mpz_mul(result_num, result_num, mpq_denref(x_value));
		}
		mpz_root(result_num, result_num, n);
		mpz_set(mpq_denref(result_value), mpq_denref(x_value));
		mpq_canonicalize(result_value);
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_sqrt(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = mlgmp_alloc_q_init();
	mpq_ptr result_value = Q_val(result);
	mpq_ptr x_value = Q_val(x);
	/* (d/n)^(1/2) = ((d*n) / (n*n))^(1/2) = (d*n)^(1/2) / n */
	mpz_ptr result_num = mpq_numref(result_value);
	mpz_mul(result_num, mpq_numref(x_value), mpq_denref(x_value));
	mpz_sqrt(result_num, result_num);
	mpz_set(mpq_denref(result_value), mpq_denref(x_value));
	mpq_canonicalize(result_value);
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_num(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpq_get_num(Z_val(result), Q_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_den(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpq_get_den(Z_val(result), Q_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_of_based_string(value base, value x)
{
	CAMLparam2(base, x);
	CAMLlocal1(result);
	result = mlgmp_alloc_q_init();
	mpq_ptr result_value = Q_val(result);
	int b = Int_val(base);
	char const *x_value = String_val(x);
	char *period = strchr(x_value, '.');
	if(period == NULL){
		int err = mpq_set_str(result_value, x_value, b);
		if(err < 0) caml_failwith(__FUNCTION__);
		if(mpz_sgn(mpq_denref(result_value)) == 0) caml_raise_zero_divide();
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
	result = mlgmp_alloc_q_init();
	mpq_ptr result_value = Q_val(result);
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
	result = mlgmp_alloc_q_init();
	mpq_ptr result_value = Q_val(result);
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
	result = mlgmp_alloc_q_init();
	mpq_ptr result_value = Q_val(result);
	mpq_set_z(result_value, Z_val(x));
	mpq_canonicalize(result_value); /* ? */
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_of_truncated_q(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_set_q(Z_val(result), Q_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_make_int(value x, value y)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = mlgmp_alloc_q_init();
	mpq_ptr result_value = Q_val(result);
	long num = Long_val(x);
	long den = Long_val(y);
	if(den < 0){
		num = -num;
		den = -den;
	}
	mpq_set_si(result_value, num, den);
	mpq_canonicalize(result_value);
	CAMLreturn(result);
}

CAMLprim value mlgmp_q_make_z(value x, value y)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = mlgmp_alloc_q_init();
	mpq_ptr result_value = Q_val(result);
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

CAMLexport value mlgmp_alloc_f_init2(mp_bitcnt_t prec)
{
	CAMLparam0();
	CAMLlocal1(result);
	result = caml_alloc_custom(&mlgmp_f_ops, sizeof(mpf_t), 0, 1);
	mpf_init2(F_val(result), prec);
	CAMLreturn(result);
}

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

CAMLprim value mlgmp_f_neg(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_neg(F_val(result), F_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_abs(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_abs(F_val(result), F_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_add(value prec, value left, value right)
{
	CAMLparam3(prec, left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_add(F_val(result), F_val(left), F_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_add_int(value prec, value left, value right)
{
	CAMLparam3(prec, left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_ptr result_value = F_val(result);
	mpf_ptr l = F_val(left);
	long r = Long_val(right);
	if(r >= 0){
		mpf_add_ui(result_value, l, r);
	}else{
		mpf_sub_ui(result_value, l, -r);
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_sub(value prec, value left, value right)
{
	CAMLparam3(prec, left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_sub(F_val(result), F_val(left), F_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_sub_int(value prec, value left, value right)
{
	CAMLparam3(prec, left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_ptr result_value = F_val(result);
	mpf_ptr l = F_val(left);
	long r = Long_val(right);
	if(r >= 0){
		mpf_sub_ui(result_value, l, r);
	}else{
		mpf_add_ui(result_value, l, -r);
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_mul(value prec, value left, value right)
{
	CAMLparam3(prec, left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_mul(F_val(result), F_val(left), F_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_mul_int(value prec, value left, value right)
{
	CAMLparam3(prec, left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_ptr result_value = F_val(result);
	mpf_ptr l = F_val(left);
	long r = Long_val(right);
	if(r >= 0){
		mpf_mul_ui(result_value, l, r);
	}else{
		mpf_mul_ui(result_value, l, -r);
		mpf_neg(result_value, result_value);
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_div(value prec, value left, value right)
{
	CAMLparam3(prec, left, right);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_div(F_val(result), F_val(left), F_val(right));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_fma(
	value val_prec,
	value val_x,
	value val_y,
	value val_z)
{
	CAMLparam4(val_prec, val_x, val_y, val_z);
	CAMLlocal1(val_result);
	val_result = mlgmp_alloc_f_init2(Long_val(val_prec));
	mpf_ptr result = F_val(val_result);
	mpf_mul(result, F_val(val_x), F_val(val_y));
	mpf_add(result, result, F_val(val_z));
	CAMLreturn(val_result);
}

CAMLprim value mlgmp_f_pow_int(value prec, value base, value exponent)
{
	CAMLparam3(prec, base, exponent);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_ptr result_value = F_val(result);
	mpf_ptr b = F_val(base);
	long e = Long_val(exponent);
	if(e >= 0){
		mpf_pow_ui(result_value, b, e);
	}else{
		mpf_pow_ui(result_value, b, -e);
		mpf_ui_div(result_value, 1, result_value);
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_int_pow_int(value prec, value base, value exponent)
{
	CAMLparam3(prec, base, exponent);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_ptr result_value = F_val(result);
	long b = Long_val(base);
	long e = Long_val(exponent);
	if(b == 2){
		mpf_set_ui(result_value, 1);
		if(e < 0){
			mpf_div_2exp(result_value, result_value, -e);
		}else{
			mpf_mul_2exp(result_value, result_value, e);
		}
	}else if(b < 0){
		mpf_set_ui(result_value, -b);
		if(e < 0){
			mpf_pow_ui(result_value, result_value, -e);
			if(e % 2 != 0){
				mpf_neg(result_value, result_value);
			}
			mpf_ui_div(result_value, 1, result_value);
		}else{
			mpf_pow_ui(result_value, result_value, e);
			if(e % 2 != 0){
				mpf_neg(result_value, result_value);
			}
		}
	}else{
		mpf_set_ui(result_value, b);
		if(e < 0){
			mpf_pow_ui(result_value, result_value, -e);
			mpf_ui_div(result_value, 1, result_value);
		}else{
			mpf_pow_ui(result_value, result_value, e);
		}
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_scale(
	value prec,
	value fraction,
	value base,
	value exponent)
{
	CAMLparam4(prec, fraction, base, exponent);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_ptr result_value = F_val(result);
	mpf_ptr f = F_val(fraction);
	long b = Long_val(base);
	long e = Long_val(exponent);
	if(b == 2){
		if(e >= 0){
			mpf_mul_2exp(result_value, f, e);
		}else{
			mpf_div_2exp(result_value, f, -e);
		}
	}else{
		mpz_t a;
		mpz_init(a);
		if(e >= 0){
			mpz_ui_pow_ui(a, b, e);
			mpf_set_z(result_value, a);
			mpf_mul(result_value, f, result_value);
		}else{
			mpz_ui_pow_ui(a, b, -e);
			mpf_set_z(result_value, a);
			mpf_div(result_value, f, result_value);
		}
		mpz_clear(a);
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_root(value prec, value nth, value x)
{
	CAMLparam3(prec, nth, x);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_ptr result_value = F_val(result);
	long n = Long_val(nth);
	mpf_ptr x_value = F_val(x);
	if(n == 1){
		mpf_set(result_value, x_value);
	}else if(n == 2){
		mpf_sqrt(result_value, x_value);
	}else{
		/* exp (log x / nth) */
		long exponent;
		double mantissa = mpf_get_d_2exp(&exponent, x_value);
		double log_x = log(mantissa) + (double)exponent * M_LN2;
		mpf_set_d(result_value, exp(log_x / n));
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_sqrt(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_sqrt(F_val(result), F_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_nearly_equal(value bits, value left, value right)
{
	CAMLparam3(bits, left, right);
	bool result = mpf_eq(F_val(left), F_val(right), Long_val(bits));
	CAMLreturn(Val_bool(result));
}

CAMLprim value mlgmp_f_frexp(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal2(result, result_fraction);
	mpf_ptr x_value = F_val(x);
	long exponent;
	mpf_get_d_2exp(&exponent, x_value);
	if(exponent == 0){
		result_fraction = x;
	}else{
		result_fraction = mlgmp_alloc_f_init2(Long_val(prec));
		mpf_ptr rf_value = F_val(result_fraction);
		x_value = F_val(x); /* moved if gc was invoked by caml_alloc_... */
		if(exponent > 0){
			mpf_div_2exp(rf_value, x_value, exponent);
		}else{
			mpf_mul_2exp(rf_value, x_value, - exponent);
		}
	}
	result = caml_alloc_tuple(2);
	Store_field(result, 0, result_fraction);
	Store_field(result, 1, Val_long(exponent));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_trunc(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_trunc(F_val(result), F_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_ceil(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_ceil(F_val(result), F_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_floor(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_floor(F_val(result), F_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_log(value prec, value x)
{
	/* log x = log (m * 2^e)
	 *       = log m + log (2^e)
	 *       = log m + e * log 2 */
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	long exponent;
	double mantissa = mpf_get_d_2exp(&exponent, F_val(x));
	mpf_set_d(F_val(result), log(mantissa) + (double)exponent * M_LN2);
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_based_log(value prec, value base, value x)
{
	CAMLparam3(prec, base, x);
	CAMLlocal1(result);
	mp_bitcnt_t p = Long_val(prec);
	result = mlgmp_alloc_f_init2(p);
	mpf_ptr result_value = F_val(result);
	long b = Long_val(base);
	long exponent;
	double mantissa = mpf_get_d_2exp(&exponent, F_val(x));
	if(b == 2){
		mpf_set_d(result_value, log(mantissa) / M_LN2 + (double)exponent);
	}else if(b == 16){
		mpf_set_d(result_value, (log(mantissa) / M_LN2 + (double)exponent) / 4.0);
	}else{
		mpf_set_d(result_value, log(mantissa) + (double)exponent * M_LN2);
		mpf_t base_value;
		mpf_init2(base_value, p);
		mpf_set_ui(base_value, b);
		long base_exponent;
		double base_mantissa = mpf_get_d_2exp(&base_exponent, base_value);
		mpf_t logeb;
		mpf_init2(logeb, p);
		mpf_set_d(logeb, log(base_mantissa) + (double)base_exponent * M_LN2);
		mpf_div(result_value, result_value, logeb);
		mpf_clear(logeb);
		mpf_clear(base_value);
	}
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_of_based_string(value prec, value base, value x)
{
	CAMLparam3(prec, base, x);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	int err = mpf_set_str(F_val(result), String_val(x), Int_val(base));
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
	free(image);
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_get_str(value base, value digits, value x)
{
	CAMLparam3(base, digits, x);
	CAMLlocal1(result);
	mp_exp_t exponent;
	char *image = mpf_get_str(
		NULL,
		&exponent,
		Int_val(base),
		Long_val(digits),
		F_val(x));
	result = caml_alloc_tuple(2);
	Store_field(result, 0, caml_copy_string(image));
	Store_field(result, 1, Val_long(exponent));
	free(image);
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_of_int(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_set_si(F_val(result), Long_val(x));
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
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_set_d(F_val(result), x_value);
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
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_set_z(F_val(result), Z_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_z_of_truncated_f(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_set_f(Z_val(result), F_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_of_f(value prec, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = mlgmp_alloc_f_init2(Long_val(prec));
	mpf_set(F_val(result), F_val(x));
	CAMLreturn(result);
}

CAMLprim value mlgmp_f_default_prec(value unit)
{
	CAMLparam1(unit);
	long result = mpf_get_default_prec();
	CAMLreturn(Val_long(result));
}

/* setup */

CAMLprim value mlgmp_setup(value unit)
{
	CAMLparam1(unit);
	caml_register_custom_operations(&mlgmp_z_ops);
	caml_register_custom_operations(&mlgmp_q_ops);
	caml_register_custom_operations(&mlgmp_f_ops);
	CAMLreturn(Val_unit);
}
