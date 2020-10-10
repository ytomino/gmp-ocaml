open Gmp
open Mpfr

type c
type rounding_mode = [`N | `Z | `U | `D] * [`N | `Z | `U | `D]

external c_of_based_string: prec:int * int -> mode:rounding_mode -> base:int ->
	string -> c =
	"mlmpc_c_of_based_string"
val c_of_string: prec:int * int -> mode:rounding_mode -> string -> c
external based_string_of_c: mode:rounding_mode -> base:int -> c -> string =
	"mlmpc_based_string_of_c"
val string_of_c: mode:rounding_mode -> c -> string
external c_of_int: prec:int * int -> mode:rounding_mode -> int -> c =
	"mlmpc_c_of_int"
external c_of_float: prec:int * int -> mode:rounding_mode -> float -> c =
	"mlmpc_c_of_float"
external c_of_z: prec:int * int -> mode:rounding_mode -> z -> c =
	"mlmpc_c_of_z"
external c_of_q: prec:int * int -> mode:rounding_mode -> q -> c =
	"mlmpc_c_of_q"
external c_of_f: prec:int * int -> mode:rounding_mode -> f -> c =
	"mlmpc_c_of_f"
external c_of_fr: prec:int * int -> mode:rounding_mode -> fr -> c =
	"mlmpc_c_of_fr"

val default_prec: unit -> int * int
val default_rounding_mode: unit -> rounding_mode

module C (Prec: sig val prec: int * int end): sig
	type t = c
	val zero: t
	val one: t
	val minus_one: t
	val i: t
	external compare: t -> t -> int = "mlmpc_c_compare"
	external compare_int: t -> int -> int = "mlmpc_c_compare_int"
	val neg: mode:rounding_mode -> t -> t
	val abs: mode:Mpfr.rounding_mode -> t -> fr
	val add: mode:rounding_mode -> t -> t -> t
	val add_int: mode:rounding_mode -> t -> int -> t
	val sub: mode:rounding_mode -> t -> t -> t
	val sub_int: mode:rounding_mode -> t -> int -> t
	val mul: mode:rounding_mode -> t -> t -> t
	val mul_int: mode:rounding_mode -> t -> int -> t
	val div: mode:rounding_mode -> t -> t -> t
	val pow_int: mode:rounding_mode -> base:t -> exponent:int -> t
	val int_pow_int: mode:rounding_mode -> base:int -> exponent:int -> t
	val scale: mode:rounding_mode -> t -> base:int -> exponent:int -> t
	val root: mode:rounding_mode -> nth:int -> t -> t
	val sqrt: mode:rounding_mode -> t -> t
	(* floating-point operations *)
	val log: mode:rounding_mode -> t -> t
	val based_log: mode:rounding_mode -> base: int -> t -> t
	(* complex functions *)
	val conj: mode:rounding_mode -> t -> t
	val norm: mode:Mpfr.rounding_mode -> t -> fr
	val arg: mode:Mpfr.rounding_mode -> t -> fr
	val proj: mode:rounding_mode -> t -> t
	(* partial access *)
	external real: t -> fr = "mlmpc_c_real"
	external imag: t -> fr = "mlmpc_c_imag"
	(* conversions *)
	val of_based_string: mode:rounding_mode -> base:int -> string -> t
	val of_string: mode:rounding_mode -> string -> t
	external to_based_string: mode:rounding_mode -> base:int -> c -> string =
		"mlmpc_based_string_of_c"
	val to_string: mode:rounding_mode -> t -> string
	val of_int: mode:rounding_mode -> int -> t
	val of_float: mode:rounding_mode -> float -> t
	val of_z: mode:rounding_mode -> z -> t
	val of_q: mode:rounding_mode -> q -> t
	val of_f: mode:rounding_mode -> f -> t
	val of_fr: mode:rounding_mode -> fr -> t
	val make_int: mode:rounding_mode -> int -> int -> t
	val make_float: mode:rounding_mode -> float -> float -> t
	val make_z: mode:rounding_mode -> z -> z -> t
	val make_q: mode:rounding_mode -> q -> q -> t
	val make_f: mode:rounding_mode -> f -> f -> t
	val make_fr: mode:rounding_mode -> fr -> fr -> t
	(* make the signature like F *)
	module F (Mode: sig val rounding_mode: rounding_mode end): sig
		type t = c
		val zero: t
		val one: t
		val minus_one: t
		val i: t
		external compare: t -> t -> int = "mlmpc_c_compare"
		external compare_int: t -> int -> int = "mlmpc_c_compare_int"
		val neg: t -> t
		val abs: t -> fr
		val add: t -> t -> t
		val add_int: t -> int -> t
		val sub: t -> t -> t
		val sub_int: t -> int -> t
		val mul: t -> t -> t
		val mul_int: t -> int -> t
		val div: t -> t -> t
		val pow_int: base:t -> exponent:int -> t
		val int_pow_int: base:int -> exponent:int -> t
		val scale: t -> base:int -> exponent:int -> t
		val root: nth:int -> t -> t
		val sqrt: t -> t
		(* floating-point operations *)
		val log: t -> t
		val based_log: base: int -> t -> t
		(* complex functions *)
		val conj: t -> t
		val norm: t -> fr
		val arg: t -> fr
		val proj: t -> t
		(* partial access *)
		external real: t -> fr = "mlmpc_c_real"
		external imag: t -> fr = "mlmpc_c_imag"
		(* conversions *)
		val of_based_string: base:int -> string -> t
		val of_string: string -> t
		val to_based_string: base:int -> t -> string
		val to_string: t -> string
		val of_int: int -> t
		val of_float: float -> t
		val of_z: z -> t
		val of_q: q -> t
		val of_f: f -> t
		val of_fr: fr -> t
		val make_int: int -> int -> t
		val make_float: float -> float -> t
		val make_z: z -> z -> t
		val make_q: q -> q -> t
		val make_f: f -> f -> t
		val make_fr: fr -> fr -> t
	end
end
