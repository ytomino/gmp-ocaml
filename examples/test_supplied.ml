open Gmp;;
open Mpfr;;
open Mpc;;

module F = F.Make (val F.default ());;
module FR = FR.Make (val FR.default ());;
module C = C.Make (val C.default ());;

(* mpz_add_si is missing *)
assert (Z.add_int (Z.of_int 4) 1 = Z.of_int 5);;
assert (Z.add_int (Z.of_int 4) (-1) = Z.of_int 3);;

(* mpz_sub_si is missing *)
assert (Z.sub_int (Z.of_int 4) 1 = Z.of_int 3);;
assert (Z.sub_int (Z.of_int 4) (-1) = Z.of_int 5);;

(* mpz_fma is missing *)
assert (Z.fma (Z.of_int 2) (Z.of_int 3) (Z.of_int 5) = Z.of_int 11);;

(* mpz_pow_si is missing *)
assert (Z.pow_int ~base:(Z.of_int 3) ~exponent:3 = Z.of_int 27);;
assert (Z.pow_int ~base:(Z.of_int 3) ~exponent:(-3) = Z.zero);;
assert (Z.pow_int ~base:Z.zero ~exponent:0 = Z.one);;
assert (Z.pow_int ~base:(Z.of_int (-3)) ~exponent:2 = Z.of_int 9);;
assert (Z.pow_int ~base:(Z.of_int (-3)) ~exponent:3 = Z.of_int (-27));;

(* mpz_si_pow_si is missing *)
assert (Z.int_pow_int ~base:3 ~exponent:3 = Z.of_int 27);;
assert (Z.int_pow_int ~base:3 ~exponent:(-3) = Z.zero);;
assert (Z.int_pow_int ~base:0 ~exponent:0 = Z.one);;
assert (Z.int_pow_int ~base:(-3) ~exponent:2 = Z.of_int 9);;
assert (Z.int_pow_int ~base:(-3) ~exponent:3 = Z.of_int (-27));;

(* mpz_tdiv_q_si, mpz_cdiv_q_si, and mpz_fdiv_q_si are missing *)
let table = [
	(Z.tdiv, Z.tdiv_int, 't');
	(Z.fdiv, Z.fdiv_int, 'f');
	(Z.cdiv, Z.cdiv_int, 'c')
]
in
List.iter (fun (f1, f2, id) ->
	for d = -10 to 10 do
		if d <> 0 then (
			for n = -10 to 10 do
				let r1, q1 = f1 (Z.of_int n) (Z.of_int d) in
				let r2, q2 = f2 (Z.of_int n) d in
				if Z.compare r1 r2 <> 0 || Z.compare_int q1 q2 <> 0 then (
					Printf.eprintf "Z.%cdiv %d %d = %s, %s\n" id n d (Z.to_string r1)
						(Z.to_string q1);
					Printf.eprintf "Z.%cdiv_int %d %d = %s, %d\n" id n d (Z.to_string r2) q2;
					assert false
				)
			done
		)
	done
) table;;

(* mpz_and_si is missing *)
assert (Z.logand_int (Z.of_int 7) 14 = Z.of_int 6);;
assert (Z.logand_int (Z.of_int 7) (-2) = Z.of_int 6);;

(* mpz_ior_si is missing *)
assert (Z.logor_int (Z.of_int 7) 14 = Z.of_int 15);;
assert (Z.logor_int (Z.of_int 7) (-2) = Z.minus_one);;

(* mpz_xor_si is missing *)
assert (Z.logxor_int (Z.of_int 7) 14 = Z.of_int 9);;
assert (Z.logxor_int (Z.of_int 7) (-2) = Z.of_int (-7));;

(* mpq_add_si is missing *)
assert (Q.add_int (Q.of_int 4) 1 = Q.of_int 5);;
assert (Q.add_int (Q.of_int 4) (-1) = Q.of_int 3);;

(* mpq_sub_si is missing *)
assert (Q.sub_int (Q.of_int 4) 1 = Q.of_int 3);;
assert (Q.sub_int (Q.of_int 4) (-1) = Q.of_int 5);;

(* mpq_mul_si is missing *)
assert (Q.mul_int (Q.of_int 4) 2 = Q.of_int 8);;
assert (Q.mul_int (Q.of_int 4) (-2) = Q.of_int (-8));;

(* mpq_fma is missing *)
assert (Q.fma (Q.of_int 2) (Q.of_int 3) (Q.of_int 5) = Q.of_int 11);;

(* mpq_pow_si is missing *)
assert (Q.pow_int ~base:(Q.make_int 2 3) ~exponent:3 = Q.make_int 8 27);;
assert (Q.pow_int ~base:(Q.make_int 2 3) ~exponent:0 = Q.one);;
assert (Q.pow_int ~base:(Q.make_int 2 3) ~exponent:(-3) = Q.make_int 27 8);;
assert (Q.pow_int ~base:(Q.make_int (-2) 3) ~exponent:2 = Q.make_int 4 9);;
assert (Q.pow_int ~base:(Q.make_int (-2) 3) ~exponent:3 = Q.make_int (-8) 27);;
assert (Q.pow_int ~base:(Q.make_int (-2) 3) ~exponent:(-2) = Q.make_int 9 4);;
assert (
	Q.pow_int ~base:(Q.make_int (-2) 3) ~exponent:(-3) = Q.make_int (-27) 8
);;

(* mpq_si_pow_si is missing *)
assert (Q.int_pow_int ~base:3 ~exponent:3 = Q.make_int 27 1);;
assert (Q.int_pow_int ~base:3 ~exponent:0 = Q.one);;
assert (Q.int_pow_int ~base:3 ~exponent:(-3) = Q.make_int 1 27);;
assert (Q.int_pow_int ~base:(-3) ~exponent:2 = Q.make_int 9 1);;
assert (Q.int_pow_int ~base:(-3) ~exponent:3 = Q.make_int (-27) 1);;
assert (Q.int_pow_int ~base:(-3) ~exponent:(-2) = Q.make_int 1 9);;
assert (Q.int_pow_int ~base:(-3) ~exponent:(-3) = Q.make_int (-1) 27);;

(* mpq_root is missing *)
assert (Q.root ~nth:1 (Q.make_int 2 3) = Q.make_int 2 3);;
assert (Q.root ~nth:2 (Q.make_int 4 9) = Q.make_int 2 3);;
assert (Q.root ~nth:3 (Q.make_int 8 27) = Q.make_int 2 3);;

(* mpq_sqrt is missing *)
assert (Q.sqrt (Q.make_int 4 9) = Q.make_int 2 3);;

(* mpf_add_si is missing *)
assert (F.add_int (F.of_int 4) 1 = F.of_int 5);;
assert (F.add_int (F.of_int 4) (-1) = F.of_int 3);;

(* mpf_sub_si is missing *)
assert (F.sub_int (F.of_int 4) 1 = F.of_int 3);;
assert (F.sub_int (F.of_int 4) (-1) = F.of_int 5);;

(* mpf_mul_si is missing *)
assert (F.mul_int (F.of_int 4) 2 = F.of_int 8);;
assert (F.mul_int (F.of_int 4) (-2) = F.of_int (-8));;

(* mpf_fma is missing *)
assert (F.fma (F.of_int 2) (F.of_int 3) (F.of_int 5) = F.of_int 11);;

(* mpf_pow_si is missing *)
assert (F.pow_int ~base:(F.of_int 2) ~exponent:3 = F.of_int 8);;
assert (
	F.pow_int ~base:(F.of_int 2) ~exponent:(-3) = F.of_float (1.0 /. 8.0)
);;
assert (F.pow_int ~base:F.zero ~exponent:0 = F.one);;
assert (F.pow_int ~base:(F.of_int (-2)) ~exponent:2 = F.of_int 4);;
assert (F.pow_int ~base:(F.of_int (-2)) ~exponent:3 = F.of_int (-8));;
assert (
	F.pow_int ~base:(F.of_int (-2)) ~exponent:(-2) = F.of_float (1.0 /. 4.0)
);;
assert (
	F.pow_int ~base:(F.of_int (-2)) ~exponent:(-3) = F.of_float (-1.0 /. 8.0)
);;

(* mpf_si_pow_si is missing *)
assert (F.int_pow_int ~base:2 ~exponent:3 = F.of_int 8);;
assert (F.int_pow_int ~base:2 ~exponent:(-3) = F.of_float (1.0 /. 8.0));;
assert (F.int_pow_int ~base:3 ~exponent:3 = F.of_int 27);;
assert (F.int_pow_int ~base:3 ~exponent:(-3) = F.div F.one (F.of_int 27));;
assert (F.int_pow_int ~base:0 ~exponent:0 = F.one);;
assert (F.int_pow_int ~base:(-2) ~exponent:2 = F.of_int 4);;
assert (F.int_pow_int ~base:(-2) ~exponent:3 = F.of_int (-8));;
assert (F.int_pow_int ~base:(-2) ~exponent:(-2) = F.of_float (1.0 /. 4.0));;
assert (F.int_pow_int ~base:(-2) ~exponent:(-3) = F.of_float (-1.0 /. 8.0));;
assert (F.int_pow_int ~base:(-3) ~exponent:2 = F.of_int 9);;
assert (F.int_pow_int ~base:(-3) ~exponent:3 = F.of_int (-27));;
assert (F.int_pow_int ~base:(-3) ~exponent:(-2) = F.div F.one (F.of_int 9));;
assert (
	F.int_pow_int ~base:(-3) ~exponent:(-3) = F.div F.minus_one (F.of_int 27)
);;

(* mpf_root is missing *)
assert (F.root ~nth:1 (F.of_int 2) = F.of_int 2);;
assert (F.root ~nth:2 (F.of_int 4) = F.of_int 2);;
assert (F.root ~nth:3 (F.of_int 8) = F.of_int 2);;

(* mpf_frexp is missing *)
assert (F.frexp F.one = (F.of_float 0.5, 1));;
assert (F.frexp (F.of_float 0.25) = (F.of_float 0.5, (-1)));;
assert (F.frexp F.minus_one = (F.of_float (-0.5), 1));;
assert (F.frexp (F.of_float (-0.25)) = (F.of_float (-0.5), (-1)));;

(* mpf_ldexp is missing *)
assert (F.ldexp (F.of_float 1.5) (-2) = F.of_float 0.375);;
assert (F.ldexp (F.of_float 1.5) 2 = F.of_float 6.);;
assert (F.ldexp (F.of_float (-1.5)) (-2) = F.of_float (-0.375));;
assert (F.ldexp (F.of_float (-1.5)) 2 = F.of_float (-6.));;

(* mpf_log is missing *)
let prec = 10 in
assert (
	F.nearly_equal prec (F.log (F.of_float 10.0)) (F.of_float 2.302585093)
);;
assert (F.based_log ~base:2 (F.of_int 2) = F.one);;
assert (F.based_log ~base:4 (F.of_int 4) = F.one);;

(* mpfr_si_pow_si is missing *)
assert (FR.int_pow_int ~base:2 ~exponent:3 = FR.of_int 8);;
assert (FR.int_pow_int ~base:2 ~exponent:(-3) = FR.of_float (1.0 /. 8.0));;
assert (FR.int_pow_int ~base:3 ~exponent:3 = FR.of_int 27);;
assert (FR.int_pow_int ~base:3 ~exponent:(-3) = FR.div FR.one (FR.of_int 27));;
assert (FR.int_pow_int ~base:0 ~exponent:0 = FR.one);;
assert (FR.int_pow_int ~base:(-2) ~exponent:2 = FR.of_int 4);;
assert (FR.int_pow_int ~base:(-2) ~exponent:3 = FR.of_int (-8));;
assert (FR.int_pow_int ~base:(-2) ~exponent:(-2) = FR.of_float (1.0 /. 4.0));;
assert (FR.int_pow_int ~base:(-2) ~exponent:(-3) = FR.of_float (-1.0 /. 8.0));;
assert (FR.int_pow_int ~base:(-3) ~exponent:2 = FR.of_int 9);;
assert (FR.int_pow_int ~base:(-3) ~exponent:3 = FR.of_int (-27));;
assert (
	FR.int_pow_int ~base:(-3) ~exponent:(-2) = FR.div FR.one (FR.of_int 9)
);;
assert (
	FR.int_pow_int ~base:(-3) ~exponent:(-3) = FR.div FR.minus_one (FR.of_int 27)
);;

(* mpfr_ldexp is missing *)
assert (FR.ldexp (FR.of_float 1.5) (-2) = FR.of_float 0.375);;
assert (FR.ldexp (FR.of_float 1.5) 2 = FR.of_float 6.);;
assert (FR.ldexp (FR.of_float (-1.5)) (-2) = FR.of_float (-0.375));;
assert (FR.ldexp (FR.of_float (-1.5)) 2 = FR.of_float (-6.));;

(* mpc_sub_si is missing *)
assert (C.sub_int (C.of_int 4) 1 = C.of_int 3);;
assert (C.sub_int (C.of_int 4) (-1) = C.of_int 5);;

(* mpc_si_pow_si is missing *)
assert (C.int_pow_int ~base:2 ~exponent:3 = C.of_int 8);;
assert (C.int_pow_int ~base:2 ~exponent:(-3) = C.of_float (1.0 /. 8.0));;
assert (C.int_pow_int ~base:3 ~exponent:3 = C.of_int 27);;
assert (C.int_pow_int ~base:3 ~exponent:(-3) = C.div C.one (C.of_int 27));;
assert (C.int_pow_int ~base:0 ~exponent:0 = C.one);;
assert (C.int_pow_int ~base:(-2) ~exponent:2 = C.of_int 4);;
assert (C.int_pow_int ~base:(-2) ~exponent:3 = C.of_int (-8));;
assert (C.int_pow_int ~base:(-2) ~exponent:(-2) = C.of_float (1.0 /. 4.0));;
assert (C.int_pow_int ~base:(-2) ~exponent:(-3) = C.of_float (-1.0 /. 8.0));;
assert (C.int_pow_int ~base:(-3) ~exponent:2 = C.of_int 9);;
assert (C.int_pow_int ~base:(-3) ~exponent:3 = C.of_int (-27));;
assert (C.int_pow_int ~base:(-3) ~exponent:(-2) = C.div C.one (C.of_int 9));;
assert (
	C.int_pow_int ~base:(-3) ~exponent:(-3) = C.div C.minus_one (C.of_int 27)
);;

(* mpc_root is missing *)
assert (C.root ~nth:1 (C.of_int 2) = C.of_int 2);;
assert (C.root ~nth:2 (C.of_int 4) = C.of_int 2);;
assert (C.root ~nth:3 (C.of_int 8) = C.of_int 2);;

(* mpc_polar is missimg *)
assert (C.polar (FR.of_int 2) FR.zero = C.make_int 2 0);;
let d = 0x1.p-50 in
assert (
	let r = C.polar (FR.of_int 2) (FR.div FR.pi (FR.of_int 2)) in
	FR.abs (C.real r) < FR.of_float d
		&& FR.abs (FR.sub_int (C.imag r) 2) < FR.of_float d
);
assert (
	let r = C.polar (FR.of_int 2) FR.pi in
	FR.abs (FR.sub_int (C.real r) (-2)) < FR.of_float d
		&& FR.abs (C.imag r) < FR.of_float d
);
assert (
	let r = C.polar (FR.of_int 2) (FR.mul FR.pi (FR.of_float 1.5)) in
	FR.abs (C.real r) < FR.of_float d
		&& FR.abs (FR.sub_int (C.imag r) (-2)) < FR.of_float d
);
assert (
	let r = C.polar (FR.of_int 2) (FR.mul FR.pi (FR.of_int 2)) in
	FR.abs (FR.sub_int (C.real r) 2) < FR.of_float d
		&& FR.abs (C.imag r) < FR.of_float d
);;

prerr_endline "ok";;
