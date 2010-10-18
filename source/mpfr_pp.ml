open Mpfr;;
open Format;;

let pp_fr (f: formatter) (x: fr): unit = (
	pp_print_string f (string_of_fr ~mode:(default_rounding_mode ()) x)
);;
