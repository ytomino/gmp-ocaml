external setup: unit -> unit = "mlgmp_setup";;
setup ();;

type z;;

external z_of_based_string: base:int -> string -> z = "mlgmp_z_of_based_string";;
let z_of_string = z_of_based_string ~base:10;;
external based_string_of_z: base:int -> z -> string = "mlgmp_based_string_of_z";;
let string_of_z = based_string_of_z ~base:10;;
external z_of_int: int -> z = "mlgmp_z_of_int";;
external int_of_z: z -> int = "mlgmp_int_of_z";;
external z_of_int32: int32 -> z = "mlgmp_z_of_int32";;
external int32_of_z: z -> int32 = "mlgmp_int32_of_z";;
external z_of_nativeint: nativeint -> z = "mlgmp_z_of_nativeint";;
external nativeint_of_z: z -> nativeint = "mlgmp_nativeint_of_z";;
external z_of_int64: int64 -> z = "mlgmp_z_of_int64";;
external int64_of_z: z -> int64 = "mlgmp_int64_of_z";;
external float_of_z: z -> float = "mlgmp_float_of_z";;

module Z = struct
	type t = z;;
	let zero = z_of_int 0;;
	let one = z_of_int 1;;
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
	external logand: t -> t -> t = "mlgmp_z_logand";;
	external logor: t -> t -> t = "mlgmp_z_logor";;
	external logxor: t -> t -> t = "mlgmp_z_logxor";;
	external lognot: t -> t = "mlgmp_z_lognot";;
	external shift_left: t -> int -> t = "mlgmp_z_shift_left";;
	external shift_right: t -> int -> t = "mlgmp_z_shift_right";;
	external of_based_string: base:int -> string -> t = "mlgmp_z_of_based_string";;
	let of_string = z_of_string;;
	external to_based_string: base:int -> t -> string = "mlgmp_based_string_of_z";;
	let to_string = string_of_z;;
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
let q_of_string = q_of_based_string ~base:10;;
external based_string_of_q: base:int -> q -> string = "mlgmp_based_string_of_q";;
let string_of_q = based_string_of_q ~base:10;;
external q_of_int: int -> q = "mlgmp_q_of_int";;
external q_of_float: float -> q = "mlgmp_q_of_float";;
external float_of_q: q -> float = "mlgmp_float_of_q";;
external q_of_z: z -> q = "mlgmp_q_of_z";;
external z_of_truncated_q: q -> z = "mlgmp_z_of_truncated_q";;

module Q = struct
	type t = q;;
	let zero = q_of_int 0;;
	let one = q_of_int 1;;
	external compare: t -> t -> int = "mlgmp_q_compare";;
	external neg: t -> t = "mlgmp_q_neg";;
	external add: t -> t -> t = "mlgmp_q_add";;
	external add_int: t -> int -> t = "mlgmp_q_add_int";;
	external sub: t -> t -> t = "mlgmp_q_sub";;
	external mul: t -> t -> t = "mlgmp_q_mul";;
	external div: t -> t -> t = "mlgmp_q_div";;
	external int_pow_int: base:int -> exponent:int -> t = "mlgmp_q_int_pow_int";;
	external scale: t -> base:int -> exponent:int -> t = "mlgmp_q_scale";;
	external num: t -> z = "mlgmp_q_num";;
	external den: t -> z = "mlgmp_q_den";;
	external of_based_string: base:int -> string -> t = "mlgmp_q_of_based_string";;
	let of_string = q_of_string;;
	external to_based_string: base:int -> t -> string = "mlgmp_based_string_of_q";;
	let to_string = string_of_q;;
	external of_int: int -> t = "mlgmp_q_of_int";;
	external of_float: float -> t = "mlgmp_q_of_float";;
	external to_float: t -> float = "mlgmp_float_of_q";;
	external of_z: z -> t = "mlgmp_q_of_z";;
	external make_int: int -> int -> t = "mlgmp_q_make_int";;
	external make_z: z -> z -> t = "mlgmp_q_make_z";;
end;;

type f;;

external neg: prec:int -> f -> f = "mlgmp_f_neg";;
external add: prec:int -> f -> f -> f = "mlgmp_f_add";;
external add_int: prec:int -> f -> int -> f = "mlgmp_f_add_int";;
external sub: prec:int -> f -> f -> f = "mlgmp_f_sub";;
external mul: prec:int -> f -> f -> f = "mlgmp_f_mul";;
external div: prec:int -> f -> f -> f = "mlgmp_f_div";;
external int_pow_int: prec:int -> base:int -> exponent:int -> f = "mlgmp_f_int_pow_int";;
external scale: prec:int -> f -> base:int -> exponent:int -> f = "mlgmp_f_scale";;
external log: prec:int -> f -> f = "mlgmp_f_log";;
external based_log: prec:int -> base:int -> f -> f = "mlgmp_f_based_log";;
external frexp: prec:int -> f -> f * int = "mlgmp_f_frexp";;
external f_of_based_string: prec:int -> base:int -> string -> f = "mlgmp_f_of_based_string";;
let f_of_string = f_of_based_string ~base:10;;
external based_string_of_f: base:int -> f -> string = "mlgmp_based_string_of_f";;
let string_of_f = based_string_of_f ~base:10;;
external f_of_int: prec:int -> int -> f = "mlgmp_f_of_int";;
external f_of_float: prec:int -> float -> f = "mlgmp_f_of_float";;
external float_of_f: f -> float = "mlgmp_float_of_f";;
external f_of_z: prec:int -> z -> f = "mlgmp_f_of_z";;
external z_of_truncated_f: f -> z = "mlgmp_z_of_truncated_f";;
external f_of_f: prec:int -> f -> f = "mlgmp_f_of_f";;

external default_prec: unit -> int = "mlgmp_f_get_default_prec";;

module F (Prec: sig val prec: int end) = struct
	let prec = Prec.prec;;
	type t = f;;
	let zero = f_of_int ~prec 0;;
	let one = f_of_int ~prec 1;;
	external compare: t -> t -> int = "mlgmp_f_compare";;
	let neg = neg ~prec;;
	let add = add ~prec;;
	let add_int = add_int ~prec;;
	let sub = sub ~prec;;
	let mul = mul ~prec;;
	let div = div ~prec;;
	let int_pow_int = int_pow_int ~prec;;
	let scale = scale ~prec;;
	let log = log ~prec;;
	let based_log = based_log ~prec;;
	let frexp = frexp ~prec;;
	let of_based_string = f_of_based_string ~prec;;
	let of_string = of_based_string ~base:10;;
	external to_based_string: base:int -> t -> string = "mlgmp_based_string_of_f";;
	let to_string = string_of_f;;
	let of_int = f_of_int ~prec;;
	let of_float = f_of_float ~prec;;
	external to_float: t -> float = "mlgmp_float_of_f";;
	let of_z = f_of_z ~prec;;
end;;

external random_seed: unit -> int = "caml_sys_random_seed";;

module Random = struct
	type t;;
	external make_int: int -> t = "mlgmp_random_make_int";;
	let make_self_init () = make_int (random_seed ());
	external make_z: z -> t = "mlgmp_random_make_z";;
	let make a =
		let rec loop a i seed =
			if i >= Array.length a then make_z seed else
			let n = Z.add_int (Z.shift_left seed 30) a.(i) in
			loop a (i + 1) n
		in
		loop a 0 Z.zero
	external copy: t -> t = "mlgmp_random_copy";;
	external bits: t -> int = "mlgmp_random_bits";;
	external f_bits: t -> int -> f = "mlgmp_random_f_bits";;
	external int: t -> int -> int = "mlgmp_random_int";;
	external int32: t -> int32 -> int32 = "mlgmp_random_int32";;
	external nativeint: t -> nativeint -> nativeint = "mlgmp_random_nativeint";;
	external int64: t -> int64 -> int64 = "mlgmp_random_int64";;
	external bool: t -> bool = "mlgmp_random_bool";;
	let float state n = n *. float_of_f (f_bits state 52);;
	external z: t -> z -> z = "mlgmp_random_z";;
	external f: t -> prec:int -> f -> f = "mlgmp_random_f";;
end;;
