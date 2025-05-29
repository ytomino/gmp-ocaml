open Gmp;;
open Mpfr;;
open Mpc;;

let log = false;;

let expect_invalid_arg (type t u) (f: t -> u) (x: t) =
	try let _: u = f x in false with
	| Invalid_argument _ -> true;;

assert (let x = 123 in int_of_z (z_of_int x) = x);;
assert (let x = -123 in int_of_z (z_of_int x) = x);;
assert (let x = 123l in int32_of_z (z_of_int32 x) = x);;
assert (let x = -123l in int32_of_z (z_of_int32 x) = x);;
assert (let x = 123n in nativeint_of_z (z_of_nativeint x) = x);;
assert (let x = -123n in nativeint_of_z (z_of_nativeint x) = x);;
assert (let x = 123L in int64_of_z (z_of_int64 x) = x);;
assert (let x = -123L in int64_of_z (z_of_int64 x) = x);;
assert (let x = 123. in float_of_z (z_of_truncated_float x) = x);;
assert (let x = -123. in float_of_z (z_of_truncated_float x) = x);;
assert (let x = "123" in string_of_z (z_of_string x) = x);;
assert (let x = "-123" in string_of_z (z_of_string x) = x);;

assert (expect_invalid_arg z_of_truncated_float Float.infinity);;
assert (expect_invalid_arg z_of_truncated_float Float.neg_infinity);;
assert (expect_invalid_arg z_of_truncated_float Float.nan);;

assert (let x = 123 in int_of_float (float_of_q (q_of_int x)) = x);;
assert (let x = -123 in int_of_float (float_of_q (q_of_int x)) = x);;
assert (let x = 1.5 in float_of_q (q_of_float x) = x);;
assert (let x = -1.5 in float_of_q (q_of_float x) = x);;
assert (let x = z_of_int 10 in z_of_truncated_q (q_of_z x) = x);;
assert (let x = z_of_int (-10) in z_of_truncated_q (q_of_z x) = x);;
assert (let x = "2/3" in string_of_q (q_of_string x) = x);;
assert (let x = "-2/3" in string_of_q (q_of_string x) = x);;
assert (Q.make_int 6 2 = q_of_int 3);;
assert (Q.make_int (-6) (-2) = q_of_int 3);;
assert (Q.make_z (z_of_int 6) (z_of_int 2) = q_of_int 3);;
assert (Q.make_z (z_of_int (-6)) (z_of_int (-2)) = q_of_int 3);;

assert (expect_invalid_arg q_of_float Float.infinity);;
assert (expect_invalid_arg q_of_float Float.neg_infinity);;
assert (expect_invalid_arg q_of_float Float.nan);;

assert (let x = 123 in int_of_float (float_of_f (f_of_int ~prec:8 x)) = x);;
assert (let x = -123 in int_of_float (float_of_f (f_of_int ~prec:8 x)) = x);;
assert (let x = 1.5 in float_of_f (f_of_float ~prec:2 x) = x);;
assert (let x = -1.5 in float_of_f (f_of_float ~prec:2 x) = x);;
assert (let x = z_of_int 10 in z_of_truncated_f (f_of_z ~prec:4 x) = x);;
assert (let x = z_of_int (-10) in z_of_truncated_f (f_of_z ~prec:4 x) = x);;
assert (let x = "0." in string_of_f (f_of_string ~prec:10 x) = x);;
assert (let x = "12." in string_of_f (f_of_string ~prec:10 x) = x);;
assert (let x = "100." in string_of_f (f_of_string ~prec:10 x) = x);;
assert (let x = "34.25" in string_of_f (f_of_string ~prec:10 x) = x);;
assert (let x = "0.0625" in string_of_f (f_of_string ~prec:10 x) = x);;
assert (let x = "-12." in string_of_f (f_of_string ~prec:10 x) = x);;
assert (let x = "-100." in string_of_f (f_of_string ~prec:10 x) = x);;
assert (let x = "-34.25" in string_of_f (f_of_string ~prec:10 x) = x);;
assert (let x = "-0.0625" in string_of_f (f_of_string ~prec:10 x) = x);;

assert (expect_invalid_arg (f_of_float ~prec:53) Float.infinity);;
assert (expect_invalid_arg (f_of_float ~prec:53) Float.neg_infinity);;
assert (expect_invalid_arg (f_of_float ~prec:53) Float.nan);;

assert (123. = float_of_fr ~mode:`N (fr_of_int ~prec:8 ~mode:`N 123));;
assert (-123. = float_of_fr ~mode:`N (fr_of_int ~prec:8 ~mode:`N (-123)));;
assert (
	fr_of_int ~prec:8 ~mode:`N 10 = fr_of_z ~prec:4 ~mode:`N (z_of_int 10)
);;
assert (string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N 0.) = "0.00000");;
assert (
	string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N 12352.) = "12352."
);;
assert (
	string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N 1000400.) = "1000400."
);;
assert (
	string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N 34.812) = "34.812"
);;
assert (
	string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N 0.015625) = "0.015625"
);;
assert (
	string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N (-12352.)) = "-12352."
);;
assert (
	string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N (-1000400.)) = "-1000400."
);;
assert (
	string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N (-34.25)) = "-34.250"
);;
assert (
	string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N (-0.015625)) = "-0.015625"
);;

(* assert (string_of_c ~mode:(`N, `N) (C.zero ~prec:(10, 10)) = "(+0 +0)");; *)

let inf = fr_of_float ~prec:10 ~mode:`N infinity in
let inf_str = string_of_float infinity in
assert (fr_of_string ~prec:10 ~mode:`N inf_str = inf);
assert (string_of_fr ~mode:`N inf = inf_str);;

let neg_inf = fr_of_float ~prec:10 ~mode:`N neg_infinity in
let neg_inf_str = string_of_float neg_infinity in
assert (fr_of_string ~prec:10 ~mode:`N neg_inf_str = neg_inf);
assert (string_of_fr ~mode:`N neg_inf = neg_inf_str);;

assert (
	c_of_int ~prec:(8, 8) ~mode:(`N, `N) 10
		= c_of_string ~prec:(4, 4) ~mode:(`N, `N) "10"
);;

assert (F.default_prec () = 64);;
assert (FR.default_prec () = 53);;
assert (FR.default_rounding_mode () = `N);;
assert (C.default_prec () = (53, 53));;
assert (C.default_rounding_mode () = (`N, `N));;

prerr_endline "ok";;
