open Gmp
open Mpfr

external mpc_compiled_version: unit -> int * int * int =
	"mlmpc_compiled_version"
external mpc_compiled_version_string: unit -> string =
	"mlmpc_compiled_version_string"
external mpc_get_version_string: unit -> string = "mlmpc_get_version_string"

type c
type rounding_mode = [`N | `Z | `U | `D | `A] * [`N | `Z | `U | `D | `A]

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

module C: sig
	type t = c
	val zero: prec:int * int -> t
	val one: prec:int * int -> t
	val minus_one: prec:int * int -> t
	val i: prec:int * int -> t
	external compare: t -> t -> int = "mlmpc_c_compare"
	external compare_int: t -> int -> int = "mlmpc_c_compare_int"
	external neg: prec:int * int -> mode:rounding_mode -> t -> t = "mlmpc_c_neg"
	external abs: prec:int -> mode:Mpfr.rounding_mode -> t -> fr = "mlmpc_c_abs"
	external add: prec:int * int -> mode:rounding_mode -> t -> t -> t =
		"mlmpc_c_add"
	external add_int: prec:int * int -> mode:rounding_mode -> t -> int -> t =
		"mlmpc_c_add_int"
	external sub: prec:int * int -> mode:rounding_mode -> t -> t -> t =
		"mlmpc_c_sub"
	external sub_int: prec:int * int -> mode:rounding_mode -> t -> int -> t =
		"mlmpc_c_sub_int"
	external mul: prec:int * int -> mode:rounding_mode -> t -> t -> t =
		"mlmpc_c_mul"
	external mul_int: prec:int * int -> mode:rounding_mode -> t -> int -> t =
		"mlmpc_c_mul_int"
	external div: prec:int * int -> mode:rounding_mode -> t -> t -> t =
		"mlmpc_c_div"
	external fma: prec:int * int -> mode:rounding_mode -> t -> t -> t -> t =
		"mlmpc_c_fma"
	external pow_int: prec:int * int -> mode:rounding_mode -> base:t ->
		exponent:int -> t =
		"mlmpc_c_pow_int"
	external int_pow_int: prec:int * int -> mode:rounding_mode -> base:int ->
		exponent:int -> t =
		"mlmpc_c_int_pow_int"
	external scale: prec:int * int -> mode:rounding_mode -> t -> base:int ->
		exponent:int -> t =
		"mlmpc_c_scale"
	external root: prec:int * int -> mode:rounding_mode -> nth:int -> t -> t =
		"mlmpc_c_root"
	external sqrt: prec:int * int -> mode:rounding_mode -> t -> t = "mlmpc_c_sqrt"
	(* elementary functions *)
	external log: prec:int * int -> mode:rounding_mode -> t -> t = "mlmpc_c_log"
	external based_log: prec:int * int -> mode:rounding_mode -> base:int -> t ->
		t =
		"mlmpc_c_based_log"
	external pow: prec:int * int -> mode:rounding_mode -> t -> t -> t =
		"mlmpc_c_pow"
	external exp: prec:int * int -> mode:rounding_mode -> t -> t = "mlmpc_c_exp"
	(* complex functions *)
	external conj: prec:int * int -> mode:rounding_mode -> t -> t = "mlmpc_c_conj"
	external norm2: prec:int -> mode:Mpfr.rounding_mode -> t -> fr =
		"mlmpc_c_norm2"
	external arg: prec:int -> mode:Mpfr.rounding_mode -> t -> fr = "mlmpc_c_arg"
	external polar: prec:int * int -> mode:rounding_mode -> fr -> fr -> t =
		"mlmpc_c_polar"
	external proj: prec:int * int -> mode:rounding_mode -> t -> t = "mlmpc_c_proj"
	(* partial access *)
	external real: t -> fr = "mlmpc_c_real"
	external imag: t -> fr = "mlmpc_c_imag"
	(* conversions *)
	external of_based_string: prec:int * int -> mode:rounding_mode -> base:int ->
		string -> t =
		"mlmpc_c_of_based_string"
	val of_string: prec:int * int -> mode:rounding_mode -> string -> t
	external to_based_string: mode:rounding_mode -> base:int -> t -> string =
		"mlmpc_based_string_of_c"
	val to_string: mode:rounding_mode -> t -> string
	external of_int: prec:int * int -> mode:rounding_mode -> int -> t =
		"mlmpc_c_of_int"
	external of_float: prec:int * int -> mode:rounding_mode -> float -> t =
		"mlmpc_c_of_float"
	external of_z: prec:int * int -> mode:rounding_mode -> z -> t = "mlmpc_c_of_z"
	external of_q: prec:int * int -> mode:rounding_mode -> q -> t = "mlmpc_c_of_q"
	external of_f: prec:int * int -> mode:rounding_mode -> f -> t = "mlmpc_c_of_f"
	external of_fr: prec:int * int -> mode:rounding_mode -> fr -> t =
		"mlmpc_c_of_fr"
	external make_int: prec:int * int -> mode:rounding_mode -> int -> int -> t =
		"mlmpc_c_make_int"
	external make_float: prec:int * int -> mode:rounding_mode -> float -> float ->
		t =
		"mlmpc_c_make_float"
	external make_z: prec:int * int -> mode:rounding_mode -> z -> z -> t =
		"mlmpc_c_make_z"
	external make_q: prec:int * int -> mode:rounding_mode -> q -> q -> t =
		"mlmpc_c_make_q"
	external make_f: prec:int * int -> mode:rounding_mode -> f -> f -> t =
		"mlmpc_c_make_f"
	external make_fr: prec:int * int -> mode:rounding_mode -> fr -> fr -> t =
		"mlmpc_c_make_fr"
	(* make the signature like Float *)
	module type Param = sig
		val prec: int * int
		val mode: rounding_mode
	end
	module Make (_: Param): sig
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
		val fma: t -> t -> t -> t
		val pow_int: base:t -> exponent:int -> t
		val int_pow_int: base:int -> exponent:int -> t
		val scale: t -> base:int -> exponent:int -> t
		val root: nth:int -> t -> t
		val sqrt: t -> t
		(* elementary functions *)
		val log: t -> t
		val based_log: base:int -> t -> t
		val pow: t -> t -> t
		val exp: t -> t
		(* complex functions *)
		val conj: t -> t
		val norm2: t -> fr
		val arg: t -> fr
		val polar: fr -> fr -> t
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
	val default_prec: unit -> int * int
	external default_rounding_mode: unit -> rounding_mode =
		"mlmpc_c_default_rounding_mode"
	val default: unit -> (module Param)
end
