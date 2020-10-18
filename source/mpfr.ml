open Gmp;;

external setup: unit -> unit = "mlmpfr_setup";;
setup ();;

type fr;;
type rounding_mode = [`N | `Z | `U | `D | `A | `F | `NA];;

external neg: prec:int -> mode:rounding_mode -> fr -> fr = "mlmpfr_fr_neg";;
external abs: prec:int -> mode:rounding_mode -> fr -> fr = "mlmpfr_fr_abs";;
external add: prec:int -> mode:rounding_mode -> fr -> fr -> fr =
	"mlmpfr_fr_add";;
external add_int: prec:int -> mode:rounding_mode -> fr -> int -> fr =
	"mlmpfr_fr_add_int";;
external sub: prec:int -> mode:rounding_mode -> fr -> fr -> fr =
	"mlmpfr_fr_sub";;
external sub_int: prec:int -> mode:rounding_mode -> fr -> int -> fr =
	"mlmpfr_fr_sub_int";;
external mul: prec:int -> mode:rounding_mode -> fr -> fr -> fr =
	"mlmpfr_fr_mul";;
external mul_int: prec:int -> mode:rounding_mode -> fr -> int -> fr =
	"mlmpfr_fr_mul_int";;
external div: prec:int -> mode:rounding_mode -> fr -> fr -> fr =
	"mlmpfr_fr_div";;
external pow_int: prec:int -> mode:rounding_mode -> base:fr -> exponent:int ->
	fr =
	"mlmpfr_fr_pow_int";;
external int_pow_int: prec:int -> mode:rounding_mode -> base:int ->
	exponent:int -> fr =
	"mlmpfr_fr_int_pow_int";;
external scale: prec:int -> mode:rounding_mode -> fr -> base:int ->
	exponent:int -> fr =
	"mlmpfr_fr_scale";;
external root: prec:int -> mode:rounding_mode -> nth:int -> fr -> fr =
	"mlmpfr_fr_root";;
external sqrt: prec:int -> mode:rounding_mode -> fr -> fr = "mlmpfr_fr_sqrt";;
external frexp: prec:int -> mode:rounding_mode -> fr -> fr * int =
	"mlmpfr_fr_frexp";;
external trunc: prec:int -> fr -> fr = "mlmpfr_fr_trunc";;
external ceil: prec:int -> fr -> fr = "mlmpfr_fr_ceil";;
external floor: prec:int -> fr -> fr = "mlmpfr_fr_floor";;
external pi: prec:int -> mode:rounding_mode -> fr = "mlmpfr_fr_pi";;
external log: prec:int -> mode:rounding_mode -> fr -> fr = "mlmpfr_fr_log";;
external based_log: prec:int -> mode:rounding_mode -> base:int -> fr -> fr =
	"mlmpfr_fr_based_log";;
external pow: prec:int -> mode:rounding_mode -> fr -> fr -> fr =
	"mlmpfr_fr_pow";;
external exp: prec:int -> mode:rounding_mode -> fr -> fr = "mlmpfr_fr_exp";;
external sin: prec:int -> mode:rounding_mode -> fr -> fr = "mlmpfr_fr_sin";;
external cos: prec:int -> mode:rounding_mode -> fr -> fr = "mlmpfr_fr_cos";;
external tan: prec:int -> mode:rounding_mode -> fr -> fr = "mlmpfr_fr_tan";;
external atan: prec:int -> mode:rounding_mode -> fr -> fr = "mlmpfr_fr_atan";;
external atan2: prec:int -> mode:rounding_mode -> fr -> fr -> fr =
	"mlmpfr_fr_atan2";;
external acosh: prec:int -> mode:rounding_mode -> fr -> fr =
	"mlmpfr_fr_acosh";;
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

external default_prec: unit -> int = "mlmpfr_fr_get_default_prec";;
external default_rounding_mode: unit -> rounding_mode =
	"mlmpfr_fr_get_default_rounding_mode";;

module FR (Prec: sig val prec: int end) = struct
	let prec = Prec.prec;;
	type t = fr;;
	let zero = fr_of_int ~prec ~mode:`N 0;;
	let one = fr_of_int ~prec ~mode:`N 1;;
	let minus_one = fr_of_int ~prec ~mode:`N ~-1;;
	external compare: t -> t -> int = "mlmpfr_fr_compare";;
	external compare_int: t -> int -> int = "mlmpfr_fr_compare_int";;
	let neg = neg ~prec;;
	let abs = abs ~prec;;
	let add = add ~prec;;
	let add_int = add_int ~prec;;
	let sub = sub ~prec;;
	let sub_int = sub_int ~prec;;
	let mul = mul ~prec;;
	let mul_int = mul_int ~prec;;
	let div = div ~prec;;
	let pow_int = pow_int ~prec;;
	let int_pow_int = int_pow_int ~prec;;
	let scale = scale ~prec;;
	let root = root ~prec;;
	let sqrt = sqrt ~prec;;
	external nearly_equal: int -> t -> t -> bool = "mlmpfr_fr_nearly_equal";;
	let frexp = frexp ~prec;;
	let trunc = trunc ~prec;;
	let ceil = ceil ~prec;;
	let floor = floor ~prec;;
	external is_infinite: t -> bool = "mlmpfr_fr_is_infinite"
	let pi = pi ~prec;;
	let log = log ~prec;;
	let based_log = based_log ~prec;;
	let pow = pow ~prec;;
	let exp = exp ~prec;;
	let sin = sin ~prec;;
	let cos = cos ~prec;;
	let tan = tan ~prec;;
	let atan = atan ~prec;;
	let atan2 = atan2 ~prec;;
	let acosh = acosh ~prec;;
	let of_based_string = fr_of_based_string ~prec;;
	let of_string = of_based_string ~base:10;;
	external to_based_string: mode:rounding_mode -> base:int -> fr -> string =
		"mlmpfr_based_string_of_fr";;
	let to_string = string_of_fr;;
	let of_int = fr_of_int ~prec;;
	let of_float = fr_of_float ~prec;;
	external to_float: mode:rounding_mode -> fr -> float = "mlmpfr_float_of_fr";;
	let of_z = fr_of_z ~prec;;
	external to_z: mode:rounding_mode -> t -> z = "mlmpfr_z_of_fr";;
	module F (Mode: sig val rounding_mode: rounding_mode end) = struct
		let mode = Mode.rounding_mode;;
		type t = fr;;
		let zero = zero;;
		let one = one;;
		let minus_one = minus_one;;
		external compare: t -> t -> int = "mlmpfr_fr_compare";;
		external compare_int: t -> int -> int = "mlmpfr_fr_compare_int";;
		let neg = neg ~mode;;
		let abs = abs ~mode;;
		let add = add ~mode;;
		let add_int = add_int ~mode;;
		let sub = sub ~mode;;
		let sub_int = sub_int ~mode;;
		let mul = mul ~mode;;
		let mul_int = mul_int ~mode;;
		let div = div ~mode;;
		let pow_int = pow_int ~mode;;
		let int_pow_int = int_pow_int ~mode;;
		let scale = scale ~mode;;
		let root = root ~mode;;
		let sqrt = sqrt ~mode;;
		external nearly_equal: int -> t -> t -> bool = "mlmpfr_fr_nearly_equal";;
		let frexp = frexp ~mode;;
		let trunc = trunc;;
		let ceil = ceil;;
		let floor = floor;;
		external is_infinite: t -> bool = "mlmpfr_fr_is_infinite"
		let pi = pi ~mode;;
		let log = log ~mode;;
		let based_log = based_log ~mode;;
		let pow = pow ~mode;;
		let exp = exp ~mode;;
		let sin = sin ~mode;;
		let cos = cos ~mode;;
		let tan = tan ~mode;;
		let atan = atan ~mode;;
		let atan2 = atan2 ~mode;;
		let acosh = acosh ~mode;;
		let of_based_string = of_based_string ~mode;;
		let of_string = of_based_string ~base:10;;
		let to_based_string = to_based_string ~mode;;
		let to_string = to_based_string ~base:10;;
		let of_int = of_int ~mode;;
		let of_float = of_float ~mode;;
		let to_float = float_of_fr ~mode;;
		let of_z = of_z ~mode;;
		let to_z = to_z ~mode;;
	end;;
end;;
