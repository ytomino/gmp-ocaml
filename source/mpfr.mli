open Gmp;;

type fr;;
type rounding_mode = [`N | `Z | `U | `D | `A | `F | `NA];;

external fr_of_based_string: prec:int -> mode:rounding_mode -> base:int -> string -> fr = "mlmpfr_fr_of_based_string";;
val fr_of_string: prec:int -> mode:rounding_mode -> string -> fr;;
external based_string_of_fr: mode:rounding_mode -> base:int -> fr -> string = "mlmpfr_based_string_of_fr";;
val string_of_fr: mode:rounding_mode -> fr -> string;;
external fr_get_str: mode:rounding_mode -> int -> int -> fr -> string * int = "mlmpfr_fr_get_str";;
external fr_of_int: prec:int -> mode:rounding_mode -> int -> fr = "mlmpfr_fr_of_int";;
external fr_of_float: prec:int -> mode:rounding_mode -> float -> fr = "mlmpfr_fr_of_float";;
external float_of_fr: mode:rounding_mode -> fr -> float = "mlmpfr_float_of_fr";;
external fr_of_z: prec:int -> mode:rounding_mode -> z -> fr = "mlmpfr_fr_of_z";;
external z_of_fr: mode:rounding_mode -> fr -> z = "mlmpfr_z_of_fr";;
val z_of_truncated_fr: fr -> z;;
external fr_of_fr: prec:int -> mode:rounding_mode -> fr -> fr = "mlmpfr_fr_of_fr";;
external bits_of_single: fr -> int32 = "mlmpfr_fr_bits_of_single";;
external bits_of_double: fr -> int64 = "mlmpfr_fr_bits_of_double";;
external bits_of_extended: fr -> int64 * int = "mlmpfr_fr_bits_of_extended";;
external single_of_bits: int32 -> fr = "mlmpfr_fr_single_of_bits";;
external double_of_bits: int64 -> fr = "mlmpfr_fr_double_of_bits";;
external extended_of_bits: int64 * int -> fr = "mlmpfr_fr_extended_of_bits";;

external default_prec: unit -> int = "mlmpfr_fr_get_default_prec";;
external default_rounding_mode: unit -> rounding_mode = "mlmpfr_fr_get_default_rounding_mode";;

module FR (Prec: sig val prec: int end): sig
	type t = fr;;
	val zero: t;;
	val one: t;;
	external compare: t -> t -> int = "mlmpfr_fr_compare";;
	external compare_int: t -> int -> int = "mlmpfr_fr_compare_int";;
	external nearly_equal: int -> t -> t -> bool = "mlmpfr_fr_nearly_equal";;
	val neg: mode:rounding_mode -> t -> t;;
	val abs: mode:rounding_mode -> t -> t;;
	val add: mode:rounding_mode -> t -> t -> t;;
	val add_int: mode:rounding_mode -> t -> int -> t;;
	val sub: mode:rounding_mode -> t -> t -> t;;
	val mul: mode:rounding_mode -> t -> t -> t;;
	val div: mode:rounding_mode -> t -> t -> t;;
	val pow_int: mode:rounding_mode -> base:t -> exponent:int -> t;;
	val int_pow_int: mode:rounding_mode -> base:int -> exponent:int -> t;;
	val scale: mode:rounding_mode -> t -> base:int -> exponent:int -> t;;
	val sqrt: mode:rounding_mode -> t -> t;;
	(* floating-point operations *)
	val frexp: mode:rounding_mode -> t -> t * int;;
	val ceil: t -> t;;
	val floor: t -> t;;
	val log: mode:rounding_mode -> t -> t;;
	val based_log: mode:rounding_mode -> base:int -> t -> t;;
	(* elementary functions *)
	val pow: mode:rounding_mode -> t -> t -> t;;
	val exp: mode:rounding_mode -> t -> t;;
	val sin: mode:rounding_mode -> t -> t;;
	val acosh: mode:rounding_mode -> t -> t;;
	(* conversions *)
	val of_based_string: mode:rounding_mode -> base:int -> string -> t;;
	val of_string: mode:rounding_mode -> string -> t;;
	external to_based_string: mode:rounding_mode -> base:int -> fr -> string = "mlmpfr_based_string_of_fr";;
	val to_string: mode:rounding_mode -> t -> string;;
	val of_int: mode:rounding_mode -> int -> t;;
	val of_float: mode:rounding_mode -> float -> t;;
	external to_float: mode:rounding_mode -> fr -> float = "mlmpfr_float_of_fr";;
	val of_z: mode:rounding_mode -> z -> t;;
	external to_z: mode:rounding_mode -> t -> z = "mlmpfr_z_of_fr";;
	(* make the signature like F *)
	module F (Mode: sig val rounding_mode: rounding_mode end): sig
		type t = fr;;
		val zero: t;;
		val one: t;;
		external compare: t -> t -> int = "mlmpfr_fr_compare";;
		external compare_int: t -> int -> int = "mlmpfr_fr_compare_int";;
		external nearly_equal: int -> t -> t -> bool = "mlmpfr_fr_nearly_equal";;
		val neg: t -> t;;
		val abs: t -> t;;
		val add: t -> t -> t;;
		val add_int: t -> int -> t;;
		val sub: t -> t -> t;;
		val mul: t -> t -> t;;
		val div: t -> t -> t;;
		val pow_int: base:t -> exponent:int -> t;;
		val int_pow_int: base:int -> exponent:int -> t;;
		val scale: t -> base:int -> exponent:int -> t;;
		val sqrt: t -> t;;
		(* floating-point operations *)
		val frexp: t -> t * int;;
		val ceil: t -> t;;
		val floor: t -> t;;
		val log: t -> t;;
		val based_log: base:int -> t -> t;;
		(* elementary functions *)
		val pow: t -> t -> t;;
		val exp: t -> t;;
		val sin: t -> t;;
		val acosh: t -> t;;
		(* conversions *)
		val of_based_string: base:int -> string -> t;;
		val of_string: string -> t;;
		val to_based_string: base:int -> t -> string;;
		val to_string: t -> string;;
		val of_int: int -> t;;
		val of_float: float -> t;;
		val to_float: t -> float;;
		val of_z: z -> t;;
		val to_z: t -> z;;
	end;;
end;;
