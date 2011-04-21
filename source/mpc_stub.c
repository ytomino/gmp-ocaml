#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/fail.h>
#include <caml/intext.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>
#include <limits.h>
#include <string.h>
#include <mpc.h>
#include "gmp_stub.h"
#include "mpfr_stub.h"
#include "mpc_stub.h"

/**** C ****/

/* custom data */

static void mlmpc_c_finalize(value x)
{
	mpc_clear(C_val(x));
}

static int mlmpc_c_custom_compare(value left, value right)
{
	CAMLparam2(left, right);
	int result = mpc_cmp(C_val(left), C_val(right));
	CAMLreturnT(int, result);
}

static long mlmpc_c_hash(value x)
{
	CAMLparam1(x);
	long result = c_hash(C_val(x));
	CAMLreturnT(long, result);
}

static void mlmpc_c_serialize(value x,
	unsigned long *wsize_32, unsigned long *wsize_64)
{
	CAMLparam1(x);
	*wsize_32 = WSIZE_32_C;
	*wsize_64 = WSIZE_64_C;
	c_serialize(C_val(x));
	CAMLreturn0;
}

static unsigned long mlmpc_c_deserialize(void *dst)
{
	CAMLparam0();
	c_deserialize((mpc_ptr)dst);
	CAMLreturnT(unsigned long, sizeof(mpfr_t));
}

struct custom_operations mlmpc_c_ops = {
	.identifier = "jp.halfmoon.panathenaia.mpc.c",
	.finalize = mlmpc_c_finalize,
	.compare = mlmpc_c_custom_compare,
	.hash = mlmpc_c_hash,
	.serialize = mlmpc_c_serialize,
	.deserialize = mlmpc_c_deserialize};

/* functions */

CAMLprim value mlmpc_c_compare(value left, value right)
{
	CAMLparam2(left, right);
	int result = mpc_cmp(C_val(left), C_val(right));
	CAMLreturn(Val_int(result));
}

CAMLprim value mlmpc_c_neg(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpc_neg(result_value, C_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_add(value prec, value mode, value left, value right)
{
	CAMLparam4(prec, mode, left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpc_add(result_value, C_val(left), C_val(right), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_add_int(value prec, value mode, value left, value right)
{
	CAMLparam4(prec, mode, left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpc_add_si(result_value, C_val(left), Int_val(right), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_sub(value prec, value mode, value left, value right)
{
	CAMLparam4(prec, mode, left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpc_sub(result_value, C_val(left), C_val(right), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_mul(value prec, value mode, value left, value right)
{
	CAMLparam4(prec, mode, left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpc_mul(result_value, C_val(left), C_val(right), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_div(value prec, value mode, value left, value right)
{
	CAMLparam4(prec, mode, left, right);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpc_div(result_value, C_val(left), C_val(right), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_int_pow_int(value prec, value mode, value base, value exponent)
{
	CAMLparam4(prec, mode, base, exponent);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpz_t a;
	mpz_init(a);
	mpz_ui_pow_ui(a, Int_val(base), Int_val(exponent));
	mpc_set_z(result_value, a, Crnd_val(mode));
	mpz_clear(a);
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_scale(value prec, value mode, value fraction, value base, value exponent)
{
	CAMLparam5(prec, mode, fraction, base, exponent);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpfr_prec_t real_prec = Int_val(Field(prec, 0));
	mpc_init3(result_value, real_prec, Int_val(Field(prec, 1)));
	mpc_rnd_t m = Crnd_val(mode);
	int b = Int_val(base);
	int e = Int_val(exponent);
	mpc_ptr f = C_val(fraction);
	if(b == 2){
		if(e >= 0){
			mpc_mul_2exp(result_value, f, e, m);
		}else{
			mpc_div_2exp(result_value, f, -e, m);
		}
	}else{
		mpfr_rnd_t real_rounding = MPC_RND_RE(m);
		mpfr_t a;
		mpfr_init2(a, real_prec);
		if(e >= 0){
			mpfr_ui_pow_ui(a, b, e, real_rounding);
			mpc_mul_fr(result_value, f, a, m);
		}else{
			mpfr_ui_pow_ui(a, b, -e, real_rounding);
			mpc_div_fr(result_value, f, a, m);
		}
		mpfr_clear(a);
	}
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_based_log(value prec, value mode, value base, value x)
{
	CAMLparam4(prec, mode, base, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpfr_prec_t real_prec = Int_val(Field(prec, 0));
	mpfr_prec_t imag_prec = Int_val(Field(prec, 1));
	mpc_init3(result_value, real_prec, imag_prec);
	mpc_rnd_t m = Crnd_val(mode);
	mpc_ptr x_value = C_val(x);
	mpc_t n;
	mpc_init3(n, real_prec, imag_prec);
	mpc_log(n, x_value, m);
	mpc_t base_value;
	mpc_init3(base_value, real_prec, imag_prec);
	mpc_set_si(base_value, Int_val(base), m);
	mpc_t d;
	mpc_init3(d, real_prec, imag_prec);
	mpc_log(d, base_value, m);
	mpc_div(result_value, n, d, m);
	mpc_clear(d);
	mpc_clear(n);
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_log(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpc_log(result_value, C_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_real(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpfr_fr_ops, sizeof(mpfr_t), 0, 1);
	mpfr_ptr result_value = FR_val(result);
	mpfr_ptr real = mpc_realref(C_val(x));
	mpfr_init2(result_value, mpfr_get_prec(real));
	mpfr_set(result_value, real, GMP_RNDN);
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_imag(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpfr_fr_ops, sizeof(mpfr_t), 0, 1);
	mpfr_ptr result_value = FR_val(result);
	mpfr_ptr imag = mpc_imagref(C_val(x));
	mpfr_init2(result_value, mpfr_get_prec(imag));
	mpfr_set(result_value, imag, GMP_RNDN);
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_of_based_string(value prec, value mode, value base, value x)
{
	CAMLparam4(prec, mode, base, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	int err = mpc_set_str(result_value, String_val(x), Int_val(base), Crnd_val(mode));
	if(err < 0) caml_failwith(__FUNCTION__);
	CAMLreturn(result);
}

CAMLprim value mlmpc_based_string_of_c(value mode, value base, value x)
{
	CAMLparam3(mode, base, x);
	CAMLlocal1(result);
	char *image = mpc_get_str(Int_val(base), 0, C_val(x), Crnd_val(mode));
	result = caml_copy_string(image);
	mpc_free_str(image);
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_of_int(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpc_set_si(result_value, Int_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_of_float(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpc_set_d(result_value, Double_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_of_z(value prec, value mode, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpc_set_z(result_value, Z_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_of_q(value prec, value mode, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpc_set_q(result_value, Q_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_of_f(value prec, value mode, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpc_set_f(result_value, F_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_of_fr(value prec, value mode, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpc_set_fr(result_value, FR_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_make_int(value prec, value mode, value r, value i)
{
	CAMLparam3(prec, r, i);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpc_set_si_si(result_value, Int_val(r), Int_val(i), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_make_float(value prec, value mode, value r, value i)
{
	CAMLparam3(prec, r, i);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpc_set_d_d(result_value, Double_val(r), Double_val(i), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_make_z(value prec, value mode, value r, value i)
{
	CAMLparam3(prec, r, i);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpc_set_z_z(result_value, Z_val(r), Z_val(i), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_make_q(value prec, value mode, value r, value i)
{
	CAMLparam3(prec, r, i);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpc_set_q_q(result_value, Q_val(r), Q_val(i), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_make_f(value prec, value mode, value r, value i)
{
	CAMLparam3(prec, r, i);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpc_set_f_f(result_value, F_val(r), F_val(i), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_make_fr(value prec, value mode, value r, value i)
{
	CAMLparam3(prec, r, i);
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_ptr result_value = C_val(result);
	mpc_init3(result_value, Int_val(Field(prec, 0)), Int_val(Field(prec, 1)));
	mpc_set_fr_fr(result_value, FR_val(r), FR_val(i), Crnd_val(mode));
	CAMLreturn(result);
}

/* setup */

CAMLprim value mlmpc_setup(value unit)
{
  CAMLparam1(unit);
  register_custom_operations(&mlmpc_c_ops);
  CAMLreturn(Val_unit);
}
