open Mpfr;;
open Format;;

let pp_fr (f: formatter) (x: fr) = (
	pp_print_string f (string_of_fr ~mode:(FR.default_rounding_mode ()) x)
);;

(* like float for the toplevel *)
let pp_float_of_fr (f: formatter) (x: fr) = (
	let s = string_of_fr ~mode:(FR.default_rounding_mode ()) x in
	let s =
		(* according to the standard pretty printer of float *)
		if s = "inf" then "infinity" else
		if s = "-inf" then "neg_infinity" else
		s
	in
	pp_print_string f s
);;
