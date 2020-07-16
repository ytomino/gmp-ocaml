open Gmp;;
open Format;;

let pp_z (f: formatter) (x: z) = (
	pp_print_string f (string_of_z x)
);;

let pp_q (f: formatter) (x: q) = (
	pp_print_string f (string_of_q x)
);;

let pp_f (f: formatter) (x: f) = (
	pp_print_string f (string_of_f x)
);;
