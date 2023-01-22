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

/* for version < 1.0.0 */

#if MPC_VERSION < 0x010000
#include "mpc_010000.h"
#endif

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
	CAMLreturnT(unsigned long, sizeof(mpc_t));
}

struct custom_operations mlmpc_c_ops = {
	.identifier = "jp.halfmoon.panathenaia.mpc.c",
	.finalize = mlmpc_c_finalize,
	.compare = mlmpc_c_custom_compare,
	.hash = mlmpc_c_hash,
	.serialize = mlmpc_c_serialize,
	.deserialize = mlmpc_c_deserialize};

CAMLexport value mlmpc_alloc_c_init3(mpfr_prec_t prec_r, mpfr_prec_t prec_i)
{
	CAMLparam0();
	CAMLlocal1(result);
	result = alloc_custom(&mlmpc_c_ops, sizeof(mpc_t), 0, 1);
	mpc_init3(C_val(result), prec_r, prec_i);
	CAMLreturn(result);
}

/* functions */

CAMLprim value mlmpc_c_compare(value left, value right)
{
	CAMLparam2(left, right);
	int result = mpc_cmp(C_val(left), C_val(right));
	CAMLreturn(Val_int(result));
}

CAMLprim value mlmpc_c_compare_int(value left, value right)
{
	CAMLparam2(left, right);
	int result = mpc_cmp_si(C_val(left), Long_val(right));
	CAMLreturn(Val_int(result));
}

CAMLprim value mlmpc_c_neg(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_neg(C_val(result), C_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_abs(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpc_abs(FR_val(result), C_val(x), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_add(value prec, value mode, value left, value right)
{
	CAMLparam4(prec, mode, left, right);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_add(C_val(result), C_val(left), C_val(right), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_add_int(value prec, value mode, value left, value right)
{
	CAMLparam4(prec, mode, left, right);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_add_si(C_val(result), C_val(left), Long_val(right), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_sub(value prec, value mode, value left, value right)
{
	CAMLparam4(prec, mode, left, right);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_sub(C_val(result), C_val(left), C_val(right), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_sub_int(value prec, value mode, value left, value right)
{
	CAMLparam4(prec, mode, left, right);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_rnd_t m = Crnd_val(mode);
	mpc_ptr l = C_val(left);
	long r = Long_val(right);
	if(r >= 0){
		mpc_sub_ui(C_val(result), l, r, m);
	}else{
		mpc_add_ui(C_val(result), l, -r, m);
	}
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_mul(value prec, value mode, value left, value right)
{
	CAMLparam4(prec, mode, left, right);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_mul(C_val(result), C_val(left), C_val(right), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_mul_int(value prec, value mode, value left, value right)
{
	CAMLparam4(prec, mode, left, right);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_mul_si(C_val(result), C_val(left), Long_val(right), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_div(value prec, value mode, value left, value right)
{
	CAMLparam4(prec, mode, left, right);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_div(C_val(result), C_val(left), C_val(right), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_pow_int(
	value prec,
	value mode,
	value base,
	value exponent)
{
	CAMLparam4(prec, mode, base, exponent);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_pow_si(C_val(result), C_val(base), Long_val(exponent), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_int_pow_int(
	value prec,
	value mode,
	value base,
	value exponent)
{
	CAMLparam4(prec, mode, base, exponent);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_ptr result_value = C_val(result);
	mpc_rnd_t m = Crnd_val(mode);
	long b = Long_val(base);
	long e = Long_val(exponent);
	mpfr_rnd_t real_rnd = MPC_RND_RE(m);
	mpfr_rnd_t imag_rnd = MPC_RND_IM(m);
	if(e < 0){
		long n;
		mpfr_ptr result_real = mpc_realref(result_value);
		if(b < 0){
			if(e % 2 != 0){
				n = -1;
			}else{
				n = 1;
			}
			mpfr_ui_pow_ui(result_real, -b, -e, real_rnd);
		}else{
			n = 1;
			mpfr_ui_pow_ui(result_real, b, -e, real_rnd);
		}
		mpfr_si_div(result_real, n, result_real, real_rnd);
	}else{
		if(b < 0){
			if(e % 2 != 0){
				mpfr_ptr result_real = mpc_realref(result_value);
				mpfr_ui_pow_ui(result_real, -b, e, real_rnd);
				mpfr_neg(result_real, result_real, real_rnd);
			}else{
				mpfr_ui_pow_ui(mpc_realref(result_value), -b, e, real_rnd);
			}
		}else{
			mpfr_ui_pow_ui(mpc_realref(result_value), b, e, real_rnd);
		}
	}
	mpfr_set_ui(mpc_imagref(result_value), 0, imag_rnd);
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_scale(
	value prec,
	value mode,
	value fraction,
	value base,
	value exponent)
{
	CAMLparam5(prec, mode, fraction, base, exponent);
	CAMLlocal1(result);
	mpfr_prec_t real_prec = Long_val(Field(prec, 0));
	result = mlmpc_alloc_c_init3(real_prec, Long_val(Field(prec, 1)));
	mpc_ptr result_value = C_val(result);
	mpc_rnd_t m = Crnd_val(mode);
	mpc_ptr f = C_val(fraction);
	long b = Long_val(base);
	long e = Long_val(exponent);
	if(b == 2){
		if(e >= 0){
			mpc_mul_2ui(result_value, f, e, m);
		}else{
			mpc_div_2ui(result_value, f, -e, m);
		}
	}else{
		mpfr_rnd_t real_rnd = MPC_RND_RE(m);
		mpfr_t a;
		mpfr_init2(a, real_prec);
		if(e >= 0){
			mpfr_ui_pow_ui(a, b, e, real_rnd);
			mpc_mul_fr(result_value, f, a, m);
		}else{
			mpfr_ui_pow_ui(a, b, -e, real_rnd);
			mpc_div_fr(result_value, f, a, m);
		}
		mpfr_clear(a);
	}
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_root(value prec, value mode, value nth, value x)
{
	CAMLparam4(prec, mode, nth, x);
	CAMLlocal1(result);
	mpfr_prec_t real_prec = Long_val(Field(prec, 0));
	result = mlmpc_alloc_c_init3(real_prec, Long_val(Field(prec, 1)));
	mpc_ptr result_value = C_val(result);
	mpc_rnd_t m = Crnd_val(mode);
	long n = Long_val(nth);
	mpc_ptr x_value = C_val(x);
	if(n == 1){
		mpc_set(result_value, x_value, m);
	}else if(n == 2){
		mpc_sqrt(result_value, x_value, m);
	}else{
		/* x^(1/nth) */
		mpfr_rnd_t real_rnd = MPC_RND_RE(m);
		mpfr_t a; /* 1/n */
		mpfr_init2(a, real_prec);
		mpfr_set_ui(a, 1, real_rnd);
		mpfr_div_ui(a, a, n, real_rnd);
		mpc_pow_fr(result_value, x_value, a, m);
		mpfr_clear(a);
	}
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_sqrt(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_sqrt(C_val(result), C_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_log(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_log(C_val(result), C_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_based_log(value prec, value mode, value base, value x)
{
	CAMLparam4(prec, mode, base, x);
	CAMLlocal1(result);
	mpfr_prec_t real_prec = Long_val(Field(prec, 0));
	mpfr_prec_t imag_prec = Long_val(Field(prec, 1));
	result = mlmpc_alloc_c_init3(real_prec, imag_prec);
	mpc_ptr result_value = C_val(result);
	mpc_rnd_t m = Crnd_val(mode);
	long b = Long_val(base);
	mpc_ptr x_value = C_val(x);
	if(b == 10){
		mpc_log10(result_value, x_value, m);
	}else{
		mpc_log(result_value, x_value, m);
		mpfr_rnd_t real_rnd = MPC_RND_RE(m);
		mpfr_t base_value;
		mpfr_init2(base_value, real_prec);
		mpfr_set_ui(base_value, b, real_rnd);
		mpfr_log(base_value, base_value, real_rnd);
		mpc_div_fr(result_value, result_value, base_value, m);
		mpfr_clear(base_value);
	}
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_pow(value prec, value mode, value base, value exponent)
{
	CAMLparam4(prec, mode, base, exponent);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_pow(C_val(result), C_val(base), C_val(exponent), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_exp(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_exp(C_val(result), C_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_conj(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_conj(C_val(result), C_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_norm2(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpc_norm(FR_val(result), C_val(x), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_arg(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpfr_alloc_fr_init2(Long_val(prec));
	mpc_arg(FR_val(result), C_val(x), Rnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_polar(value prec, value mode, value norm, value arg)
{
	CAMLparam4(prec, mode, norm, arg);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_rnd_t m = Crnd_val(mode);
	mpfr_rnd_t real_rnd = MPC_RND_RE(m);
	mpfr_rnd_t imag_rnd = MPC_RND_IM(m);
	mpc_ptr r = C_val(result);
	mpfr_ptr a = FR_val(arg);
	if(real_rnd == imag_rnd){
		mpfr_sin_cos(mpc_imagref(r), mpc_realref(r), a, real_rnd);
	}else{
		mpfr_cos(mpc_realref(r), a, real_rnd);
		mpfr_sin(mpc_imagref(r), a, imag_rnd);
	}
	mpc_mul_fr(r, r, FR_val(norm), m);
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_proj(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_proj(C_val(result), C_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_real(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	mpfr_ptr real = mpc_realref(C_val(x));
	result = mlmpfr_alloc_fr_init2(mpfr_get_prec(real));
	real = mpc_realref(C_val(x)); /* moved if gc was invoked by alloc_custom */
	mpfr_set(FR_val(result), real, GMP_RNDN);
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_imag(value x)
{
	CAMLparam1(x);
	CAMLlocal1(result);
	mpfr_ptr imag = mpc_imagref(C_val(x));
	result = mlmpfr_alloc_fr_init2(mpfr_get_prec(imag));
	imag = mpc_imagref(C_val(x)); /* moved if gc was invoked by alloc_custom */
	mpfr_set(FR_val(result), imag, GMP_RNDN);
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_of_based_string(
	value prec,
	value mode,
	value base,
	value x)
{
	CAMLparam4(prec, mode, base, x);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	int err = mpc_set_str(
		C_val(result),
		String_val(x),
		Int_val(base),
		Crnd_val(mode));
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
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_set_si(C_val(result), Long_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_of_float(value prec, value mode, value x)
{
	CAMLparam3(prec, mode, x);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_set_d(C_val(result), Double_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_of_z(value prec, value mode, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_set_z(C_val(result), Z_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_of_q(value prec, value mode, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_set_q(C_val(result), Q_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_of_f(value prec, value mode, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_set_f(C_val(result), F_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_of_fr(value prec, value mode, value x)
{
	CAMLparam2(prec, x);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_set_fr(C_val(result), FR_val(x), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_make_int(value prec, value mode, value r, value i)
{
	CAMLparam3(prec, r, i);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_set_si_si(C_val(result), Long_val(r), Long_val(i), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_make_float(value prec, value mode, value r, value i)
{
	CAMLparam3(prec, r, i);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_set_d_d(C_val(result), Double_val(r), Double_val(i), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_make_z(value prec, value mode, value r, value i)
{
	CAMLparam3(prec, r, i);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_set_z_z(C_val(result), Z_val(r), Z_val(i), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_make_q(value prec, value mode, value r, value i)
{
	CAMLparam3(prec, r, i);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_set_q_q(C_val(result), Q_val(r), Q_val(i), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_make_f(value prec, value mode, value r, value i)
{
	CAMLparam3(prec, r, i);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_set_f_f(C_val(result), F_val(r), F_val(i), Crnd_val(mode));
	CAMLreturn(result);
}

CAMLprim value mlmpc_c_make_fr(value prec, value mode, value r, value i)
{
	CAMLparam3(prec, r, i);
	CAMLlocal1(result);
	result = mlmpc_alloc_c_init3(
		Long_val(Field(prec, 0)),
		Long_val(Field(prec, 1)));
	mpc_set_fr_fr(C_val(result), FR_val(r), FR_val(i), Crnd_val(mode));
	CAMLreturn(result);
}

/* setup */

CAMLprim value mlmpc_setup(value unit)
{
	CAMLparam1(unit);
	register_custom_operations(&mlmpc_c_ops);
	CAMLreturn(Val_unit);
}
