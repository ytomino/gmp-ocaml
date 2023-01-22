open Gmp;;
open Mpfr;;

external setup: unit -> unit = "mlmpc_setup";;
setup ();;

external mpc_compiled_version: unit -> int * int * int =
	"mlmpc_compiled_version";;
external mpc_compiled_version_string: unit -> string =
	"mlmpc_compiled_version_string";;
external mpc_get_version_string: unit -> string = "mlmpc_get_version_string";;

type c;;
type rounding_mode_elem = [`N | `Z | `U | `D | `A];;
type rounding_mode = rounding_mode_elem * rounding_mode_elem;;

external c_of_based_string: prec:int * int -> mode:rounding_mode -> base:int ->
	string -> c =
	"mlmpc_c_of_based_string";;
let c_of_string = c_of_based_string ~base:10;;
external based_string_of_c: mode:rounding_mode -> base:int -> c -> string =
	"mlmpc_based_string_of_c";;
let string_of_c = based_string_of_c ~base:10;;
external c_of_int: prec:int * int -> mode:rounding_mode -> int -> c =
	"mlmpc_c_of_int";;
external c_of_float: prec:int * int -> mode:rounding_mode -> float -> c =
	"mlmpc_c_of_float";;
external c_of_z: prec:int * int -> mode:rounding_mode -> z -> c =
	"mlmpc_c_of_z";;
external c_of_q: prec:int * int -> mode:rounding_mode -> q -> c =
	"mlmpc_c_of_q";;
external c_of_f: prec:int * int -> mode:rounding_mode -> f -> c =
	"mlmpc_c_of_f";;
external c_of_fr: prec:int * int -> mode:rounding_mode -> fr -> c =
	"mlmpc_c_of_fr";;
external make_int: prec:int * int -> mode:rounding_mode -> int -> int -> c =
	"mlmpc_c_make_int";;

let nn = (`N, `N);;

module C = struct
	type t = c;;
	let zero ~prec = c_of_int ~prec ~mode:nn 0;;
	let one ~prec = c_of_int ~prec ~mode:nn 1;;
	let minus_one ~prec = c_of_int ~prec ~mode:nn ~-1;;
	let i ~prec = make_int ~prec ~mode:nn 0 1;;
	external compare: t -> t -> int = "mlmpc_c_compare";;
	external compare_int: t -> int -> int = "mlmpc_c_compare_int";;
	external neg: prec:int * int -> mode:rounding_mode -> t -> t = "mlmpc_c_neg";;
	external abs: prec:int -> mode:Mpfr.rounding_mode -> t -> fr = "mlmpc_c_abs";;
	external add: prec:int * int -> mode:rounding_mode -> t -> t -> t =
		"mlmpc_c_add";;
	external add_int: prec:int * int -> mode:rounding_mode -> t -> int -> t =
		"mlmpc_c_add_int";;
	external sub: prec:int * int -> mode:rounding_mode -> t -> t -> t =
		"mlmpc_c_sub";;
	external sub_int: prec:int * int -> mode:rounding_mode -> t -> int -> t =
		"mlmpc_c_sub_int";;
	external mul: prec:int * int -> mode:rounding_mode -> t -> t -> t =
		"mlmpc_c_mul";;
	external mul_int: prec:int * int -> mode:rounding_mode -> t -> int -> t =
		"mlmpc_c_mul_int";;
	external div: prec:int * int -> mode:rounding_mode -> t -> t -> t =
		"mlmpc_c_div";;
	external pow_int: prec:int * int -> mode:rounding_mode -> base:t ->
		exponent:int -> t =
		"mlmpc_c_pow_int";;
	external int_pow_int: prec:int * int -> mode:rounding_mode -> base:int ->
		exponent:int -> t =
		"mlmpc_c_int_pow_int";;
	external scale: prec:int * int -> mode:rounding_mode -> t -> base:int ->
		exponent:int -> t =
		"mlmpc_c_scale";;
	external root: prec:int * int -> mode:rounding_mode -> nth:int -> t -> t =
		"mlmpc_c_root";;
	external sqrt: prec:int * int -> mode:rounding_mode -> t -> t =
		"mlmpc_c_sqrt";;
	external log: prec:int * int -> mode:rounding_mode -> t -> t = "mlmpc_c_log";;
	external based_log: prec:int * int -> mode:rounding_mode -> base:int -> t ->
		t =
		"mlmpc_c_based_log";;
	external pow: prec:int * int -> mode:rounding_mode -> t -> t -> t =
		"mlmpc_c_pow";;
	external exp: prec:int * int -> mode:rounding_mode -> t -> t = "mlmpc_c_exp";;
	external conj: prec:int * int -> mode:rounding_mode -> t -> t =
		"mlmpc_c_conj";;
	external norm2: prec:int -> mode:Mpfr.rounding_mode -> t -> fr =
		"mlmpc_c_norm2";;
	external arg: prec:int -> mode:Mpfr.rounding_mode -> t -> fr = "mlmpc_c_arg";;
	external polar: prec:int * int -> mode:rounding_mode -> fr -> fr -> t =
		"mlmpc_c_polar";;
	external proj: prec:int * int -> mode:rounding_mode -> t -> t =
		"mlmpc_c_proj";;
	external real: t -> fr = "mlmpc_c_real";;
	external imag: t -> fr = "mlmpc_c_imag";;
	external of_based_string: prec:int * int -> mode:rounding_mode -> base:int ->
		string -> t =
		"mlmpc_c_of_based_string";;
	let of_string = c_of_string;;
	external to_based_string: mode:rounding_mode -> base:int -> t -> string =
		"mlmpc_based_string_of_c";;
	let to_string = string_of_c;;
	external of_int: prec:int * int -> mode:rounding_mode -> int -> t =
		"mlmpc_c_of_int";;
	external of_float: prec:int * int -> mode:rounding_mode -> float -> t =
		"mlmpc_c_of_float";;
	external of_z: prec:int * int -> mode:rounding_mode -> z -> t =
		"mlmpc_c_of_z";;
	external of_q: prec:int * int -> mode:rounding_mode -> q -> t =
		"mlmpc_c_of_q";;
	external of_f: prec:int * int -> mode:rounding_mode -> f -> t =
		"mlmpc_c_of_f";;
	external of_fr: prec:int * int -> mode:rounding_mode -> fr -> t =
		"mlmpc_c_of_fr";;
	external make_int: prec:int * int -> mode:rounding_mode -> int -> int -> t =
		"mlmpc_c_make_int";;
	external make_float: prec:int * int -> mode:rounding_mode -> float -> float ->
		t =
		"mlmpc_c_make_float";;
	external make_z: prec:int * int -> mode:rounding_mode -> z -> z -> t =
		"mlmpc_c_make_z";;
	external make_q: prec:int * int -> mode:rounding_mode -> q -> q -> t =
		"mlmpc_c_make_q";;
	external make_f: prec:int * int -> mode:rounding_mode -> f -> f -> t =
		"mlmpc_c_make_f";;
	external make_fr: prec:int * int -> mode:rounding_mode -> fr -> fr -> t =
		"mlmpc_c_make_fr";;
	module type Param = sig
		val prec: int * int
		val mode: rounding_mode
	end;;
	module Make (Param: Param) = struct
		open Param
		type t = c;;
		let zero = zero ~prec;;
		let one = one ~prec;;
		let minus_one = minus_one ~prec;;
		let i = i ~prec;;
		external compare: t -> t -> int = "mlmpc_c_compare";;
		external compare_int: t -> int -> int = "mlmpc_c_compare_int";;
		let neg = neg ~prec ~mode;;
		let abs = abs ~prec:(fst prec) ~mode:(fst mode :> Mpfr.rounding_mode);;
		let add = add ~prec ~mode;;
		let add_int = add_int ~prec ~mode;;
		let sub = sub ~prec ~mode;;
		let sub_int = sub_int ~prec ~mode;;
		let mul = mul ~prec ~mode;;
		let mul_int = mul_int ~prec ~mode;;
		let div = div ~prec ~mode;;
		let pow_int = pow_int ~prec ~mode;;
		let int_pow_int = int_pow_int ~prec ~mode;;
		let scale = scale ~prec ~mode;;
		let root = root ~prec ~mode;;
		let sqrt = sqrt ~prec ~mode;;
		let log = log ~prec ~mode;;
		let based_log = based_log ~prec ~mode;;
		let pow = pow ~prec ~mode;;
		let exp = exp ~prec ~mode;;
		let conj = conj ~prec ~mode;;
		let norm2 = norm2 ~prec:(fst prec) ~mode:(fst mode :> Mpfr.rounding_mode);;
		let arg = arg ~prec:(fst prec) ~mode:(fst mode :> Mpfr.rounding_mode);;
		let polar = polar ~prec ~mode;;
		let proj = proj ~prec ~mode;;
		external real: t -> fr = "mlmpc_c_real";;
		external imag: t -> fr = "mlmpc_c_imag";;
		let of_based_string = of_based_string ~prec ~mode;;
		let of_string = of_string ~prec ~mode;;
		let to_based_string = to_based_string ~mode;;
		let to_string = to_string ~mode;;
		let of_int = of_int ~prec ~mode;;
		let of_float = of_float ~prec ~mode;;
		let of_z = of_z ~prec ~mode;;
		let of_q = of_q ~prec ~mode;;
		let of_f = of_f ~prec ~mode;;
		let of_fr = of_fr ~prec ~mode;;
		let make_int = make_int ~prec ~mode;;
		let make_float = make_float ~prec ~mode;;
		let make_z = make_z ~prec ~mode;;
		let make_q = make_q ~prec ~mode;;
		let make_f = make_f ~prec ~mode;;
		let make_fr = make_fr ~prec ~mode;;
	end;;
	let default_prec () =
		let fr_prec = FR.default_prec () in
		fr_prec, fr_prec;;
	external default_rounding_mode: unit -> rounding_mode =
		"mlmpc_c_get_default_rounding_mode";;
	let default () =
		let module Default: Param = struct
			let prec = default_prec ();;
			let mode = default_rounding_mode ();;
		end in
		(module Default: Param);;
end;;
