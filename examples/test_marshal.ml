open Gmp;;
open Mpfr;;
open Mpc;;

let log = false;;

let marshal (x: 'a) = (
	if log then (Printf.eprintf "serialize\n"; flush stderr);
	let s = Marshal.to_string x [] in
	if log then (Printf.eprintf "deserialize\n"; flush stderr);
	let y = Marshal.from_string s 0 in
	if log then (Printf.eprintf "compare\n"; flush stderr);
	Gc.full_major ();
	y
);;

let check_marshal (x: 'a) = (
	x = marshal x
);;

if log then (Printf.eprintf "Z\n"; flush stderr);;

assert (check_marshal Z.zero);;
assert (check_marshal Z.one);;
assert (check_marshal (Z.of_int 2, Z.of_int ~-3));;

if log then (Printf.eprintf "Q\n"; flush stderr);;

assert (check_marshal Q.zero);;
assert (check_marshal Q.one);;
assert (check_marshal (Q.make_int 2 3, Q.make_int ~-3 ~-4));;

if log then (Printf.eprintf "F\n"; flush stderr);;

module Fd = F.Make (val F.default ());;

assert (check_marshal Fd.zero);;
assert (check_marshal Fd.one);;
assert (check_marshal (Fd.of_float 1.41421356, Fd.of_float ~-.2.3620679));;

if log then (Printf.eprintf "FR\n"; flush stderr);;

module FRd = FR.Make (val FR.default ());;

assert (check_marshal FRd.zero);;
assert (check_marshal FRd.one);;
assert (check_marshal (FRd.of_float 1.41421356, FRd.of_float ~-.2.3620679));;
assert (check_marshal (FRd.of_float infinity));;
assert (check_marshal (FRd.of_float neg_infinity));;
assert (classify_float (FRd.to_float (marshal (FRd.of_float nan))) = FP_nan);;

if log then (Printf.eprintf "C\n"; flush stderr);;

module Cd = C.Make (val C.default ());;

assert (check_marshal Cd.zero);;
assert (check_marshal Cd.one);;
assert (check_marshal Cd.i);;
assert (check_marshal (Cd.make_float ~-.1.2 3.4, Cd.make_float ~-.5.6 7.8));;

prerr_endline "ok";;
