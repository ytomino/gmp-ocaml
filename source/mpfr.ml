open Gmp;;

external setup: unit -> unit = "mlmpfr_setup";;
setup ();;

external mpfr_compiled_version: unit -> int * int * int =
	"mlmpfr_compiled_version";;
external mpfr_compiled_version_string: unit -> string =
	"mlmpfr_compiled_version_string";;
external mpfr_get_version_string: unit -> string =
	"mlmpfr_get_version_string";;

type fr;;
type rounding_mode = [`N | `Z | `U | `D | `A | `F | `NA];;

external fr_of_based_string: prec:int -> mode:rounding_mode -> base:int ->
	string -> fr =
	"mlmpfr_fr_of_based_string";;
let fr_of_string = fr_of_based_string ~base:10;;
external based_string_of_fr: mode:rounding_mode -> base:int -> fr -> string =
	"mlmpfr_based_string_of_fr";;
let string_of_fr = based_string_of_fr ~base:10;;
external fr_get_str: mode:rounding_mode -> base:int -> int -> fr ->
	string * int =
	"mlmpfr_fr_get_str";;
external fr_of_int: prec:int -> mode:rounding_mode -> int -> fr =
	"mlmpfr_fr_of_int";;
external fr_of_float: prec:int -> mode:rounding_mode -> float -> fr =
	"mlmpfr_fr_of_float";;
external float_of_fr: mode:rounding_mode -> fr -> float =
	"mlmpfr_float_of_fr";;
external fr_of_z: prec:int -> mode:rounding_mode -> z -> fr =
	"mlmpfr_fr_of_z";;
external z_of_fr: mode:rounding_mode -> fr -> z = "mlmpfr_z_of_fr";;
let z_of_truncated_fr = z_of_fr ~mode:`Z;;
external fr_of_fr: prec:int -> mode:rounding_mode -> fr -> fr =
	"mlmpfr_fr_of_fr";;
external bits_of_single: fr -> int32 = "mlmpfr_fr_bits_of_single";;
external bits_of_double: fr -> int64 = "mlmpfr_fr_bits_of_double";;
external bits_of_extended: fr -> int64 * int = "mlmpfr_fr_bits_of_extended";;
external single_of_bits: int32 -> fr = "mlmpfr_fr_single_of_bits";;
external double_of_bits: int64 -> fr = "mlmpfr_fr_double_of_bits";;
external extended_of_bits: int64 * int -> fr = "mlmpfr_fr_extended_of_bits";;

module FR = struct
	type t = fr;;
	let zero ~prec = fr_of_int ~prec ~mode:`N 0;;
	let one ~prec = fr_of_int ~prec ~mode:`N 1;;
	let minus_one ~prec = fr_of_int ~prec ~mode:`N ~-1;;
	external compare: t -> t -> int = "mlmpfr_fr_compare";;
	external compare_int: t -> int -> int = "mlmpfr_fr_compare_int";;
	external neg: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_neg";;
	external abs: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_abs";;
	external add: prec:int -> mode:rounding_mode -> t -> t -> t = "mlmpfr_fr_add";;
	external add_int: prec:int -> mode:rounding_mode -> t -> int -> t =
		"mlmpfr_fr_add_int";;
	external sub: prec:int -> mode:rounding_mode -> t -> t -> t = "mlmpfr_fr_sub";;
	external sub_int: prec:int -> mode:rounding_mode -> t -> int -> t =
		"mlmpfr_fr_sub_int";;
	external mul: prec:int -> mode:rounding_mode -> t -> t -> t = "mlmpfr_fr_mul";;
	external mul_int: prec:int -> mode:rounding_mode -> t -> int -> t =
		"mlmpfr_fr_mul_int";;
	external div: prec:int -> mode:rounding_mode -> t -> t -> t = "mlmpfr_fr_div";;
	external fma: prec:int -> mode:rounding_mode -> t -> t -> t -> t =
		"mlmpfr_fr_fma";;
	external pow_int: prec:int -> mode:rounding_mode -> base:t -> exponent:int ->
		t =
		"mlmpfr_fr_pow_int";;
	external int_pow_int: prec:int -> mode:rounding_mode -> base:int ->
		exponent:int -> t =
		"mlmpfr_fr_int_pow_int";;
	external scale: prec:int -> mode:rounding_mode -> t -> base:int ->
		exponent:int -> t =
		"mlmpfr_fr_scale";;
	external root: prec:int -> mode:rounding_mode -> nth:int -> t -> t =
		"mlmpfr_fr_root";;
	external sqrt: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_sqrt";;
	external nearly_equal: int -> t -> t -> bool = "mlmpfr_fr_nearly_equal";;
	external frexp: prec:int -> mode:rounding_mode -> t -> t * int =
		"mlmpfr_fr_frexp";;
	external trunc: prec:int -> t -> t = "mlmpfr_fr_trunc";;
	external ceil: prec:int -> t -> t = "mlmpfr_fr_ceil";;
	external floor: prec:int -> t -> t = "mlmpfr_fr_floor";;
	external is_infinite: t -> bool = "mlmpfr_fr_is_infinite"
	external pi: prec:int -> mode:rounding_mode -> t = "mlmpfr_fr_pi";;
	external log: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_log";;
	external based_log: prec:int -> mode:rounding_mode -> base:int -> t -> t =
		"mlmpfr_fr_based_log";;
	external pow: prec:int -> mode:rounding_mode -> t -> t -> t = "mlmpfr_fr_pow";;
	external exp: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_exp";;
	external sin: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_sin";;
	external cos: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_cos";;
	external tan: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_tan";;
	external atan: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_atan";;
	external atan2: prec:int -> mode:rounding_mode -> t -> t -> t =
		"mlmpfr_fr_atan2";;
	external acosh: prec:int -> mode:rounding_mode -> t -> t = "mlmpfr_fr_acosh";;
	external of_based_string: prec:int -> mode:rounding_mode -> base:int ->
		string -> t =
		"mlmpfr_fr_of_based_string";;
	let of_string = fr_of_string;;
	external to_based_string: mode:rounding_mode -> base:int -> t -> string =
		"mlmpfr_based_string_of_fr";;
	let to_string = string_of_fr;;
	external of_int: prec:int -> mode:rounding_mode -> int -> t =
		"mlmpfr_fr_of_int";;
	external of_float: prec:int -> mode:rounding_mode -> float -> t =
		"mlmpfr_fr_of_float";;
	external to_float: mode:rounding_mode -> t -> float = "mlmpfr_float_of_fr";;
	external of_z: prec:int -> mode:rounding_mode -> z -> t = "mlmpfr_fr_of_z";;
	external to_z: mode:rounding_mode -> t -> z = "mlmpfr_z_of_fr";;
	module type Param = sig
		val prec: int
		val mode: rounding_mode
	end;;
	module Make (Param: Param) = struct
		open Param
		type t = fr;;
		let zero = zero ~prec;;
		let one = one ~prec;;
		let minus_one = minus_one ~prec;;
		external compare: t -> t -> int = "mlmpfr_fr_compare";;
		external compare_int: t -> int -> int = "mlmpfr_fr_compare_int";;
		let neg = neg ~prec ~mode;;
		let abs = abs ~prec ~mode;;
		let add = add ~prec ~mode;;
		let add_int = add_int ~prec ~mode;;
		let sub = sub ~prec ~mode;;
		let sub_int = sub_int ~prec ~mode;;
		let mul = mul ~prec ~mode;;
		let mul_int = mul_int ~prec ~mode;;
		let div = div ~prec ~mode;;
		let fma = fma ~prec ~mode;;
		let pow_int = pow_int ~prec ~mode;;
		let int_pow_int = int_pow_int ~prec ~mode;;
		let scale = scale ~prec ~mode;;
		let root = root ~prec ~mode;;
		let sqrt = sqrt ~prec ~mode;;
		external nearly_equal: int -> t -> t -> bool = "mlmpfr_fr_nearly_equal";;
		let frexp = frexp ~prec ~mode;;
		let trunc = trunc ~prec;;
		let ceil = ceil ~prec;;
		let floor = floor ~prec;;
		external is_infinite: t -> bool = "mlmpfr_fr_is_infinite"
		let pi = pi ~prec ~mode;;
		let log = log ~prec ~mode;;
		let based_log = based_log ~prec ~mode;;
		let pow = pow ~prec ~mode;;
		let exp = exp ~prec ~mode;;
		let sin = sin ~prec ~mode;;
		let cos = cos ~prec ~mode;;
		let tan = tan ~prec ~mode;;
		let atan = atan ~prec ~mode;;
		let atan2 = atan2 ~prec ~mode;;
		let acosh = acosh ~prec ~mode;;
		let of_based_string = of_based_string ~prec ~mode;;
		let of_string = of_string ~prec ~mode;;
		let to_based_string = to_based_string ~mode;;
		let to_string = to_string ~mode;;
		let of_int = of_int ~prec ~mode;;
		let of_float = of_float ~prec ~mode;;
		let to_float = float_of_fr ~mode;;
		let of_z = of_z ~prec ~mode;;
		let to_z = to_z ~mode;;
	end;;
	external default_prec: unit -> int = "mlmpfr_fr_get_default_prec";;
	external default_rounding_mode: unit -> rounding_mode =
		"mlmpfr_fr_get_default_rounding_mode";;
	let default () =
		let module Default: Param = struct
			let prec = default_prec ();;
			let mode = default_rounding_mode ();;
		end in
		(module Default: Param);;
end;;
