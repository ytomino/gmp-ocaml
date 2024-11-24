open Gmp;;

let verbose = false;;

let state = Random.make_self_init ();;

(* float_exclusive *)

let prec = 3;;
let bound = 1 lsl prec;;

let try_once f of_int to_int nums trial_count =
	incr trial_count;
	let x = f state ~prec (of_int ~prec bound) in
	let x_int = to_int x in
	assert (of_int ~prec x_int = x);
	nums.(x_int) <- nums.(x_int) + 1;
	x_int;;

let try_mask f of_int to_int mask_all nums trial_count =
	let mask = ref 0 in
	while !mask <> mask_all do
		let n = try_once f of_int to_int nums trial_count in
		mask := !mask lor (1 lsl n);
	done;;

let try_1024 f of_int to_int nums trial_count =
	for i = !trial_count to 1023 do
		let _: int = try_once f of_int to_int nums trial_count in
		()
	done;;

let print_nums nums =
	for i = 0 to Array.length nums - 1 do
		if i > 0 then (
			prerr_string "; "
		);
		prerr_int i;
		prerr_string ": ";
		prerr_int nums.(i)
	done;
	prerr_newline ();;

let float_of_int ~prec = float_of_int;;

let do_float_exclusive int64 state ~prec n =
	let bound = Int64.sub (Int64.shift_left 1L prec) 1L in
	let r = Int64.add (int64 state bound) 1L in
	let r = ldexp (Int64.to_float r) ~-prec in
	n *. r;;
	(* same algorithm as float_exclusive *)

let float_bits_exclusive = do_float_exclusive Random.int64;;

let count = ref 0 in
let nums = Array.make (bound + 1) 0 in
let mask_all = (1 lsl bound - 1) lxor 1 in
try_mask float_bits_exclusive float_of_int int_of_float mask_all nums count;
assert (nums.(0) = 0);
assert (nums.(bound) = 0);
if verbose then (
	try_1024 float_bits_exclusive float_of_int int_of_float nums count;
	assert (nums.(0) = 0);
	assert (nums.(bound) = 0);
	prerr_endline "float_exclusive";
	print_nums nums
);;

let smallest = 0x1p-53 in 
assert (
	let r = do_float_exclusive (fun _ _ -> 0L) () ~prec:53 1. in
	r > 0. && r -. smallest = 0.
);
assert (
	let r = do_float_exclusive (fun _ bound -> Int64.pred bound) () ~prec:53 1. in
	r < 1. && r +. smallest = 1.
);;

(* float_inclusive *)

let do_float_inclusive int64 state ~prec n =
	let bound = Int64.add (Int64.shift_left 1L prec) 1L in
	let r = int64 state bound in
	let r = ldexp (Int64.to_float r) ~-prec in
	n *. r;;
	(* same algorithm as float_inclusive *)

let float_bits_inclusive = do_float_inclusive Random.int64;;

let count = ref 0 in
let nums = Array.make (bound + 1) 0 in
let mask_all = 1 lsl (bound + 1) - 1 in
try_mask float_bits_inclusive float_of_int int_of_float mask_all nums count;
if verbose then (
	try_1024 float_bits_inclusive float_of_int int_of_float nums count;
	prerr_endline "float_inclusive";
	print_nums nums
);;

assert (
	let r = do_float_inclusive (fun _ _ -> 0L) () ~prec:53 1. in
	r = 0.
);
assert (
	let r = do_float_inclusive (fun _ bound -> Int64.pred bound) () ~prec:53 1. in
	r = 1.
);;

(* f_exclusive *)

let one = F.one ~prec;;
let int_of_f x = int_of_z (z_of_truncated_f x);;

let count = ref 0 in
let nums = Array.make (bound + 1) 0 in
let mask_all = (1 lsl bound - 1) lxor 1 in
try_mask Random.f_exclusive f_of_int int_of_f mask_all nums count;
assert (nums.(0) = 0);
assert (nums.(bound) = 0);
if verbose then (
	try_1024 Random.f_exclusive f_of_int int_of_f nums count;
	assert (nums.(0) = 0);
	assert (nums.(bound) = 0);
	prerr_endline "f_exclusive";
	print_nums nums
);;

let do_f_exclusive z state ~prec n =
	let bound = Z.sub_int (Z.int_pow_int ~base:2 ~exponent:prec) 1 in
	let r = Z.add_int (z state bound) 1 in
	let r = F.ldexp ~prec (f_of_z ~prec r) ~-prec in
	F.mul ~prec n r;;
	(* same algorithm as Gmp.Random.f_exclusive *)

for prec = 2 to 53 do
	let smallest = F.int_pow_int ~prec ~base:2 ~exponent:~-prec in 
	assert (
		let r = do_f_exclusive (fun _ _ -> Z.zero) () ~prec one in
		F.compare_int r 0 > 0 && F.compare_int (F.sub ~prec r smallest) 0 = 0
	);
	assert (
		let r = do_f_exclusive (fun _ bound -> Z.sub_int bound 1) () ~prec one in
		F.compare_int r 1 < 0 && F.compare_int (F.add ~prec r smallest) 1 = 0
	)
done;;

(* f_inclusive *)

let count = ref 0 in
let nums = Array.make (bound + 1) 0 in
let mask_all = 1 lsl (bound + 1) - 1 in
try_mask Random.f_inclusive f_of_int int_of_f mask_all nums count;
if verbose then (
	try_1024 Random.f_inclusive f_of_int int_of_f nums count;
	prerr_endline "f_inclusive";
	print_nums nums
);;

let do_f_inclusive z state ~prec n =
	let bound = Z.add_int (Z.int_pow_int ~base:2 ~exponent:prec) 1 in
	let r = z state bound in
	let r = F.ldexp ~prec (f_of_z ~prec r) ~-prec in
	F.mul ~prec n r;;
	(* same algorithm as Gmp.Random.f_inclusive *)

for prec = 2 to 53 do
	assert (
		let r = do_f_inclusive (fun _ _ -> Z.zero) () ~prec one in
		F.compare_int r 0 = 0
	);
	assert (
		let r = do_f_inclusive (fun _ bound -> Z.sub_int bound 1) () ~prec one in
		F.compare_int r 1 = 0
	)
done;;

prerr_endline "ok";;
