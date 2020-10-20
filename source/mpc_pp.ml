open Mpc;;
open Format;;
open Mpfr_pp;;

let pp_c (f: formatter) (x: c) = (
	pp_print_string f (string_of_c ~mode:(default_rounding_mode()) x)
);;

(* like Complex.t for the toplevel *)
let pp_complex_of_c (f: formatter) (x: c) = (
	let module C = C (struct let prec = default_prec () end) in
	pp_print_char f '{';
	pp_open_box f 0;
	pp_open_box f 0;
	pp_print_string f "re =";
	pp_print_space f ();
	pp_float_of_fr f (C.real x);
	pp_close_box f ();
	pp_print_char f ';';
	pp_print_space f ();
	pp_open_box f 0;
	pp_print_string f "im =";
	pp_print_space f ();
	pp_float_of_fr f (C.imag x);
	pp_close_box f ();
	pp_close_box f ();
	pp_print_char f '}'
);;
