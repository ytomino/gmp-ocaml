open Mpc;;
open Format;;

let pp_c (f: formatter) (x: c): unit = (
	pp_print_string f (string_of_c ~mode:(default_rounding_mode()) x)
);;
