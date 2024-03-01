module type N0 = sig (* numeric *)
	type t
	val compare: t -> t -> int
	val compare_int: t -> int -> int
end;;

module type N = sig (* numeric *)
	type real
	include N0
	val zero: t
	val one: t
	val minus_one: t
	val neg: t -> t
	val abs: t -> real
	val add: t -> t -> t
	val add_int: t -> int -> t
	val sub: t -> t -> t
	val sub_int: t -> int -> t
	val mul: t -> t -> t
	val mul_int: t -> int -> t
	val div: t -> t -> t
	val fma: t -> t -> t -> t
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

module type S0 = N0;; (* scalar *)

module type S = sig (* scalar *)
	type t
	include N with type real := t and type t := t
	val to_float: t -> float
end;;

module type R0 = S0;; (* real *)

module type R = sig (* real *)
	include S
	val of_float: float -> t
end;;

module type Elementary1 = sig (* basic elementary functions *)
	type t
	val log: t -> t
	val based_log: base:int -> t -> t
end;;

module type Elementary2 = sig (* additional elementary functions *)
	type t
	val pow: t ->t -> t
	val exp: t -> t
end;;

module type F0 = sig (* float *)
	include R0
	val nearly_equal: int -> t -> t -> bool
end;;

module type F1 = sig (* float *)
	include R
	include F0 with type t := t
	val frexp: t -> t * int
	val trunc: t -> t
	val ceil: t -> t
	val floor: t -> t
	include Elementary1 with type t := t
end;;

module type F2 = sig (* float *)
	include F1
	include Elementary2 with type t := t
end;;

module type C2 = sig (* complex *)
	include N
	include Elementary1 with type t := t
	include Elementary2 with type t := t
end;;

let (_: unit) = let module Check: S = Gmp.Z in ();;

let (_: unit) = let module Check: R = Gmp.Q in ();;

let (_: unit) = let module Check: F0 = Gmp.F in ();;
let (_: unit) =
	let module Check: F1 =
		Gmp.F.Make (struct
			let prec = 10;;
		end)
	in ();;

let (_: unit) = let module Check: F0 = Mpfr.FR in ();;
let (_: unit) =
	let module Check: F2 =
		Mpfr.FR.Make (struct
			let prec = 10;;
			let mode = `D;;
		end)
	in ();;

let (_: unit) = let module Check: S0 = Mpc.C in ();;
let (_: unit) =
	let module Check: C2 with type real := Mpfr.fr =
		Mpc.C.Make (struct
			let prec = 10, 10;;
			let mode = `D, `D;;
		end)
	in ();;

prerr_endline "ok";;
