type z;;

external z_of_based_string: base:int -> string -> z = "mlgmp_z_of_based_string";;
val z_of_string: string -> z;;
external based_string_of_z: base:int -> z -> string = "mlgmp_based_string_of_z";;
val string_of_z: z -> string;;
external z_of_int: int -> z = "mlgmp_z_of_int";;
external int_of_z: z -> int = "mlgmp_int_of_z";;
external z_of_int32: int32 -> z = "mlgmp_z_of_int32";;
external int32_of_z: z -> int32 = "mlgmp_int32_of_z";;
external z_of_nativeint: nativeint -> z = "mlgmp_z_of_nativeint";;
external nativeint_of_z: z -> nativeint = "mlgmp_nativeint_of_z";;
external z_of_int64: int64 -> z = "mlgmp_z_of_int64";;
external int64_of_z: z -> int64 = "mlgmp_int64_of_z";;
external float_of_z: z -> float = "mlgmp_float_of_z";;

module Z: sig
	type t = z;;
	val zero: t;;
	val one: t;;
	external compare: t -> t -> int = "mlgmp_z_compare";;
	external neg: t -> t = "mlgmp_z_neg";;
	external add: t -> t -> t = "mlgmp_z_add";;
	external add_int: t -> int -> t = "mlgmp_z_add_int";;
	external sub: t -> t -> t = "mlgmp_z_sub";;
	external mul: t -> t -> t = "mlgmp_z_mul";;
	external div: t -> t -> t = "mlgmp_z_div";;
	external rem: t -> t -> t = "mlgmp_z_rem";;
	external int_pow_int: base:int -> exponent:int -> t = "mlgmp_z_int_pow_int";;
	external scale: t -> base:int -> exponent:int -> t = "mlgmp_z_scale";;
	(* bit operations *)
	external logand: t -> t -> t = "mlgmp_z_logand";;
	external logor: t -> t -> t = "mlgmp_z_logor";;
	external logxor: t -> t -> t = "mlgmp_z_logxor";;
	external lognot: t -> t = "mlgmp_z_lognot";;
	external shift_left: t -> int -> t = "mlgmp_z_shift_left";;
	external shift_right: t -> int -> t = "mlgmp_z_shift_right";;
	(* conversions *)
	external of_based_string: base:int -> string -> t = "mlgmp_z_of_based_string";;
	val of_string: string -> t;;
	external to_based_string: base:int -> t -> string = "mlgmp_based_string_of_z";;
	val to_string: t -> string;;
	external of_int: int -> t = "mlgmp_z_of_int";;
	external to_int: t -> int = "mlgmp_int_of_z";;
	external of_int32: int32 -> t = "mlgmp_z_of_int32";;
	external to_int32: int32 -> t = "mlgmp_int32_of_z";;
	external of_nativeint: nativeint -> t = "mlgmp_z_of_nativeint";;
	external to_nativeint: nativeint -> t = "mlgmp_nativeint_of_z";;
	external of_int64: int64 -> t = "mlgmp_z_of_int64";;
	external to_int64: t -> int64 = "mlgmp_int64_of_z";;
	external to_float: t -> float = "mlgmp_float_of_z";;
end;;

type q;;

external q_of_based_string: base:int -> string -> q = "mlgmp_q_of_based_string";;
val q_of_string: string -> q;;
external based_string_of_q: base:int -> q -> string = "mlgmp_based_string_of_q";;
val string_of_q: q -> string;;
external q_of_int: int -> q = "mlgmp_q_of_int";;
external q_of_float: float -> q = "mlgmp_q_of_float";;
external float_of_q: q -> float = "mlgmp_float_of_q";;
external q_of_z: z -> q = "mlgmp_q_of_z";;
external z_of_truncated_q: q -> z = "mlgmp_z_of_truncated_q";;

module Q: sig
	type t = q;;
	val zero: t;;
	val one: t;;
	external compare: t -> t -> int = "mlgmp_q_compare";;
	external neg: t -> t = "mlgmp_q_neg";;
	external add: t -> t -> t = "mlgmp_q_add";;
	external add_int: t -> int -> t = "mlgmp_q_add_int";;
	external sub: t -> t -> t = "mlgmp_q_sub";;
	external mul: t -> t -> t = "mlgmp_q_mul";;
	external div: t -> t -> t = "mlgmp_q_div";;
	external int_pow_int: base:int -> exponent:int -> t = "mlgmp_q_int_pow_int";;
	external scale: t -> base:int -> exponent:int -> t = "mlgmp_q_scale";;
	(* partial acccess *)
	external num: t -> z = "mlgmp_q_num";;
	external den: t -> z = "mlgmp_q_den";;
	(* conversions *)
	external of_based_string: base:int -> string -> t = "mlgmp_q_of_based_string";;
	val of_string: string -> t;;
	external to_based_string: base:int -> t -> string = "mlgmp_based_string_of_q";;
	val to_string: t -> string;;
	external of_int: int -> t = "mlgmp_q_of_int";;
	external of_float: float -> t = "mlgmp_q_of_float";;
	external to_float: t -> float = "mlgmp_float_of_q";;
	external of_z: z -> t = "mlgmp_q_of_z";;
end;;

type f;;

external f_of_based_string: prec:int -> base:int -> string -> f = "mlgmp_f_of_based_string";;
val f_of_string: prec:int -> string -> f;;
external based_string_of_f: base:int -> f -> string = "mlgmp_based_string_of_f";;
val string_of_f: f -> string;;
external f_of_int: prec:int -> int -> f = "mlgmp_f_of_int";;
external f_of_float: prec:int -> float -> f = "mlgmp_f_of_float";;
external float_of_f: f -> float = "mlgmp_float_of_f";;
external f_of_z: prec:int -> z -> f = "mlgmp_f_of_z";;
external z_of_truncated_f: f -> z = "mlgmp_z_of_truncated_f";;
external f_of_f: prec:int -> f -> f = "mlgmp_f_of_f";;

external default_prec: unit -> int = "mlgmp_f_get_default_prec";;

module F (Prec: sig val prec: int end): sig
	type t = f;;
	val zero: t;;
	val one: t;;
	external compare: t -> t -> int = "mlgmp_f_compare";;
	val neg: t -> t;;
	val add: t -> t -> t;;
	val add_int: t -> int -> t;;
	val sub: t -> t -> t;;
	val mul: t -> t -> t;;
	val div: t -> t -> t;;
	val int_pow_int: base:int -> exponent:int -> t;;
	val scale: t -> base:int -> exponent:int -> t;;
	(* floating-point operations *)
	val log: t -> t;;
	val based_log: base:int -> t -> t;;
	val frexp: t -> t * int;;
	(* conversions *)
	val of_based_string: base:int -> string -> t;;
	val of_string: string -> t;;
	external to_based_string: base:int -> t -> string = "mlgmp_based_string_of_f";;
	val to_string: t -> string;;
	val of_int: int -> t;;
	val of_float: float -> t;;
	external to_float: t -> float = "mlgmp_float_of_f";;
	val of_z: z -> t;;
end;;

module Random: sig
	type t;;
	val make: int array -> t;;
	val make_self_init: unit -> t;;
	external make_int: int -> t = "mlgmp_random_make_int";;
	external make_z: z -> t = "mlgmp_random_make_z";;
	external copy: t -> t = "mlgmp_random_copy";;
	external bits: t -> int = "mlgmp_random_bits";;
	external f_bits: t -> int -> f = "mlgmp_random_f_bits";;
	external int: t -> int -> int = "mlgmp_random_int";;
	external int32: t -> int32 -> int32 = "mlgmp_random_int32";;
	external nativeint: t -> nativeint -> nativeint = "mlgmp_random_nativeint";;
	external int64: t -> int64 -> int64 = "mlgmp_random_int64";;
	external bool: t -> bool = "mlgmp_random_bool";;
	val float: t -> float -> float;;
	external z: t -> z -> z = "mlgmp_random_z";;
	external f: t -> prec:int -> f -> f = "mlgmp_random_f";;
end;;
