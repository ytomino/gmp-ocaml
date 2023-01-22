open Gmp;;
open Mpfr;;
open Mpc;;

let gmp_cv = gmp_compiled_version_string ();;
let mpfr_cv = mpfr_compiled_version_string ();;
let mpc_cv = mpc_compiled_version_string ();;

let gmp_lv = gmp_get_version_string ();;
let mpfr_lv = mpfr_get_version_string ();;
let mpc_lv = mpc_get_version_string ();;

if gmp_cv <> gmp_lv || mpfr_cv <> mpfr_lv || mpc_cv <> mpc_lv then (
	Printf.printf "compiled with:\n";
	if gmp_cv <> gmp_lv then Printf.printf " GMP: %s\n" gmp_cv;
	if mpfr_cv <> mpfr_lv then Printf.printf " MPFR: %s\n" mpfr_cv;
	if mpc_cv <> mpc_lv then Printf.printf " MPC: %s\n" mpc_cv
);;

Printf.printf "GMP: %s\n" gmp_lv;;
Printf.printf "MPFR: %s\n" mpfr_lv;;
Printf.printf "MPC: %s\n" mpc_lv;;
