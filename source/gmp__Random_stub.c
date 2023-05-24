#include "gmp_stub.h"

#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/memory.h>

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
	result = caml_alloc_custom(&random_ops, sizeof(gmp_randstate_t), 0, 1);
	gmp_randinit_default(Random_val(result));
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_create_lc_2exp(value a, value c, value m2exp)
{
	CAMLparam3(a, c, m2exp);
	CAMLlocal1(result);
	result = caml_alloc_custom(&random_ops, sizeof(gmp_randstate_t), 0, 1);
	gmp_randinit_lc_2exp(
		Random_val(result),
		Z_val(a),
		Long_val(c),
		Long_val(m2exp));
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_create_lc_2exp_size(value size)
{
	CAMLparam1(size);
	CAMLlocal1(result);
	result = caml_alloc_custom(&random_ops, sizeof(gmp_randstate_t), 0, 1);
	gmp_randinit_lc_2exp_size(Random_val(result), Long_val(size));
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_create_mt(value unit)
{
	CAMLparam1(unit);
	CAMLlocal1(result);
	result = caml_alloc_custom(&random_ops, sizeof(gmp_randstate_t), 0, 1);
	gmp_randinit_mt(Random_val(result));
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
	result = caml_alloc_custom(&random_ops, sizeof(gmp_randstate_t), 0, 1);
	gmp_randinit_set(Random_val(result), Random_val(source));
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_int_bits(value state, value bits)
{
	CAMLparam2(state, bits);
	long result = gmp_urandomb_ui(Random_val(state), Long_val(bits));
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
	CAMLlocal1(result);
#if LONG_BIT >= 64
	result = caml_copy_int64(gmp_urandomm_ui(Random_val(state), Int64_val(n)));
#elif LONG_BIT >= 32
	mpz_t nz;
	mpz_init(nz);
	int64_t n_value = Int64_val(n);
	mpz_set_si(nz, n_value >> 32);
	mpz_mul_2exp(nz, nz, 32);
	mpz_add_ui(nz, nz, n_value & 0xffffffffUL);
	mpz_t r;
	mpz_init(r);
	mpz_urandomm(r, Random_val(state), nz);
	mpz_t lo;
	mpz_init(lo);
	mpz_init_set_ui(lo, 0xffffffffU);
	mpz_and(lo, r, lo);
	mpz_fdiv_q_2exp(r, r, 32);
	result = caml_copy_int64(((int64_t)mpz_get_si(r) << 32) | mpz_get_ui(lo));
	mpz_clear(lo);
	mpz_clear(r);
	mpz_clear(nz);
#else
#error "sizeof(long) < 4"
#endif
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_nativeint(value state, value n)
{
	CAMLparam2(state, n);
	CAMLlocal1(result);
	result = caml_copy_nativeint(
		gmp_urandomm_ui(Random_val(state), Nativeint_val(n)));
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_float_bits(value state, value bits)
{
	CAMLparam2(state, bits);
	CAMLlocal1(result);
	mp_bitcnt_t b = Long_val(bits);
	mpf_t r;
	mpf_init2(r, b);
	mpf_urandomb(r, Random_val(state), b);
	result = caml_copy_double(mpf_get_d(r));
	mpf_clear(r);
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_z(value state, value n)
{
	CAMLparam2(state, n);
	CAMLlocal1(result);
	result = mlgmp_alloc_z_init();
	mpz_urandomm(Z_val(result), Random_val(state), Z_val(n));
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_f_bits(value state, value bits)
{
	CAMLparam2(state, bits);
	CAMLlocal1(result);
	mp_bitcnt_t b = Long_val(bits);
	result = mlgmp_alloc_f_init2(b);
	mpf_urandomb(F_val(result), Random_val(state), b);
	CAMLreturn(result);
}

CAMLprim value mlgmp_random_f(value state, value prec, value n)
{
	CAMLparam3(state, prec, n);
	CAMLlocal1(result);
	mp_bitcnt_t b = Long_val(prec);
	result = mlgmp_alloc_f_init2(b);
	mpf_ptr result_value = F_val(result);
	mpf_urandomb(result_value, Random_val(state), b);
	mpf_mul(result_value, result_value, F_val(n));
	CAMLreturn(result);
}
