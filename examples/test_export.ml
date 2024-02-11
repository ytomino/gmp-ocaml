open Gmp;;
open Mpfr;;

let log = false;;

(* Z *)

assert (Z.export_length (Z.of_int (-32769)) = 3);;
assert (Z.export_length (Z.of_int (-32768)) = 2);;
assert (Z.export_length (Z.of_int (-129)) = 2);;
assert (Z.export_length (Z.of_int (-128)) = 1);;
assert (Z.export_length (Z.of_int (-1)) = 1);;
assert (Z.export_length Z.zero = 1);;
assert (Z.export_length Z.one = 1);;
assert (Z.export_length (Z.of_int 127) = 1);;
assert (Z.export_length (Z.of_int 128) = 2);;
assert (Z.export_length (Z.of_int 32767) = 2);;
assert (Z.export_length (Z.of_int 32768) = 3);;

let expect_export_failure x buf pos len = (
	try
		Z.export ~order:`N x buf pos len;
		assert false
	with
	| Invalid_argument _ -> ()
);;

expect_export_failure Z.zero Bytes.empty 0 1;; (* overrun *)
expect_export_failure Z.zero Bytes.empty 1 0;; (* overrun *)
expect_export_failure Z.zero Bytes.empty ~-1 0;; (* negative pos *)
expect_export_failure Z.zero Bytes.empty ~-1 1;; (* negative pos *)

let expect_export order x buf pos len expect = (
	Z.export ~order:order x buf pos len;
	if buf <> expect then (
		Printf.printf "expect = \"%s\"; result = \"%s\"\n"
			(String.escaped (Bytes.to_string expect))
			(String.escaped (Bytes.to_string buf));
		flush stdout;
		assert false
	)
);;

expect_export `N Z.zero (Bytes.create 0) 0 0 Bytes.empty;;

expect_export `B (Z.of_int (-65536)) (Bytes.make 3 'x') 0 3
	(Bytes.of_string "\xff\x00\x00");;
expect_export `B (Z.of_int (-65536)) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\x00\x00");;
expect_export `B (Z.of_int (-257)) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\xfe\xff");;
expect_export `B (Z.of_int (-256)) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\xff\x00");;
expect_export `B (Z.of_int (-128)) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\xff\x80");;
expect_export `B (Z.of_int (-1)) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\xff\xff");;
expect_export `B (Z.of_int (-1)) (Bytes.make 1 'x') 0 1
	(Bytes.of_string "\xff");;
expect_export `B Z.zero (Bytes.make 1 'x') 0 1 (Bytes.of_string "\x00");;
expect_export `B Z.one (Bytes.make 1 'x') 0 1 (Bytes.of_string "\x01");;
expect_export `B (Z.of_int 127) (Bytes.make 1 'x') 0 1
	(Bytes.of_string "\x7f");;
expect_export `B (Z.of_int 127) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\x00\x7f");;
expect_export `B (Z.of_int 128) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\x00\x80");;
expect_export `B (Z.of_int 255) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\x00\xff");;
expect_export `B (Z.of_int 256) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\x01\x00");;
expect_export `B (Z.of_int 32767) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\x7f\xff");;
expect_export `B (Z.of_int 32768) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\x80\x00");;
expect_export `B (Z.of_int 32768) (Bytes.make 3 'x') 0 3
	(Bytes.of_string "\x00\x80\x00");;

expect_export `L (Z.of_int (-65536)) (Bytes.make 3 'x') 0 3
	(Bytes.of_string "\x00\x00\xff");;
expect_export `L (Z.of_int (-65536)) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\x00\x00");;
expect_export `L (Z.of_int (-257)) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\xff\xfe");;
expect_export `L (Z.of_int (-256)) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\x00\xff");;
expect_export `L (Z.of_int (-128)) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\x80\xff");;
expect_export `L (Z.of_int (-1)) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\xff\xff");;
expect_export `L (Z.of_int (-1)) (Bytes.make 1 'x') 0 1
	(Bytes.of_string "\xff");;
expect_export `L Z.zero (Bytes.make 1 'x') 0 1 (Bytes.of_string "\x00");;
expect_export `L Z.one (Bytes.make 1 'x') 0 1 (Bytes.of_string "\x01");;
expect_export `L (Z.of_int 127) (Bytes.make 1 'x') 0 1
	(Bytes.of_string "\x7f");;
expect_export `L (Z.of_int 127) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\x7f\x00");;
expect_export `L (Z.of_int 128) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\x80\x00");;
expect_export `L (Z.of_int 255) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\xff\x00");;
expect_export `L (Z.of_int 256) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\x00\x01");;
expect_export `L (Z.of_int 32767) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\xff\x7f");;
expect_export `L (Z.of_int 32768) (Bytes.make 2 'x') 0 2
	(Bytes.of_string "\x00\x80");;
expect_export `L (Z.of_int 32768) (Bytes.make 3 'x') 0 3
	(Bytes.of_string "\x00\x80\x00");;

let expect_import_failure buf pos len = (
	try
		let _: z = Z.import ~order:`N ~signed:false buf pos len in
		assert false
	with
	| Invalid_argument _ -> ()
);;

expect_import_failure Bytes.empty 0 1;; (* overrun *)
expect_import_failure Bytes.empty 1 0;; (* overrun *)
expect_import_failure Bytes.empty ~-1 0;; (* negative pos *)
expect_import_failure Bytes.empty ~-1 1;; (* negative pos *)

let expect_import order signed buf pos len expect = (
	let x = Z.import ~order ~signed buf pos len in
	if x <> expect then (
		Printf.printf "expect = \"%s\"; result = \"%s\"\n"
			(String.escaped (Z.to_string expect))
			(String.escaped (Bytes.to_string buf));
		flush stdout;
		assert false
	)
);;

expect_import `N false Bytes.empty 0 0 Z.zero;;
expect_import `N true Bytes.empty 0 0 Z.zero;;

let test_export_and_import x = (
	let len = Z.export_length x in
	let buf = Bytes.create len in
	Z.export ~order:`N x buf 0 len;
	let r = Z.import ~order:`N ~signed:true buf 0 len in
	if r <> x then (
		Printf.printf "x = %s; r = %s; buf = \"%s\"\n" (string_of_z x) (string_of_z r)
			(String.escaped (Bytes.to_string buf));
		flush stdout;
		assert false
	)
);;

test_export_and_import (Z.of_int (-32769));;
test_export_and_import (Z.of_int (-32768));;
test_export_and_import (Z.of_int (-257));;
test_export_and_import (Z.of_int (-256));;
test_export_and_import (Z.of_int (-129));;
test_export_and_import (Z.of_int (-128));;
test_export_and_import (Z.of_int (-1));;
test_export_and_import Z.zero;;
test_export_and_import Z.one;;
test_export_and_import (Z.of_int 127);;
test_export_and_import (Z.of_int 128);;
test_export_and_import (Z.of_int 255);;
test_export_and_import (Z.of_int 256);;
test_export_and_import (Z.of_int 32767);;
test_export_and_import (Z.of_int 32768);;

(* FR *)

let bit_eq (x: float) (y: float) = (
	x = y || (classify_float x = FP_nan && classify_float y = FP_nan)
);;

let single_check (x: float) (y: int32) = (
	let x1 = FR.bits_of_single (fr_of_float ~prec:24 ~mode:`N x) in
	if log then Printf.eprintf "%.8lx" x1;
	let y1 = float_of_fr ~mode:`N (FR.single_of_bits y) in
	if log then Printf.eprintf " %f\n" y1;
	x1 = y && bit_eq y1 x
);;

assert (single_check 0.0 0x00000000l);;
assert (single_check 1.0 0x3f800000l);;
assert (single_check 2.0 0x40000000l);;
assert (single_check 3.0 0x40400000l);;
assert (single_check 0.5 0x3f000000l);;
assert (single_check ~-.1.0 0xbf800000l);;
assert (single_check ~-.0.0 0x80000000l);;
assert (single_check ~-.1.25 0xbfa00000l);;
assert (single_check nan 0x7fc00000l || single_check nan 0xffc00000l);;
assert (single_check infinity 0x7f800000l);;
assert (single_check ~-.infinity 0xff800000l);;

let double_check (x: float) (y: int64) = (
	let x1 = FR.bits_of_double (fr_of_float ~prec:53 ~mode:`N x) in
	if log then Printf.eprintf "%.16Lx" x1;
	let y1 = float_of_fr ~mode:`N (FR.double_of_bits y) in
	if log then Printf.eprintf " %f\n" y1;
	x1 = y && bit_eq y1 x
);;

assert (double_check 0.0 0x0000000000000000L);;
assert (double_check 1.0 0x3ff0000000000000L);;
assert (double_check 2.0 0x4000000000000000L);;
assert (double_check 3.0 0x4008000000000000L);;
assert (double_check 0.5 0x3fe0000000000000L);;
assert (double_check ~-.1.0 0xbff0000000000000L);;
assert (double_check ~-.0.0 0x8000000000000000L);;
assert (double_check ~-.1.25 0xbff4000000000000L);;
assert (double_check nan 0x7ff8000000000000L
	|| double_check nan 0xfff8000000000000L);;
assert (double_check infinity 0x7ff0000000000000L);;
assert (double_check ~-.infinity 0xfff0000000000000L);;

let extended_check (x: float) (y: int64 * int) = (
	let (m, e) as x1 = FR.bits_of_extended (fr_of_float ~prec:64 ~mode:`N x) in
	if log then Printf.eprintf "%.4x:%.16Lx" e m;
	let y1 = float_of_fr ~mode:`N (FR.extended_of_bits y) in
	if log then Printf.eprintf " %f\n" y1;
	x1 = y && bit_eq y1 x
);;

assert (extended_check 0.0 (0x0000000000000000L, 0x0000));;
assert (extended_check 1.0 (0x8000000000000000L, 0x3fff));;
assert (extended_check 2.0 (0x8000000000000000L, 0x4000));;
assert (extended_check 3.0 (0xc000000000000000L, 0x4000));;
assert (extended_check 0.5 (0x8000000000000000L, 0x3ffe));;
assert (extended_check ~-.1.0 (0x8000000000000000L, 0xbfff));;
assert (extended_check ~-.0.0 (0x0000000000000000L, 0x8000));;
assert (extended_check ~-.1.25 (0xa000000000000000L, 0xbfff));;
assert (extended_check nan (0xc000000000000000L, 0x7fff)
	|| extended_check nan (0xc000000000000000L, 0xffff));;
assert (extended_check infinity (0x8000000000000000L, 0x7fff));;
assert (extended_check ~-.infinity (0x8000000000000000L, 0xffff));;

Printf.eprintf "ok\n";;
