open Gmp

external mpfr_compiled_version: unit -> int * int * int =
	"mlmpfr_compiled_version"
external mpfr_compiled_version_string: unit -> string =
	"mlmpfr_compiled_version_string"
external mpfr_get_version_string: unit -> string = "mlmpfr_get_version_string"

type fr
type rounding_mode = [`N | `Z | `U | `D | `A | `F | `NA]

external fr_of_based_string: prec:int -> mode:rounding_mode -> base:int ->
	string -> fr =
	"mlmpfr_fr_of_based_string"
val fr_of_string: prec:int -> mode:rounding_mode -> string -> fr
external based_string_of_fr: mode:rounding_mode -> base:int -> fr -> string =
	"mlmpfr_based_string_of_fr"
val string_of_fr: mode:rounding_mode -> fr -> string
external fr_get_str: mode:rounding_mode -> base:int -> int -> fr ->
	string * int =
	"mlmpfr_fr_get_str"
external fr_of_int: prec:int -> mode:rounding_mode -> int -> fr =
	"mlmpfr_fr_of_int"
external fr_of_float: prec:int -> mode:rounding_mode -> float -> fr =
	"mlmpfr_fr_of_float"
external float_of_fr: mode:rounding_mode -> fr -> float = "mlmpfr_float_of_fr"
external fr_of_z: prec:int -> mode:rounding_mode -> z -> fr = "mlmpfr_fr_of_z"
external z_of_fr: mode:rounding_mode -> fr -> z = "mlmpfr_z_of_fr"
val z_of_truncated_fr: fr -> z
external fr_of_fr: prec:int -> mode:rounding_mode -> fr -> fr =
	"mlmpfr_fr_of_fr"
external bits_of_single: fr -> int32 = "mlmpfr_fr_bits_of_single"
external bits_of_double: fr -> int64 = "mlmpfr_fr_bits_of_double"
external bits_of_extended: fr -> int64 * int = "mlmpfr_fr_bits_of_extended"
external single_of_bits: int32 -> fr = "mlmpfr_fr_single_of_bits"
external double_of_bits: int64 -> fr = "mlmpfr_fr_double_of_bits"
external extended_of_bits: int64 * int -> fr = "mlmpfr_fr_extended_of_bits"

module FR: sig
	type t = fr
	val zero: prec:int -> t
	val one: prec:int -> t
	val minus_one: prec:int -> t
	external compare: t -> t -> int = "mlmpfr_fr_compare"
	external compare_int: t -> int -> int = "mlmpfr_fr_compare_int"
	external neg: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_neg"
	external abs: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_abs"
	external add: prec:int -> mode:rounding_mode -> t -> t -> t = "mlmpfr_fr_add"
	external add_int: prec:int -> mode:rounding_mode -> t -> int -> t =
		"mlmpfr_fr_add_int"
	external sub: prec:int -> mode:rounding_mode -> t -> t -> t = "mlmpfr_fr_sub"
	external sub_int: prec:int -> mode:rounding_mode -> t -> int -> t =
		"mlmpfr_fr_sub_int"
	external mul: prec:int -> mode:rounding_mode -> t -> t -> t = "mlmpfr_fr_mul"
	external mul_int: prec:int -> mode:rounding_mode -> t -> int -> t =
		"mlmpfr_fr_mul_int"
	external div: prec:int -> mode:rounding_mode -> t -> t -> t = "mlmpfr_fr_div"
	external fma: prec:int -> mode:rounding_mode -> t -> t -> t -> t =
		"mlmpfr_fr_fma"
	external pow_int: prec:int -> mode:rounding_mode -> base:t -> exponent:int ->
		t =
		"mlmpfr_fr_pow_int"
	external int_pow_int: prec:int -> mode:rounding_mode -> base:int ->
		exponent:int -> t =
		"mlmpfr_fr_int_pow_int"
	external scale: prec:int -> mode:rounding_mode -> t -> base:int ->
		exponent:int -> t =
		"mlmpfr_fr_scale"
	external root: prec:int -> mode:rounding_mode -> nth:int -> t -> t =
		"mlmpfr_fr_root"
	external sqrt: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_sqrt"
	(* floating-point operations *)
	external nearly_equal: int -> t -> t -> bool = "mlmpfr_fr_nearly_equal"
	external frexp: prec:int -> mode:rounding_mode -> t -> t * int =
		"mlmpfr_fr_frexp"
	external trunc: prec:int -> t -> t = "mlmpfr_fr_trunc"
	external ceil: prec:int -> t -> t = "mlmpfr_fr_ceil"
	external floor: prec:int -> t -> t = "mlmpfr_fr_floor"
	external is_infinite: t -> bool = "mlmpfr_fr_is_infinite"
	(* elementary functions *)
	external pi: prec:int -> mode:rounding_mode -> t = "mlmpfr_fr_pi"
	external log: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_log"
	external based_log: prec:int -> mode:rounding_mode -> base:int -> t -> t =
		"mlmpfr_fr_based_log"
	external pow: prec:int -> mode:rounding_mode -> t -> t -> t = "mlmpfr_fr_pow"
	external exp: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_exp"
	external sin: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_sin"
	external cos: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_cos"
	external tan: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_tan"
	external atan: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_atan"
	external atan2: prec:int -> mode:rounding_mode -> t -> t -> t =
		"mlmpfr_fr_atan2"
	external acosh: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_acosh"
	(* conversions *)
	external of_based_string: prec:int -> mode:rounding_mode -> base:int ->
		string -> t =
		"mlmpfr_fr_of_based_string"
	val of_string: prec:int -> mode:rounding_mode -> string -> t
	external to_based_string: mode:rounding_mode -> base:int -> t -> string =
		"mlmpfr_based_string_of_fr"
	val to_string: mode:rounding_mode -> t -> string
	external of_int: prec:int -> mode:rounding_mode -> int -> t =
		"mlmpfr_fr_of_int"
	external of_float: prec:int -> mode:rounding_mode -> float -> t =
		"mlmpfr_fr_of_float"
	external to_float: mode:rounding_mode -> t -> float = "mlmpfr_float_of_fr"
	external of_z: prec:int -> mode:rounding_mode -> z -> t = "mlmpfr_fr_of_z"
	external to_z: mode:rounding_mode -> t -> z = "mlmpfr_z_of_fr"
	(* make the signature like Float *)
	module type Param = sig
		val prec: int
		val mode: rounding_mode
	end
	module Make (_: Param): sig
		type t = fr
		val zero: t
		val one: t
		val minus_one: t
		external compare: t -> t -> int = "mlmpfr_fr_compare"
		external compare_int: t -> int -> int = "mlmpfr_fr_compare_int"
		val neg: t -> t
		val abs: t -> t
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
		(* floating-point operations *)
		external nearly_equal: int -> t -> t -> bool = "mlmpfr_fr_nearly_equal"
		val frexp: t -> t * int
		val trunc: t -> t
		val ceil: t -> t
		val floor: t -> t
		external is_infinite: t -> bool = "mlmpfr_fr_is_infinite"
		(* elementary functions *)
		val pi: t
		val log: t -> t
		val based_log: base:int -> t -> t
		val pow: t -> t -> t
		val exp: t -> t
		val sin: t -> t
		val cos: t -> t
		val tan: t -> t
		val atan: t -> t
		val atan2: t -> t -> t
		val acosh: t -> t
		(* conversions *)
		val of_based_string: base:int -> string -> t
		val of_string: string -> t
		val to_based_string: base:int -> t -> string
		val to_string: t -> string
		val of_int: int -> t
		val of_float: float -> t
		val to_float: t -> float
		val of_z: z -> t
		val to_z: t -> z
	end
	external default_prec: unit -> int = "mlmpfr_fr_get_default_prec"
	external default_rounding_mode: unit -> rounding_mode =
		"mlmpfr_fr_get_default_rounding_mode"
	val default: unit -> (module Param)
end
