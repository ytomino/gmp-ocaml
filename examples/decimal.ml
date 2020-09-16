(* Demonstration for emulating some decimal floating-point type *)

open Gmp;;

module Decimal = struct
	type t = Z.t * int;;
	let canonicalize (x_val, _ as x: t) = (
		if Z.compare_int x_val 0 = 0 then Z.zero, 0 else
		let rec loop (x_val, x_exp as x: t) = (
			let q, r = Z.tdiv x_val (Z.of_int 10) in
			if Z.compare_int r 0 <> 0 then x else
			loop (q, x_exp + 1)
		) in
		loop x
	);;
	let to_common (x_val, x_exp: t) (y_val, y_exp: t) = (
		let exp' = min x_exp y_exp in
		let x_val' = Z.scale ~base:10 ~exponent:(x_exp - exp') x_val in
		let y_val' = Z.scale ~base:10 ~exponent:(y_exp - exp') y_val in
		x_val', y_val', exp'
	);;
	let make_sign (f: Z.t -> Z.t) (x_val, x_exp: t) = (
		f x_val, x_exp
	);;
	let make_add (f: Z.t -> Z.t -> Z.t) (x: t) (y: t) = (
		let x_val', y_val', exp' = to_common x y in
		canonicalize ((f x_val' y_val'), exp')
	);;
	let zero = Z.zero, 0;;
	let one = Z.one, 0;;
	let compare (x: t) (y: t) = (
		let x_val', y_val', _ = to_common x y in
		Z.compare x_val' y_val'
	);;
	let neg = make_sign Z.neg;;
	let abs = make_sign Z.abs;;
	let add = make_add Z.add;;
	let sub = make_add Z.sub;;
	let mul (x_val, x_exp: t) (y_val, y_exp: t) = (
		canonicalize (Z.mul x_val y_val, x_exp + y_exp)
	);;
	let div (x_val, x_exp: t) (y_val, y_exp: t) = (
		let prec = 2 * 38 in (* double of the decimal precision of _Decimal128 *)
		let x_val' = Z.scale ~base:10 ~exponent:prec x_val in
		let x_exp' = x_exp - prec in
		canonicalize (Z.div x_val' y_val, x_exp' - y_exp)
	);;
	let scale ~(base: int) ~(exponent: int) (x_val, x_exp as x: t) = (
		if base = 10 then x_val, x_exp + exponent else
		if exponent > 0 then canonicalize (Z.scale ~base ~exponent x_val, x_exp) else
		div x (Z.int_pow_int ~base ~exponent:(~-exponent), 0)
	);;
	let of_based_string ~(base: int) (x: string) = (
		begin match String.index_opt x '.' with
		| None ->
			canonicalize (Z.of_based_string ~base x, 0)
		| Some p ->
			let n = p + 1 in
			let e = String.length x - n in
			let v = Z.of_based_string ~base (String.sub x 0 p ^ String.sub x n e) in
			if base = 10 then canonicalize (v, ~-e) else
			div (v, 0) (Z.int_pow_int ~base ~exponent:e, 0)
		end
	);;
	let of_string = of_based_string ~base:10;;
	let to_based_string ~(base: int) (x_val, x_exp: t) = (
		if x_exp >= 0 then (
			Z.to_based_string ~base (Z.scale ~base:10 ~exponent:x_exp x_val)
		) else if base = 10 then (
			let s = Z.to_based_string ~base x_val in
			let length = String.length s in
			let p = length + x_exp in
			if p > 0 then String.sub s 0 p ^ "." ^ String.sub s p (length - p) else
			"0." ^ String.make ~-p '0' ^ s
		) else (
			let d = Z.scale ~base:10 ~exponent:~-x_exp Z.one in
			let b = Buffer.create 0 in
			let a =
				if Z.compare_int x_val 0 >= 0 then x_val else (
					Buffer.add_char b '-';
					Z.neg x_val
				)
			in
			let q, r = Z.tdiv a d in
			Buffer.add_string b (Z.to_based_string ~base q);
			Buffer.add_char b '.';
			let rec loop (limit: int) (n: Z.t) = (
				if limit = 0 || Z.compare_int n 0 = 0 then Buffer.contents b else
				let n = Z.mul_int n base in
				let q, r = Z.tdiv n d in
				Buffer.add_char b (Char.chr (Char.code '0' + Z.to_int q));
				loop (limit - 1) r
			) in
			loop 114 r (* the binary precision of _Decimal128 *)
		)
	);;
	let to_string = to_based_string ~base:10;;
	let of_int (x: int) = canonicalize (Z.of_int x, 0);;
	let of_z (x: Z.t) = canonicalize (x, 0);;
end;;

let x, y, exp = Decimal.to_common (Z.of_int 2, 5) (Z.of_int 3, 4) in
assert (x = Z.of_int 20 && y = Z.of_int 3 && exp = 4);;
let x, y, exp = Decimal.to_common (Z.of_int 2, 4) (Z.of_int 3, 5) in
assert (x = Z.of_int 2 && y = Z.of_int 30 && exp = 4);;

assert (Decimal.compare (Z.of_int 2, 5) (Z.of_int 3, 4) > 0);;
assert (Decimal.compare (Z.of_int 2, 4) (Z.of_int 3, 4) < 0);;
assert (Decimal.compare (Z.of_int 2, 4) (Z.of_int 3, 5) < 0);;
assert (Decimal.compare (Z.of_int 20, 4) (Z.of_int 2, 5) = 0);;

assert (Decimal.neg Decimal.one = (Z.of_int ~-1, 0));;
assert (Decimal.neg (Z.of_int ~-1, 0) = Decimal.one);;

assert (Decimal.abs Decimal.one = Decimal.one);;
assert (Decimal.abs (Z.of_int ~-1, 0) = Decimal.one);;

assert (Decimal.add (Z.of_int 2, 5) (Z.of_int 3, 4) = (Z.of_int 23, 4));;
assert (Decimal.add (Z.of_int 15, 1) (Z.of_int 50, 0) = (Z.of_int 2, 2));;

assert (Decimal.sub (Z.of_int 2, 5) (Z.of_int 3, 4) = (Z.of_int 17, 4));;
assert (Decimal.sub (Z.of_int 15, 1) (Z.of_int 50, 0) = (Z.one, 2));;
assert (Decimal.sub Decimal.one Decimal.one = Decimal.zero);;

assert (Decimal.mul (Z.of_int 2, ~-1) (Z.of_int 3, 1) = (Z.of_int 6, 0));;
assert (Decimal.mul (Z.of_int 2, ~-1) (Z.of_int 5, 1) = (Z.one, 1));;

assert (Decimal.div Decimal.one (Z.of_int 2, 0) = (Z.of_int 5, ~-1));;
assert (Decimal.div (Z.one, 2) (Z.of_int 2, 1) = (Z.of_int 5, 0));;

assert (Decimal.scale ~base:10 ~exponent:1 (Z.of_int 2, 5) = (Z.of_int 2, 6));;
assert (Decimal.scale ~base:5 ~exponent:1 (Z.of_int 2, 5) = (Z.of_int 1, 6));;
assert (
	Decimal.scale ~base:5 ~exponent:~-1 (Z.of_int 2, 5) = (Z.of_int 4, 4)
);;

assert (Decimal.of_string "100" = (Z.one, 2));;
assert (Decimal.of_string "0.01" = (Z.one, ~-2));;
assert (Decimal.of_string "2.3" = (Z.of_int 23, ~-1));;

assert (Decimal.of_based_string ~base:2 "1010" = (Z.one, 1));;
assert (Decimal.of_based_string ~base:2 "1.1" = (Z.of_int 15, ~-1));;
assert (Decimal.of_based_string ~base:2 "0.11" = (Z.of_int 75, ~-2));;
assert (Decimal.of_based_string ~base:2 "-1010" = (Z.of_int ~-1, 1));;
assert (Decimal.of_based_string ~base:2 "-1.1" = (Z.of_int ~-15, ~-1));;
assert (Decimal.of_based_string ~base:2 "-0.11" = (Z.of_int ~-75, ~-2));;

assert (Decimal.to_string (Z.of_int 2, 1) = "20");;
assert (Decimal.to_string (Z.of_int 2, 0) = "2");;
assert (Decimal.to_string (Z.of_int 2, ~-1) = "0.2");;
assert (Decimal.to_string (Z.of_int 2, ~-2) = "0.02");;
assert (Decimal.to_string (Z.of_int 23, ~-1) = "2.3");;

assert (Decimal.to_based_string ~base:2 (Z.one, 1) = "1010");;
assert (Decimal.to_based_string ~base:2 (Z.of_int 15, ~-1) = "1.1");;
assert (Decimal.to_based_string ~base:2 (Z.of_int 75, ~-2) = "0.11");;
assert (
	String.sub (Decimal.to_based_string ~base:3 (Z.one, ~-1)) 0 6 = "0.0022"
);;
assert (Decimal.to_based_string ~base:2 (Z.of_int ~-1, 1) = "-1010");;
assert (Decimal.to_based_string ~base:2 (Z.of_int ~-15, ~-1) = "-1.1");;
assert (Decimal.to_based_string ~base:2 (Z.of_int ~-75, ~-2) = "-0.11");;
assert (
	String.sub (Decimal.to_based_string ~base:3 (Z.of_int ~-1, ~-1)) 0 7
		= "-0.0022"
);;

Printf.eprintf "ok\n";;
