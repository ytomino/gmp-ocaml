open Gmp;;
open Mpfr;;

external setup: unit -> unit = "mlmpc_setup";;
setup ();;

type c;;
type rounding_mode_elem = [`N | `Z | `U | `D];;
type rounding_mode = rounding_mode_elem * rounding_mode_elem;;

external neg: prec:int * int -> mode:rounding_mode -> c -> c = "mlmpc_c_neg";;
external abs: prec:int * int -> mode:Mpfr.rounding_mode -> c -> fr = "mlmpc_c_abs";;
external add: prec:int * int -> mode:rounding_mode -> c -> c -> c = "mlmpc_c_add";;
external add_int: prec:int * int -> mode:rounding_mode -> c -> int -> c = "mlmpc_c_add_int";;
external sub: prec:int * int -> mode:rounding_mode -> c -> c -> c = "mlmpc_c_sub";;
external mul: prec:int * int -> mode:rounding_mode -> c -> c -> c = "mlmpc_c_mul";;
external div: prec:int * int -> mode:rounding_mode -> c -> c -> c = "mlmpc_c_div";;
external pow_int: prec:int * int -> mode:rounding_mode -> base:c -> exponent:int -> c = "mlmpc_c_pow_int";;
external int_pow_int: prec:int * int -> mode:rounding_mode -> base:int -> exponent:int -> c = "mlmpc_c_int_pow_int";;
external scale: prec:int * int -> mode:rounding_mode -> c -> base:int -> exponent:int -> c = "mlmpc_c_scale";;
external root: prec:int * int -> mode:rounding_mode -> nth:int -> c -> c = "mlmpc_c_root";;
external sqrt: prec:int * int -> mode:rounding_mode -> c -> c = "mlmpc_c_sqrt";;
external log: prec:int * int -> mode:rounding_mode -> c -> c = "mlmpc_c_log";;
external based_log: prec:int * int -> mode:rounding_mode -> base:int -> c -> c = "mlmpc_c_based_log";;
external c_of_based_string: prec:int * int -> mode:rounding_mode -> base:int -> string -> c = "mlmpc_c_of_based_string";;
let c_of_string = c_of_based_string ~base:10;;
external based_string_of_c: mode:rounding_mode -> base:int -> c -> string = "mlmpc_based_string_of_c";;
let string_of_c = based_string_of_c ~base:10;;
external c_of_int: prec:int * int -> mode:rounding_mode -> int -> c = "mlmpc_c_of_int";;
external c_of_float: prec:int * int -> mode:rounding_mode -> float -> c = "mlmpc_c_of_float";;
external c_of_z: prec:int * int -> mode:rounding_mode -> z -> c = "mlmpc_c_of_z";;
external c_of_q: prec:int * int -> mode:rounding_mode -> q -> c = "mlmpc_c_of_q";;
external c_of_f: prec:int * int -> mode:rounding_mode -> f -> c = "mlmpc_c_of_f";;
external c_of_fr: prec:int * int -> mode:rounding_mode -> fr -> c = "mlmpc_c_of_fr";;
external make_int: prec:int * int -> mode:rounding_mode -> int -> int -> c = "mlmpc_c_make_int";;
external make_float: prec:int * int -> mode:rounding_mode -> float -> float -> c = "mlmpc_c_make_float";;
external make_z: prec:int * int -> mode:rounding_mode -> z -> z -> c = "mlmpc_c_make_z";;
external make_q: prec:int * int -> mode:rounding_mode -> q -> q -> c = "mlmpc_c_make_q";;
external make_f: prec:int * int -> mode:rounding_mode -> f -> f -> c = "mlmpc_c_make_f";;
external make_fr: prec:int * int -> mode:rounding_mode -> fr -> fr -> c = "mlmpc_c_make_fr";;

let default_prec () =
	let mpfr_prec = default_prec () in
	mpfr_prec, mpfr_prec;;

let nn = (`N, `N);;

let default_rounding_mode () =
	match default_rounding_mode () with
	| #rounding_mode_elem as mpfr_rnd -> mpfr_rnd, mpfr_rnd
	| `A | `F | `NA -> nn;;

module C (Prec: sig val prec: int * int end) = struct
	let prec = Prec.prec;;
	type t = c;;
	let zero = c_of_int ~prec ~mode:nn 0;; 
	let one = c_of_int ~prec ~mode:nn 1;;
	let i = make_int ~prec ~mode:nn 0 1;;
	external compare: t -> t -> int = "mlmpc_c_compare";;
	external compare_int: t -> int -> int = "mlmpc_c_compare_int";;
	let neg = neg ~prec;;
	let abs = abs ~prec;;
	let add = add ~prec;;
	let add_int = add_int ~prec;;
	let sub = sub ~prec;;
	let mul = mul ~prec;;
	let div = div ~prec;;
	let pow_int = pow_int ~prec;;
	let int_pow_int = int_pow_int ~prec;;
	let scale = scale ~prec;;
	let root = root ~prec;;
	let sqrt = sqrt ~prec;;
	let log = log ~prec;;
	let based_log = based_log ~prec;;
	external real: t -> fr = "mlmpc_c_real";;
	external imag: t -> fr = "mlmpc_c_imag";;
	let of_based_string = c_of_based_string ~prec;;
	let of_string = of_based_string ~base:10;;
	external to_based_string: mode:rounding_mode -> base:int -> c -> string = "mlmpc_based_string_of_c";;
	let to_string = string_of_c;;
	let of_int = c_of_int ~prec;;
	let of_float = c_of_float ~prec;;
	let of_z = c_of_z ~prec;;
	let of_q = c_of_q ~prec;;
	let of_f = c_of_f ~prec;;
	let of_fr = c_of_fr ~prec;;
	let make_int = make_int ~prec;;
	let make_float = make_float ~prec;;
	let make_z = make_z ~prec;;
	let make_q = make_q ~prec;;
	let make_f = make_f ~prec;;
	let make_fr = make_fr ~prec;;
	module F (Mode: sig val rounding_mode: rounding_mode end) = struct
		let mode = Mode.rounding_mode;;
		type t = c;;
		let zero = zero;;
		let one = one;;
		let i = i;;
		external compare: t -> t -> int = "mlmpc_c_compare";;
		external compare_int: t -> int -> int = "mlmpc_c_compare_int";;
		let neg = neg ~mode;;
		let abs = abs ~mode:(fst mode :> Mpfr.rounding_mode);;
		let add = add ~mode;;
		let add_int = add_int ~mode;;
		let sub = sub ~mode;;
		let mul = mul ~mode;;
		let div = div ~mode;;
		let pow_int = pow_int ~mode;;
		let int_pow_int = int_pow_int ~mode;;
		let scale = scale ~mode;;
		let root = root ~mode;;
		let sqrt = sqrt ~mode;;
		let log = log ~mode;;
		let based_log = based_log ~mode;;
		external real: t -> fr = "mlmpc_c_real";;
		external imag: t -> fr = "mlmpc_c_imag";;
		let of_based_string = of_based_string ~mode;;
		let of_string = of_based_string ~base:10;;
		let to_based_string = to_based_string ~mode;;
		let to_string = to_based_string ~base:10;;
		let of_int = of_int ~mode;;
		let of_float = of_float ~mode;;
		let of_z = of_z ~mode;;
		let of_q = of_q ~mode;;
		let of_f = of_f ~mode;;
		let of_fr = of_fr ~mode;;
		let make_int = make_int ~mode;;
		let make_float = make_float ~mode;;
		let make_z = make_z ~mode;;
		let make_q = make_q ~mode;;
		let make_f = make_f ~mode;;
		let make_fr = make_fr ~mode;;
	end;;
end;;
