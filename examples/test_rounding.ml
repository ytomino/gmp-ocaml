open Mpfr;;
open Mpc;;

let verbose = false;;

(* check the mode A of mpfr *)

try
	(* positive *)
	let x = fr_of_float ~prec:8 ~mode:`A 0x1.01p0 in
	assert (x = fr_of_float ~prec:56 ~mode:`Z 0x1.02p0);
	(* negative *)
	let x = fr_of_float ~prec:8 ~mode:`A (-0x1.01p0) in
	assert (x = fr_of_float ~prec:56 ~mode:`Z (-0x1.02p0))
with
| Failure _ ->
	if verbose then Printf.eprintf "MPFR_RNDA is unsupported.\n";
	let major, _, _ = mpfr_compiled_version () in
	assert (major < 3);;

(* check the mode F of mpfr *)

try
	(* positive *)
	let x = fr_of_float ~prec:8 ~mode:`A 0x1.01p0 in
	let y = FR.add ~prec:53 ~mode:`F x x in (* same as ~prec:23 ~mode:`N *)
	let z = FR.add ~prec:23 ~mode:`N x x in
	assert (y = z && y = fr_of_float ~prec:56 ~mode:`Z 0x204p-8);
	(* negative *)
	let x = fr_of_float ~prec:8 ~mode:`A (-0x1.01p0) in
	let y = FR.add ~prec:53 ~mode:`F x x in (* same as ~prec:23 ~mode:`N *)
	let z = FR.add ~prec:23 ~mode:`N x x in
	assert (y = z && y = fr_of_float ~prec:56 ~mode:`Z (-0x204p-8))
with
| Failure _ ->
	if verbose then Printf.eprintf "MPFR_RNDF is unsupported.\n";
	let major, _, _ = mpfr_compiled_version () in
	assert (major < 3);;

(* check the mode A of mpc *)

try
	(* positive, zero *)
	let x = c_of_float ~prec:(8, 8) ~mode:(`A, `A) 0x1.01p0 in
	assert (x = c_of_float ~prec:(56, 56) ~mode:(`Z, `Z) 0x1.02p0);
	(* negative, zero *)
	let x = c_of_float ~prec:(8, 8) ~mode:(`A, `A) (-0x1.01p0) in
	assert (x = c_of_float ~prec:(56, 56) ~mode:(`Z, `Z) (-0x1.02p0));
	(* zero, positive *)
	let x = C.make_float ~prec:(8, 8) ~mode:(`A, `A) 0. 0x1.01p0 in
	assert (x = C.make_float ~prec:(56, 56) ~mode:(`Z, `Z) 0. 0x1.02p0);
	(* zero, negative *)
	let x = C.make_float ~prec:(8, 8) ~mode:(`A, `A) 0. (-0x1.01p0) in
	assert (x = C.make_float ~prec:(56, 56) ~mode:(`Z, `Z) 0. (-0x1.02p0))
with
| Failure _ ->
	if verbose then Printf.eprintf "MPC_RNDA is unsupported.\n";
	let major, minor, patchlevel = mpc_compiled_version () in
	let version = major lsl 16 + minor lsl 8 + patchlevel in
	assert (version < 0x010300);;

prerr_endline "ok";;
