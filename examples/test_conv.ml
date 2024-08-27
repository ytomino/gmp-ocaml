open Gmp;;
open Mpfr;;
open Mpc;;

let log = false;;

assert (123 = int_of_z (z_of_int 123));;
assert (123l = int32_of_z (z_of_int32 123l));;
assert (123n = nativeint_of_z (z_of_nativeint 123n));;
assert (123L = int64_of_z (z_of_int64 123L));;
assert (123.0 = float_of_z (z_of_string "123"));;

assert (-123 = int_of_z (z_of_int (-123)));;
assert (-123l = int32_of_z (z_of_int32 (-123l)));;
assert (-123n = nativeint_of_z (z_of_nativeint (-123n)));;
assert (-123L = int64_of_z (z_of_int64 (-123L)));;
assert (-123.0 = float_of_z (z_of_string "-123"));;

assert (123.0 = float_of_q (q_of_int 123));;
assert (-123.0 = float_of_q (q_of_int (-123)));;
assert (q_of_int 10 = q_of_z (z_of_int 10));;
assert (Q.make_int 6 2 = q_of_int 3);;
assert (Q.make_int ~-6 ~-2 = q_of_int 3);;

assert (123.0 = float_of_f (f_of_int ~prec:8 123));;
assert (-123.0 = float_of_f (f_of_int ~prec:8 (-123)));;
assert (f_of_int ~prec:8 10 = f_of_z ~prec:4 (z_of_int 10));;
assert (string_of_f (f_of_float ~prec:10 0.0) = "0.");;
assert (string_of_f (f_of_float ~prec:10 12.0) = "12.");;
assert (string_of_f (f_of_float ~prec:10 100.0) = "100.");;
assert (string_of_f (f_of_float ~prec:10 34.25) = "34.25");;
assert (string_of_f (f_of_float ~prec:10 0.0625) = "0.0625");;
assert (string_of_f (f_of_float ~prec:10 ~-.12.0) = "-12.");;
assert (string_of_f (f_of_float ~prec:10 ~-.100.0) = "-100.");;
assert (string_of_f (f_of_float ~prec:10 ~-.34.25) = "-34.25");;
assert (string_of_f (f_of_float ~prec:10 ~-.0.0625) = "-0.0625");;

assert (123.0 = float_of_fr ~mode:`N (fr_of_int ~prec:8 ~mode:`N 123));;
assert (-123.0 = float_of_fr ~mode:`N (fr_of_int ~prec:8 ~mode:`N (-123)));;
assert (
	fr_of_int ~prec:8 ~mode:`N 10 = fr_of_z ~prec:4 ~mode:`N (z_of_int 10)
);;
assert (
	string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N 0.0) = "0.00000"
);;
assert (
	string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N 12352.0) = "12352."
);;
assert (
	string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N 1000400.0) = "1000400."
);;
assert (
	string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N 34.812) = "34.812"
);;
assert (
	string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N 0.015625) = "0.015625"
);;
assert (
	string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N ~-.12352.0) = "-12352."
);;
assert (
	string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N ~-.1000400.0)
		= "-1000400."
);;
assert (
	string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N ~-.34.25) = "-34.250"
);;
assert (
	string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N ~-.0.015625) = "-0.015625"
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
