open Gmp;;

external random_seed: unit -> int = "caml_sys_random_seed";;

type t;;

external create: unit -> t = "mlgmp_random_create";;
external create_lc_2exp: z -> int -> int -> t = "mlgmp_random_create_lc_2exp";;
external create_lc_2exp_size: int -> t = "mlgmp_random_create_lc_2exp_size";;
external create_mt: unit -> t = "mlgmp_random_create_mt";;
external seed_int: t -> int -> unit = "mlgmp_random_seed_int";;
external seed_z: t -> z -> unit = "mlgmp_random_seed_z";;
let make_int x = let r = create () in seed_int r x; r;;
let make_self_init () = make_int (random_seed ());;
let make_z x = let r = create () in seed_z r x; r;;
let make a =
	let rec loop a i seed =
		if i >= Array.length a then make_z seed else
		let n = Z.add_int (Z.shift_left seed 30) a.(i) in
		loop a (i + 1) n
	in
	loop a 0 Z.zero;;
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
external z: t -> z -> z = "mlgmp_random_z";;
external f_bits: t -> int -> f = "mlgmp_random_f_bits";;
external f: t -> prec:int -> f -> f = "mlgmp_random_f";;
