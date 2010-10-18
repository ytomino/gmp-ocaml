open Gmp;;
open Format;;

let pp_z (f: formatter) (x: z): unit = (
	pp_print_string f (string_of_z x)
);;

let pp_q (f: formatter) (x: q): unit = (
	pp_print_string f (string_of_q x)
);;

let pp_f (f: formatter) (x: f): unit = (
	pp_print_string f (string_of_f x)
);;
