module type N = sig (* numeric *)
	type real
	type t
	val zero: t
	val one: t
	val compare: t -> t -> int
	val compare_int: t -> int -> int
	val neg: t -> t
	val abs: t -> real
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
	val of_based_string: base:int -> string -> t
	val of_string: string -> t
	val to_based_string: base:int -> t -> string
	val to_string: t -> string
	val of_int: int -> t
end;;

module type S = sig (* scalar *)
	type t
	include N with type real := t and type t := t
	val to_float: t -> float
end;;

module type R = sig (* real *)
	include S
	val of_float: float -> t
end;;

module type F = sig (* float *)
	include R
	val nearly_equal: int -> t -> t -> bool
	val frexp: t -> t * int
	val ceil: t -> t
	val floor: t -> t
	val log: t -> t
	val based_log: base:int -> t -> t
end;;

let (_: unit) = let module Check: S = Gmp.Z in ();;
let (_: unit) = let module Check: R = Gmp.Q in ();;

module F10 = Gmp.F (struct let prec = 10 end);;

let (_: unit) = let module Check: F = F10 in ();;

module FR10 = Mpfr.FR (struct let prec = 10 end);;
module FR10D = FR10.F (struct let rounding_mode = `D end);;

let (_: unit) = let module Check: F = FR10D in ();;

module C10 = Mpc.C (struct let prec = 10, 10 end);;
module C10DD = C10.F (struct let rounding_mode = `D, `D end);;

let (_: unit) = let module Check: N with type real := Mpfr.fr = C10DD in ();;

Printf.eprintf "ok\n";;
