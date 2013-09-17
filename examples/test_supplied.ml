open Gmp;;
open Mpfr;;
open Mpc;;

module F = Gmp.F (struct let prec = Gmp.default_prec () end);;
module FRm = Mpfr.FR (struct let prec = Mpfr.default_prec () end);;
module FR = FRm.F (struct let rounding_mode = Mpfr.default_rounding_mode () end);;
module Cm = Mpc.C (struct let prec = Mpc.default_prec () end);;
module C = Cm.F (struct let rounding_mode = Mpc.default_rounding_mode () end);;

(* mpz_add_si is missing *)
assert (Z.add_int (Z.of_int 4) (+1) = Z.of_int 5);;
assert (Z.add_int (Z.of_int 4) (-1) = Z.of_int 3);;

(* mpz_sub_si is missing *)
assert (Z.sub_int (Z.of_int 4) (+1) = Z.of_int 3);;
assert (Z.sub_int (Z.of_int 4) (-1) = Z.of_int 5);;

(* mpz_pow_si is missing *)
assert (Z.pow_int (Z.of_int 3) 3 = Z.of_int 27);;
assert (Z.pow_int (Z.of_int 3) (-3) = Z.zero);;
assert (Z.pow_int Z.zero 0 = Z.one);;
assert (Z.pow_int (Z.of_int (-3)) 2 = Z.of_int 9);;
assert (Z.pow_int (Z.of_int (-3)) 3 = Z.of_int (-27));;

(* mpz_si_pow_si is missing *)
assert (Z.int_pow_int 3 3 = Z.of_int 27);;
assert (Z.int_pow_int 3 (-3) = Z.zero);;
assert (Z.int_pow_int 0 0 = Z.one);;
assert (Z.int_pow_int (-3) 2 = Z.of_int 9);;
assert (Z.int_pow_int (-3) 3 = Z.of_int (-27));;

(* mpq_add_si is missing *)
assert (Q.add_int (Q.of_int 4) (+1) = Q.of_int 5);;
assert (Q.add_int (Q.of_int 4) (-1) = Q.of_int 3);;

(* mpq_sub_si is missing *)
assert (Q.sub_int (Q.of_int 4) (+1) = Q.of_int 3);;
assert (Q.sub_int (Q.of_int 4) (-1) = Q.of_int 5);;

(* mpq_mul_si is missing *)
assert (Q.mul_int (Q.of_int 4) (+2) = Q.of_int 8);;
assert (Q.mul_int (Q.of_int 4) (-2) = Q.of_int (-8));;

(* mpq_pow_si is missing *)
assert (Q.pow_int (Q.make_int 2 3) 3 = Q.make_int 8 27);;
assert (Q.pow_int (Q.make_int 2 3) 0 = Q.one);;
assert (Q.pow_int (Q.make_int 2 3) (-3) = Q.make_int 27 8);;
assert (Q.pow_int (Q.make_int (-2) 3) 3 = Q.make_int (-8) 27);;
assert (Q.pow_int (Q.make_int (-2) 3) 0 = Q.one);;
assert (Q.pow_int (Q.make_int (-2) 3) (-2) = Q.make_int 9 4);;
assert (Q.pow_int (Q.make_int (-2) 3) (-3) = Q.make_int (-27) 8);;

(* mpq_si_pow_si is missing *)
assert (Q.int_pow_int 3 3 = Q.make_int 27 1);;
assert (Q.int_pow_int 3 0 = Q.one);;
assert (Q.int_pow_int 3 (-3) = Q.make_int 1 27);;
assert (Q.int_pow_int (-3) 3 = Q.make_int (-27) 1);;
assert (Q.int_pow_int (-3) (-2) = Q.make_int 1 9);;
assert (Q.int_pow_int (-3) (-3) = Q.make_int (-1) 27);;

(* mpq_root is missing *)
assert (Q.root ~nth:1 (Q.make_int 2 3) = Q.make_int 2 3);
assert (Q.root ~nth:2 (Q.make_int 4 9) = Q.make_int 2 3);
assert (Q.root ~nth:3 (Q.make_int 8 27) = Q.make_int 2 3);

(* mpq_sqrt is missing *)
assert (Q.sqrt (Q.make_int 4 9) = Q.make_int 2 3);

(* mpf_add_si is missing *)
assert (F.add_int (F.of_int 4) (+1) = F.of_int 5);;
assert (F.add_int (F.of_int 4) (-1) = F.of_int 3);;

(* mpf_sub_si is missing *)
assert (F.sub_int (F.of_int 4) (+1) = F.of_int 3);;
assert (F.sub_int (F.of_int 4) (-1) = F.of_int 5);;

(* mpf_mul_si is missing *)
assert (F.mul_int (F.of_int 4) (+2) = F.of_int 8);;
assert (F.mul_int (F.of_int 4) (-2) = F.of_int (-8));;

(* mpf_pow_si is missing *)
assert (F.pow_int (F.of_int 2) 3 = F.of_int 8);;
assert (F.pow_int (F.of_int 2) (-3) = F.of_float (1.0 /. 8.0));;
assert (F.pow_int F.zero 0 = F.one);;
assert (F.pow_int (F.of_int (-2)) 2 = F.of_int 4);;
assert (F.pow_int (F.of_int (-2)) 3 = F.of_int (-8));;
assert (F.pow_int (F.of_int (-2)) (-2) = F.of_float (1.0 /. 4.0));;
assert (F.pow_int (F.of_int (-2)) (-3) = F.of_float (-1.0 /. 8.0));;

(* mpf_si_pow_si is missing *)
assert (F.int_pow_int 2 3 = F.of_int 8);;
assert (F.int_pow_int 2 (-3) = F.of_float (1.0 /. 8.0));;
assert (F.int_pow_int 0 0 = F.one);;
assert (F.int_pow_int (-2) 2 = F.of_int 4);;
assert (F.int_pow_int (-2) 3 = F.of_int (-8));;
assert (F.int_pow_int (-2) (-2) = F.of_float (1.0 /. 4.0));;
assert (F.int_pow_int (-2) (-3) = F.of_float (-1.0 /. 8.0));;

(* mpf_root is missing *)
assert (F.root ~nth:1 (F.of_int 2) = F.of_int 2);;
assert (F.root ~nth:2 (F.of_int 4) = F.of_int 2);;
assert (F.root ~nth:3 (F.of_int 8) = F.of_int 2);;

(* mpf_log is missing *)
let prec = 10 in
assert (F.nearly_equal prec (F.log (F.of_float 10.0)) (F.of_float 2.302585093));;
assert (F.based_log ~base:2 (F.of_int 2) = F.of_int 1);;
assert (F.based_log ~base:4 (F.of_int 4) = F.of_int 1);;

(* mpfr_si_pow_si is missing *)
assert (FR.int_pow_int 2 3 = FR.of_int 8);;
assert (FR.int_pow_int 2 (-3) = FR.of_float (1.0 /. 8.0));;
assert (FR.int_pow_int 0 0 = FR.one);;
assert (FR.int_pow_int (-2) 2 = FR.of_int 4);;
assert (FR.int_pow_int (-2) 3 = FR.of_int (-8));;
assert (FR.int_pow_int (-2) (-2) = FR.of_float (1.0 /. 4.0));;
assert (FR.int_pow_int (-2) (-3) = FR.of_float (-1.0 /. 8.0));;

(* mpc_sub_si is missing *)
assert (C.sub_int (C.of_int 4) (+1) = C.of_int 3);;
assert (C.sub_int (C.of_int 4) (-1) = C.of_int 5);;

(* mpc_si_pow_si is missing *)
assert (C.int_pow_int 2 3 = C.of_int 8);;
assert (C.int_pow_int 2 (-3) = C.of_float (1.0 /. 8.0));;
assert (C.int_pow_int 0 0 = C.one);;
assert (C.int_pow_int (-2) 2 = C.of_int 4);;
assert (C.int_pow_int (-2) 3 = C.of_int (-8));;
assert (C.int_pow_int (-2) (-2) = C.of_float (1.0 /. 4.0));;
assert (C.int_pow_int (-2) (-3) = C.of_float (-1.0 /. 8.0));;

(* mpc_root is missing *)
assert (C.root ~nth:1 (C.of_int 2) = C.of_int 2);;
assert (C.root ~nth:2 (C.of_int 4) = C.of_int 2);;
assert (C.root ~nth:3 (C.of_int 8) = C.of_int 2);;

Printf.eprintf "ok\n";;
