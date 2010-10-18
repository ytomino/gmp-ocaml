module type S = sig
	type t;;
	val zero: t;;
	val one: t;;
	val compare: t -> t -> int;;
	val neg: t -> t;;
	val add: t -> t -> t;;
	val add_int: t -> int -> t;;
	val sub: t -> t -> t;;
	val mul: t -> t -> t;;
	val div: t -> t -> t;;
	val int_pow_int: base:int -> exponent:int -> t;;
	val scale: t -> base:int -> exponent:int -> t;;
	val of_based_string: base:int -> string -> t;;
	val of_string: string -> t;;
	val to_based_string: base:int -> t -> string;;
	val to_string: t -> string;;
	val of_int: int -> t;;
end;;

let (_: unit) = let module Check: S = Gmp.Z in ();;
let (_: unit) = let module Check: S = Gmp.Q in ();;

module F10 = Gmp.F (struct let prec = 10 end);;

let (_: unit) = let module Check: S = F10 in ();;

module FR10 = Mpfr.FR (struct let prec = 10 end);;
module FR10D = FR10.F (struct let rounding_mode = `D end);;

let (_: unit) = let module Check: S = FR10D in ();;

module C10 = Mpc.C (struct let prec = 10, 10 end);;
module C10DD = C10.F (struct let rounding_mode = `D, `D end);;

let (_: unit) = let module Check: S = C10DD in ();;
