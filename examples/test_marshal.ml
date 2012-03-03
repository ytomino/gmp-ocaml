open Gmp;;
open Mpfr;;
open Mpc;;

let log = false;;

let check_marshal (x: 'a): bool = (
	if log then (Printf.eprintf "serialize\n"; flush stderr);
	let s = Marshal.to_string x [] in
	if log then (Printf.eprintf "deserialize\n"; flush stderr);
	let y = Marshal.from_string s 0 in
	if log then (Printf.eprintf "compare\n"; flush stderr);
	Gc.full_major ();
	x = y
);;

if log then (Printf.eprintf "Z\n"; flush stderr);

assert (check_marshal Z.zero);;
assert (check_marshal Z.one);;
assert (check_marshal (Z.of_int 2, Z.of_int ~-3));;

if log then (Printf.eprintf "Q\n"; flush stderr);

assert (check_marshal Q.zero);;
assert (check_marshal Q.one);;
assert (check_marshal (Q.make_int 2 3, Q.make_int ~-3 ~-4));;

if log then (Printf.eprintf "F\n"; flush stderr);

module Fd = F (struct let prec = Gmp.default_prec () end);;

assert (check_marshal Fd.zero);;
assert (check_marshal Fd.one);;
assert (check_marshal (Fd.of_float 1.41421356, Fd.of_float ~-.2.3620679));;

if log then (Printf.eprintf "FR\n"; flush stderr);

module FRdp = FR (struct let prec = Mpfr.default_prec () end);;
module FRd = FRdp.F (struct let rounding_mode = Mpfr.default_rounding_mode () end);;

assert (check_marshal FRd.zero);;
assert (check_marshal FRd.one);;
assert (check_marshal (FRd.of_float 1.41421356, FRd.of_float ~-.2.3620679));;

if log then (Printf.eprintf "C\n"; flush stderr);

module Cdp = C (struct let prec = Mpc.default_prec () end);;
module Cd = Cdp.F (struct let rounding_mode = Mpc.default_rounding_mode () end);;

assert (check_marshal Cd.zero);;
assert (check_marshal Cd.one);;
assert (check_marshal Cd.i);;
assert (check_marshal (Cd.make_float ~-.1.2 3.4, Cd.make_float ~-.5.6 7.8));;

Printf.eprintf "ok\n";;
