type z
type byte_order = [`B | `L | `N] (* Big, Little and Native endianness *)

external z_of_based_string: base:int -> string -> z = "mlgmp_z_of_based_string"
val z_of_string: string -> z
external based_string_of_z: base:int -> z -> string = "mlgmp_based_string_of_z"
val string_of_z: z -> string
external z_of_int: int -> z = "mlgmp_z_of_int"
external int_of_z: z -> int = "mlgmp_int_of_z"
external z_of_int32: int32 -> z = "mlgmp_z_of_int32"
external int32_of_z: z -> int32 = "mlgmp_int32_of_z"
external z_of_int64: int64 -> z = "mlgmp_z_of_int64"
external int64_of_z: z -> int64 = "mlgmp_int64_of_z"
external z_of_nativeint: nativeint -> z = "mlgmp_z_of_nativeint"
external nativeint_of_z: z -> nativeint = "mlgmp_nativeint_of_z"
external z_of_truncated_float: float -> z = "mlgmp_z_of_truncated_float"
external float_of_z: z -> float = "mlgmp_float_of_z"

module Z: sig
	type t = z
	val zero: t
	val one: t
	val minus_one: t
	external compare: t -> t -> int = "mlgmp_z_compare"
	external compare_int: t -> int -> int = "mlgmp_z_compare_int"
	external neg: t -> t = "mlgmp_z_neg"
	external abs: t -> t = "mlgmp_z_abs"
	external add: t -> t -> t = "mlgmp_z_add"
	external add_int: t -> int -> t = "mlgmp_z_add_int"
	external sub: t -> t -> t = "mlgmp_z_sub"
	external sub_int: t -> int -> t = "mlgmp_z_sub_int"
	external mul: t -> t -> t = "mlgmp_z_mul"
	external mul_int: t -> int -> t = "mlgmp_z_mul_int"
	external div: t -> t -> t = "mlgmp_z_div" (* div x y = fst (tdiv x y) *)
	external pow_int: base:t -> exponent:int -> t = "mlgmp_z_pow_int"
	external int_pow_int: base:int -> exponent:int -> t = "mlgmp_z_int_pow_int"
	external scale: t -> base:int -> exponent:int -> t = "mlgmp_z_scale"
	external root: nth:int -> t -> t = "mlgmp_z_root"
	external sqrt: t -> t = "mlgmp_z_sqrt"
		(* sqrt x = fst (tsqrt x) = root ~nth:2 x *)
	(* integer operations *)
	external rem: t -> t -> t = "mlgmp_z_rem" (* rem x y = snd (tdiv x y) *)
	external modulo: t -> t -> t = "mlgmp_z_modulo"
	external pow_mod: base:t -> exponent:t -> t -> t = "mlgmp_z_pow_mod"
	external tdiv: t -> t -> t * t = "mlgmp_z_tdiv"
	external tdiv_int: t -> int -> t * int = "mlgmp_z_tdiv_int"
	external cdiv: t -> t -> t * t = "mlgmp_z_cdiv"
	external cdiv_int: t -> int -> t * int = "mlgmp_z_cdiv_int"
	external fdiv: t -> t -> t * t = "mlgmp_z_fdiv"
	external fdiv_int: t -> int -> t * int = "mlgmp_z_fdiv_int"
	external tsqrt: t -> t * t = "mlgmp_z_tsqrt"
	external is_perfect_power: t -> bool = "mlgmp_z_is_perfect_power"
	external is_perfect_square: t -> bool = "mlgmp_z_is_perfect_square"
	(* number theoretic functions *)
	external is_probably_prime: t -> int -> int = "mlgmp_z_is_probably_prime"
	external next_prime: t -> t = "mlgmp_z_next_prime"
	external gcd: t -> t -> t = "mlgmp_z_gcd"
	external gcdext: t -> t -> t * t * t = "mlgmp_z_gcdext"
	external lcm: t -> t -> t = "mlgmp_z_lcm"
	external invert: t -> t -> t option = "mlgmp_z_invert"
	external jacobi: t -> t -> int = "mlgmp_z_jacobi"
	val legendre: t -> t -> int
	val kronecker: t -> t -> int
	external remove: t -> t -> t * int = "mlgmp_z_remove"
	external fac_int: int -> t = "mlgmp_z_fac_int"
	external dfac_int: int -> t = "mlgmp_z_dfac_int"
		(* dfac_int x = int_mfac_int ~step:2 x *)
	external int_mfac_int: step:int -> int -> t = "mlgmp_z_int_mfac_int"
	external primorial_int: int -> t = "mlgmp_z_primorial_int"
	external bin_int: t -> int -> t = "mlgmp_z_bin_int"
	external fib_int: int -> t = "mlgmp_z_fib_int"
	external lucnum_int: int -> t = "mlgmp_z_lucnum_int"
	(* bit operations *)
	external logand: t -> t -> t = "mlgmp_z_logand"
	external logand_int: t -> int -> t = "mlgmp_z_logand_int"
	external logor: t -> t -> t = "mlgmp_z_logor"
	external logor_int: t -> int -> t = "mlgmp_z_logor_int"
	external logxor: t -> t -> t = "mlgmp_z_logxor"
	external logxor_int: t -> int -> t = "mlgmp_z_logxor_int"
	external lognot: t -> t = "mlgmp_z_lognot"
	external shift_left: t -> int -> t = "mlgmp_z_shift_left"
	external shift_right: t -> int -> t = "mlgmp_z_shift_right"
	external population_count: t -> int = "mlgmp_z_population_count"
	external hamming_distance: t -> t -> int = "mlgmp_z_hamming_distance"
	external scan0: t -> int -> int = "mlgmp_z_scan0"
	external scan1: t -> int -> int = "mlgmp_z_scan1"
	external set_bit: t -> int -> t = "mlgmp_z_set_bit"
	external clear_bit: t -> int -> t = "mlgmp_z_clear_bit"
	external test_bit: t -> int -> int = "mlgmp_z_test_bit"
	(* import/export *)
	external export_length: t -> int = "mlgmp_z_export_length"
	external export: order:byte_order -> t -> bytes -> int -> int -> unit =
		"mlgmp_z_export"
	external import: order:byte_order -> signed:bool -> bytes -> int -> int -> t =
		"mlgmp_z_import"
	(* conversions *)
	external of_based_string: base:int -> string -> t = "mlgmp_z_of_based_string"
	val of_string: string -> t
	external to_based_string: base:int -> t -> string = "mlgmp_based_string_of_z"
	val to_string: t -> string
	external of_int: int -> t = "mlgmp_z_of_int"
	external to_int: t -> int = "mlgmp_int_of_z"
	external of_int32: int32 -> t = "mlgmp_z_of_int32"
	external to_int32: int32 -> t = "mlgmp_int32_of_z"
	external of_int64: int64 -> t = "mlgmp_z_of_int64"
	external to_int64: t -> int64 = "mlgmp_int64_of_z"
	external of_nativeint: nativeint -> t = "mlgmp_z_of_nativeint"
	external to_nativeint: nativeint -> t = "mlgmp_nativeint_of_z"
	external to_float: t -> float = "mlgmp_float_of_z"
end

type q

external q_of_based_string: base:int -> string -> q = "mlgmp_q_of_based_string"
val q_of_string: string -> q
external based_string_of_q: base:int -> q -> string = "mlgmp_based_string_of_q"
val string_of_q: q -> string
external q_of_int: int -> q = "mlgmp_q_of_int"
external q_of_float: float -> q = "mlgmp_q_of_float"
external float_of_q: q -> float = "mlgmp_float_of_q"
external q_of_z: z -> q = "mlgmp_q_of_z"
external z_of_truncated_q: q -> z = "mlgmp_z_of_truncated_q"

module Q: sig
	type t = q
	val zero: t
	val one: t
	val minus_one: t
	external compare: t -> t -> int = "mlgmp_q_compare"
	external compare_int: t -> int -> int = "mlgmp_q_compare_int"
	external neg: t -> t = "mlgmp_q_neg"
	external abs: t -> t = "mlgmp_q_abs"
	external add: t -> t -> t = "mlgmp_q_add"
	external add_int: t -> int -> t = "mlgmp_q_add_int"
	external sub: t -> t -> t = "mlgmp_q_sub"
	external sub_int: t -> int -> t = "mlgmp_q_sub_int"
	external mul: t -> t -> t = "mlgmp_q_mul"
	external mul_int: t -> int -> t = "mlgmp_q_mul_int"
	external div: t -> t -> t = "mlgmp_q_div"
	external pow_int: base:t -> exponent:int -> t = "mlgmp_q_pow_int"
	external int_pow_int: base:int -> exponent:int -> t = "mlgmp_q_int_pow_int"
	external scale: t -> base:int -> exponent:int -> t = "mlgmp_q_scale"
	external root: nth:int -> t -> t = "mlgmp_q_root"
	external sqrt: t -> t = "mlgmp_q_sqrt"
	(* partial access *)
	external num: t -> z = "mlgmp_q_num"
	external den: t -> z = "mlgmp_q_den"
	(* conversions *)
	external of_based_string: base:int -> string -> t = "mlgmp_q_of_based_string"
	val of_string: string -> t
	external to_based_string: base:int -> t -> string = "mlgmp_based_string_of_q"
	val to_string: t -> string
	external of_int: int -> t = "mlgmp_q_of_int"
	external of_float: float -> t = "mlgmp_q_of_float"
	external to_float: t -> float = "mlgmp_float_of_q"
	external of_z: z -> t = "mlgmp_q_of_z"
	external make_int: int -> int -> t = "mlgmp_q_make_int"
	external make_z: z -> z -> t = "mlgmp_q_make_z"
end

type f

external f_of_based_string: prec:int -> base:int -> string -> f =
	"mlgmp_f_of_based_string"
val f_of_string: prec:int -> string -> f
external based_string_of_f: base:int -> f -> string = "mlgmp_based_string_of_f"
val string_of_f: f -> string
external f_get_str: base:int -> int -> f -> string * int = "mlgmp_f_get_str"
external f_of_int: prec:int -> int -> f = "mlgmp_f_of_int"
external f_of_float: prec:int -> float -> f = "mlgmp_f_of_float"
external float_of_f: f -> float = "mlgmp_float_of_f"
external f_of_z: prec:int -> z -> f = "mlgmp_f_of_z"
external z_of_truncated_f: f -> z = "mlgmp_z_of_truncated_f"
external f_of_f: prec:int -> f -> f = "mlgmp_f_of_f"

module F: sig
	type t = f
	val zero: prec:int -> t
	val one: prec:int -> t
	val minus_one: prec:int -> t
	external compare: t -> t -> int = "mlgmp_f_compare"
	external compare_int: t -> int -> int = "mlgmp_f_compare_int"
	external neg: prec:int -> t -> t = "mlgmp_f_neg"
	external abs: prec:int -> t -> t = "mlgmp_f_abs"
	external add: prec:int -> t -> t -> t = "mlgmp_f_add"
	external add_int: prec:int -> t -> int -> t = "mlgmp_f_add_int"
	external sub: prec:int -> t -> t -> t = "mlgmp_f_sub"
	external sub_int: prec:int -> t -> int -> t = "mlgmp_f_sub_int"
	external mul: prec:int -> t -> t -> t = "mlgmp_f_mul"
	external mul_int: prec:int -> t -> int -> t = "mlgmp_f_mul_int"
	external div: prec:int -> t -> t -> t = "mlgmp_f_div"
	external pow_int: prec:int -> base:t -> exponent:int -> t = "mlgmp_f_pow_int"
	external int_pow_int: prec:int -> base:int -> exponent:int -> t =
		"mlgmp_f_int_pow_int"
	external scale: prec:int -> t -> base:int -> exponent:int -> t =
		"mlgmp_f_scale"
	external root: prec:int -> nth:int -> t -> t = "mlgmp_f_root"
	external sqrt: prec:int -> t -> t = "mlgmp_f_sqrt"
	(* floating-point operations *)
	external nearly_equal: int -> t -> t -> bool = "mlgmp_f_nearly_equal"
	external frexp: prec:int -> t -> t * int = "mlgmp_f_frexp"
	external trunc: prec:int -> t -> t = "mlgmp_f_trunc"
	external ceil: prec:int -> t -> t = "mlgmp_f_ceil"
	external floor: prec:int -> t -> t = "mlgmp_f_floor"
	(* elementary functions *)
	external log: prec:int -> t -> t = "mlgmp_f_log"
	external based_log: prec:int -> base:int -> t -> t = "mlgmp_f_based_log"
	(* conversions *)
	external of_based_string: prec:int -> base:int -> string -> t =
		"mlgmp_f_of_based_string"
	val of_string: prec:int -> string -> t
	external to_based_string: base:int -> t -> string = "mlgmp_based_string_of_f"
	val to_string: t -> string
	external of_int: prec:int -> int -> t = "mlgmp_f_of_int"
	external of_float: prec:int -> float -> t = "mlgmp_f_of_float"
	external to_float: t -> float = "mlgmp_float_of_f"
	external of_z: prec:int -> z -> t = "mlgmp_f_of_z"
	(* make the signature like Float *)
	module type Param = sig
		val prec: int
	end
	module Make (_: Param): sig
		type t = f
		val zero: t
		val one: t
		val minus_one: t
		external compare: t -> t -> int = "mlgmp_f_compare"
		external compare_int: t -> int -> int = "mlgmp_f_compare_int"
		val neg: t -> t
		val abs: t -> t
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
		external nearly_equal: int -> t -> t -> bool = "mlgmp_f_nearly_equal"
		val frexp: t -> t * int
		val trunc: t -> t
		val ceil: t -> t
		val floor: t -> t
		(* elementary functions *)
		val log: t -> t
		val based_log: base:int -> t -> t
		(* conversions *)
		val of_based_string: base:int -> string -> t
		val of_string: string -> t
		external to_based_string: base:int -> t -> string = "mlgmp_based_string_of_f"
		val to_string: t -> string
		val of_int: int -> t
		val of_float: float -> t
		external to_float: t -> float = "mlgmp_float_of_f"
		val of_z: z -> t
	end
	external default_prec: unit -> int = "mlgmp_f_get_default_prec"
	val default: unit -> (module Param)
end

module Random: sig
	type t
	external create: unit -> t = "mlgmp_random_create"
	external create_lc_2exp: z -> int -> int -> t = "mlgmp_random_create_lc_2exp"
	external create_lc_2exp_size: int -> t = "mlgmp_random_create_lc_2exp_size"
	external create_mt: unit -> t = "mlgmp_random_create_mt"
	external seed_int: t -> int -> unit = "mlgmp_random_seed_int"
	external seed_z: t -> z -> unit = "mlgmp_random_seed_z"
	val make_int: int -> t (* create and seed_int *)
	val make_self_init: unit -> t (* make_int with a seed of O'Caml runtime *)
	val make_z: z -> t (* create and seed_z *)
	val make: int array -> t
	external copy: t -> t = "mlgmp_random_copy"
	(* generating *)
	external int_bits: t -> int -> int = "mlgmp_random_int_bits"
	val bits: t -> int
	external int: t -> int -> int = "mlgmp_random_int"
	external int32: t -> int32 -> int32 = "mlgmp_random_int32"
	external int64: t -> int64 -> int64 = "mlgmp_random_int64"
	external nativeint: t -> nativeint -> nativeint = "mlgmp_random_nativeint"
	val bool: t -> bool
	external float_bits: t -> int -> float = "mlgmp_random_float_bits"
	val float: t -> float -> float
	external z: t -> z -> z = "mlgmp_random_z"
	external f_bits: t -> int -> f = "mlgmp_random_f_bits"
	external f: t -> prec:int -> f -> f = "mlgmp_random_f"
end
