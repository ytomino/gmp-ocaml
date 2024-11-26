open Gmp;;

external random_seed: unit -> int array = "caml_sys_random_seed";;

type t;;

external create: unit -> t = "mlgmp_random_create";;
external create_lc_2exp: z -> int -> int -> t = "mlgmp_random_create_lc_2exp";;
external create_lc_2exp_size: int -> t = "mlgmp_random_create_lc_2exp_size";;
external create_mt: unit -> t = "mlgmp_random_create_mt";;
external seed_int: t -> int -> unit = "mlgmp_random_seed_int";;
external seed_z: t -> z -> unit = "mlgmp_random_seed_z";;
let make_int x = let r = create () in seed_int r x; r;;
let make_z x = let r = create () in seed_z r x; r;;
let make: int array -> t =
	let rec loop i seed a =
		if i >= Array.length a then make_z seed else
		let n = Z.add_int (Z.shift_left seed 30) a.(i) in
		loop (i + 1) n a
	in
	loop 0 Z.zero;;
let make_self_init () = make (random_seed ());;
external copy: t -> t = "mlgmp_random_copy";;
external int_bits: t -> int -> int = "mlgmp_random_int_bits";;
let bits state = int_bits state 30;;
external int: t -> int -> int = "mlgmp_random_int";;
external int32: t -> int32 -> int32 = "mlgmp_random_int32";;
external int64: t -> int64 -> int64 = "mlgmp_random_int64";;
external nativeint: t -> nativeint -> nativeint = "mlgmp_random_nativeint";;
let bool state = int_bits state 1 <> 0;;
external float_bits: t -> int -> float = "mlgmp_random_float_bits";;
let float state n = n *. float_bits state 53;;
let float_exclusive state n =
	let bound = Int64.sub (Int64.shift_left 1L 53) 1L in
	let r = Int64.add (int64 state bound) 1L in (* [1,2**prec-1] *)
	let r = ldexp (Int64.to_float r) ~-53 in (* (0,1) *)
	n *. r;;
let float_inclusive state n =
	let bound = Int64.add (Int64.shift_left 1L 53) 1L in
	let r = int64 state bound in (* [0,2**prec] *)
	let r = ldexp (Int64.to_float r) ~-53 in (* [0,1] *)
	n *. r;;
external z: t -> z -> z = "mlgmp_random_z";;
external f_bits: t -> int -> f = "mlgmp_random_f_bits";;
external f: t -> prec:int -> f -> f = "mlgmp_random_f";;
let f_exclusive state ~prec n =
	let bound = Z.sub_int (Z.int_pow_int ~base:2 ~exponent:prec) 1 in
	let r = Z.add_int (z state bound) 1 in (* [1,2**prec-1] *)
	let r = F.ldexp ~prec (f_of_z ~prec r) ~-prec in (* (0,1) *)
	F.mul ~prec n r;;
let f_inclusive state ~prec n =
	let bound = Z.add_int (Z.int_pow_int ~base:2 ~exponent:prec) 1 in
	let r = z state bound in (* [0,2**prec] *)
	let r = F.ldexp ~prec (f_of_z ~prec r) ~-prec in (* [0,1] *)
	F.mul ~prec n r;;
