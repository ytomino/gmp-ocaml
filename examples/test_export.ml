open Gmp;;

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

let expect_export_failure x buf pos len =
	try
		Z.export ~order:`N x buf pos len;
		assert false
	with Failure _ -> ();;

expect_export_failure Z.zero Bytes.empty 0 1;; (* overrun *)
expect_export_failure Z.zero Bytes.empty 1 0;; (* overrun *)

let expect_export order x buf pos len expect =
	Z.export ~order:order x buf pos len;
	if buf <> expect then (
		Printf.printf "expect = \"%s\"; result = \"%s\"\n"
			(String.escaped (Bytes.to_string expect))
			(String.escaped (Bytes.to_string buf));
		flush stdout;
		assert false
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

let test_export_and_import x =
	let len = Z.export_length x in
	let buf = Bytes.create len in
	Z.export ~order:`N x buf 0 len;
	let r = Z.import ~order:`N ~signed:true buf 0 len in
	if r <> x then (
		Printf.printf "x = %s; r = %s; buf = \"%s\"\n" (string_of_z x) (string_of_z r)
			(String.escaped (Bytes.to_string buf));
		flush stdout;
		assert false
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

Printf.eprintf "ok\n";;
