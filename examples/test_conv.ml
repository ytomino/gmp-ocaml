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

assert (123.0 = float_of_f (f_of_int ~prec:8 123));;
assert (-123.0 = float_of_f (f_of_int ~prec:8 (-123)));;
assert (f_of_int ~prec:8 10 = f_of_z ~prec:4 (z_of_int 10));;
assert (string_of_f (f_of_float ~prec:10 0.0) = "0");;
assert (string_of_f (f_of_float ~prec:10 12.0) = "12");;
assert (string_of_f (f_of_float ~prec:10 100.0) = "100");;
assert (string_of_f (f_of_float ~prec:10 34.25) = "34.25");;
assert (string_of_f (f_of_float ~prec:10 0.0625) = "0.0625");;
assert (string_of_f (f_of_float ~prec:10 ~-.12.0) = "-12");;
assert (string_of_f (f_of_float ~prec:10 ~-.100.0) = "-100");;
assert (string_of_f (f_of_float ~prec:10 ~-.34.25) = "-34.25");;
assert (string_of_f (f_of_float ~prec:10 ~-.0.0625) = "-0.0625");;

assert (123.0 = float_of_fr ~mode:`N (fr_of_int ~prec:8 ~mode:`N 123));;
assert (-123.0 = float_of_fr ~mode:`N (fr_of_int ~prec:8 ~mode:`N (-123)));;
assert (fr_of_int ~prec:8 ~mode:`N 10 = fr_of_z ~prec:4 ~mode:`N (z_of_int 10));;
assert (string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N 0.0) = "0.00000");;
assert (string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N 12352.0) = "12352");;
assert (string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N 1000400.0) = "1000400");;
assert (string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N 34.812) = "34.812");;
assert (string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N 0.015625) = "0.015625");;
assert (string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N ~-.12352.0) = "-12352");;
assert (string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N ~-.1000400.0) = "-1000400");;
assert (string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N ~-.34.25) = "-34.250");;
assert (string_of_fr ~mode:`N (fr_of_float ~prec:10 ~mode:`N ~-.0.015625) = "-0.015625");;

let bit_eq (x: float) (y: float): bool = (
	x = y || (classify_float x = FP_nan && classify_float y = FP_nan)
);;

let single_check (x: float) (y: int32) = (
	let x1 = bits_of_single (fr_of_float ~prec:24 ~mode:`N x) in
	if log then Printf.eprintf "%.8lx" x1;
	let y1 = float_of_fr ~mode:`N (single_of_bits y) in
	if log then Printf.eprintf " %f\n" y1;
	x1 = y && bit_eq y1 x
);;

assert (single_check 0.0 0x00000000l);;
assert (single_check 1.0 0x3f800000l);;
assert (single_check 2.0 0x40000000l);;
assert (single_check 3.0 0x40400000l);;
assert (single_check 0.5 0x3f000000l);;
assert (single_check ~-.1.0 0xbf800000l);;
assert (single_check ~-.0.0 0x80000000l);;
assert (single_check ~-.1.25 0xbfa00000l);;
assert (single_check nan 0x7fc00000l);;
assert (single_check infinity 0x7f800000l);;
assert (single_check ~-.infinity 0xff800000l);;

let double_check (x: float) (y: int64) = (
	let x1 = bits_of_double (fr_of_float ~prec:53 ~mode:`N x) in
	if log then Printf.eprintf "%.16Lx" x1;
	let y1 = float_of_fr ~mode:`N (double_of_bits y) in
	if log then Printf.eprintf " %f\n" y1;
	x1 = y && bit_eq y1 x
);;

assert (double_check 0.0 0x0000000000000000L);;
assert (double_check 1.0 0x3ff0000000000000L);;
assert (double_check 2.0 0x4000000000000000L);;
assert (double_check 3.0 0x4008000000000000L);;
assert (double_check 0.5 0x3fe0000000000000L);;
assert (double_check ~-.1.0 0xbff0000000000000L);;
assert (double_check ~-.0.0 0x8000000000000000L);;
assert (double_check ~-.1.25 0xbff4000000000000L);;
assert (double_check nan 0x7ff8000000000000L);;
assert (double_check infinity 0x7ff0000000000000L);;
assert (double_check ~-.infinity 0xfff0000000000000L);;

let extended_check (x: float) (y: int64 * int) = (
	let (m, e) as x1 = bits_of_extended (fr_of_float ~prec:64 ~mode:`N x) in
	if log then Printf.eprintf "%.4x:%.16Lx" e m;
	let y1 = float_of_fr ~mode:`N (extended_of_bits y) in
	if log then Printf.eprintf " %f\n" y1;
	x1 = y && bit_eq y1 x
);;

assert (extended_check 0.0 (0x0000000000000000L, 0x0000));;
assert (extended_check 1.0 (0x8000000000000000L, 0x3fff));;
assert (extended_check 2.0 (0x8000000000000000L, 0x4000));;
assert (extended_check 3.0 (0xc000000000000000L, 0x4000));;
assert (extended_check 0.5 (0x8000000000000000L, 0x3ffe));;
assert (extended_check ~-.1.0 (0x8000000000000000L, 0xbfff));;
assert (extended_check ~-.0.0 (0x0000000000000000L, 0x8000));;
assert (extended_check ~-.1.25 (0xa000000000000000L, 0xbfff));;
assert (extended_check nan (0xc000000000000000L, 0x7fff));;
assert (extended_check infinity (0x8000000000000000L, 0x7fff));;
assert (extended_check ~-.infinity (0x8000000000000000L, 0xffff));;

assert (c_of_int ~prec:(8, 8) ~mode:(`N, `N) 10 = c_of_string ~prec:(4, 4) ~mode:(`N, `N) "10");;

assert (Gmp.default_prec () = 64);;
assert (Mpfr.default_prec () = 53);;
assert (Mpfr.default_rounding_mode () = `N);;
assert (Mpc.default_prec () = (53, 53));;
assert (Mpc.default_rounding_mode () = (`N, `N));;

Printf.eprintf "ok\n";;
