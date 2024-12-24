module Gmp = struct
	type rounding_mode = GMP_RNDN | GMP_RNDZ | GMP_RNDU | GMP_RNDD;;
	module RNG = struct
		type randalg_t = GMP_RAND_ALG_LC of int;;
		let randinit a =
			match a with
			| GMP_RAND_ALG_LC size -> Gmp.Random.create_lc_2exp_size size
	end;;
	module Z = struct
		type t = Gmp.Z.t;;
		let zero = Gmp.Z.zero;;
		let one = Gmp.Z.one;;
		let compare = Gmp.Z.compare;;
		let cmp = Gmp.Z.compare;;
		let cmp_si = Gmp.Z.compare_int;;
		let equal x y = Gmp.Z.compare x y = 0;;
		let equal_int x y = Gmp.Z.compare_int x y = 0;;
		let sgn x = Gmp.Z.compare x Gmp.Z.zero;;
		let neg = Gmp.Z.neg;;
		let abs = Gmp.Z.abs;;
		let add = Gmp.Z.add;;
		let add_ui = Gmp.Z.add_int;;
		let sub = Gmp.Z.sub;;
		let sub_ui = Gmp.Z.sub_int;;
		let mul = Gmp.Z.mul;;
		let mul_ui = Gmp.Z.mul_int;;
		let mul2exp x y = Gmp.Z.scale x ~base:2 ~exponent:y;;
		let mul_2exp x y = Gmp.Z.scale x ~base:2 ~exponent:y;;
		let cdiv_qr = Gmp.Z.cdiv;;
		let cdiv_q x y = fst (Gmp.Z.cdiv x y);;
		let cdiv_q_2exp x y =
			fst (Gmp.Z.cdiv x (Gmp.Z.int_pow_int ~base:2 ~exponent:y));;
		let cdiv_r x y = snd (Gmp.Z.cdiv x y);;
		let cdiv_r_ui x y = snd (Gmp.Z.cdiv x (Gmp.Z.of_int y));;
		let fdiv_q x y = fst (Gmp.Z.fdiv x y);;
		let fdiv_q_ui x y = fst (Gmp.Z.fdiv_int x y);;
		let fdiv_q_2exp x y = Gmp.Z.scale x ~base:2 ~exponent:~-y;;
		let modulo = Gmp.Z.modulo;;
		let dmod_ui x y = Gmp.Z.modulo x (Gmp.Z.of_int y);;
		let pow_ui base exponent = Gmp.Z.pow_int ~base ~exponent;;
		let pow_ui_ui base exponent = Gmp.Z.int_pow_int ~base ~exponent;;
		let powm base exponent m = Gmp.Z.pow_mod ~base ~exponent m;;
		let powm_ui base exponent m = Gmp.Z.pow_mod ~base ~exponent:(Gmp.Z.of_int exponent) m;;
		let sqrt = Gmp.Z.sqrt;;
		let sqrtrem = Gmp.Z.tsqrt;;
		let root x y = Gmp.Z.root ~nth:y x;;
		let perfect_power_p = Gmp.Z.is_perfect_power;;
		let perfect_square_p = Gmp.Z.is_perfect_square;;
		let is_probab_prime n reps = Gmp.Z.is_probably_prime n reps <> 0;;
		let is_prime n = Gmp.Z.is_probably_prime n 10 <> 0;;
		let nextprime = Gmp.Z.next_prime;;
		let gcdext = Gmp.Z.gcdext;;
		let inverse = Gmp.Z.invert;;
		let legendre = Gmp.Z.legendre;;
		let remove = Gmp.Z.remove;;
		let fac_ui = Gmp.Z.fac_int;;
		let bin_ui ~n ~k = Gmp.Z.bin_int n k;;
		let fib_ui = Gmp.Z.fib_int;;
		let bior = Gmp.Z.logor;;
		let scan0 = Gmp.Z.scan0;;
		let scan1 = Gmp.Z.scan1;;
		let from_int = Gmp.Z.of_int;;
		let from_float = Gmp.z_of_truncated_float;;
		let from_string_base = Gmp.Z.of_based_string;;
		let from_string x = Gmp.Z.of_string x;;
		let to_int = Gmp.Z.to_int;;
		let int_from = Gmp.Z.to_int;;
		let to_float = Gmp.Z.to_float;;
		let to_string_base = Gmp.Z.to_based_string;;
		let to_string = Gmp.Z.to_string;;
		let urandomm = Gmp.Random.z;;
		let output oc n = output_string oc (Gmp.Z.to_string n);;
	end;;
	module Q = struct
		type t = Gmp.Q.t;;
		let compare = Gmp.Q.compare;;
		let cmp = Gmp.Q.compare;;
		let cmp_ui x n d = Gmp.Q.compare x (Gmp.Q.make_int n d);;
		let equal x y = Gmp.Q.compare x y = 0;;
		let is_zero x = Gmp.Q.compare x Gmp.Q.zero = 0;;
		let sgn x = Gmp.Q.compare x Gmp.Q.zero;;
		let neg = Gmp.Q.neg;;
		let add = Gmp.Q.add;;
		let sub = Gmp.Q.sub;;
		let mul = Gmp.Q.mul;;
		let div = Gmp.Q.div;;
		let inv x = Gmp.Q.make_z (Gmp.Q.den x) (Gmp.Q.num x);;
		let get_num = Gmp.Q.num;;
		let get_den = Gmp.Q.den;;
		let from_int = Gmp.Q.of_int;;
		let from_si = Gmp.Q.make_int;;
		let from_ints = Gmp.Q.make_int;;
		let from_z = Gmp.Q.of_z;;
		let from_zs = Gmp.Q.make_z;;
		let from_float = Gmp.Q.of_float;;
		let to_float = Gmp.Q.to_float;;
		let float_from = Gmp.Q.to_float;;
		let to_string = Gmp.Q.to_string;;
		let sprintf () = to_string;;
	end;;
	module F = struct
		let default_prec = 120;;
		module Default_F =
			Gmp.F.Make (struct
				let prec = default_prec;;
			end);;
		let zero = Default_F.zero;;
		let compare = Gmp.F.compare;;
		let equal x y = Gmp.F.nearly_equal 90 x y;;
		let eq ~prec x y = Gmp.F.nearly_equal prec x y;;
		let sgn x = Gmp.F.compare x Default_F.zero;;
		let neg = Default_F.neg;;
		let abs = Default_F.abs;;
		let add = Default_F.add;;
		let add_ui = Default_F.add_int;;
		let sub = Default_F.sub;;
		let sub_ui = Default_F.sub_int;;
		let mul = Default_F.mul;;
		let mul_ui = Default_F.mul_int;;
		let floor = Default_F.floor;;
		let from_int = Default_F.of_int;;
		let from_float = Default_F.of_float;;
		let from_string_base = Default_F.of_based_string;;
		let from_string = Default_F.of_string;;
		let to_float = Gmp.F.to_float;;
		let to_string = Gmp.F.to_string;;
		let urandomb ~state ~nbits = Gmp.Random.f_bits state nbits;;
	end;;
	module FR = struct
		let default_prec = 120;;
		module Default_FR =
			Mpfr.FR.Make (struct
				let prec = default_prec;;
				let mode = `N;;
			end);;
		let compare = Mpfr.FR.compare;;
		let eq ~prec x y = Mpfr.FR.nearly_equal prec x y;;
		let sgn x = Mpfr.FR.compare x Default_FR.zero;;
		let neg = Default_FR.neg;;
		let abs = Default_FR.abs;;
		let add = Default_FR.add;;
		let add_ui = Default_FR.add_int;;
		let sub = Default_FR.sub;;
		let sub_ui = Default_FR.sub_int;;
		let mul = Default_FR.mul;;
		let mul_ui = Default_FR.mul_int;;
		let pow_ui base exponent = Default_FR.pow_int ~base ~exponent;;
		let sqrt = Default_FR.sqrt;;
		let exp = Default_FR.exp;;
		let exp2 x = Default_FR.pow (Default_FR.of_int 2) x;;
		let floor = Default_FR.floor;;
		let sin = Default_FR.sin;;
		let acosh = Default_FR.acosh;;
		let from_int = Default_FR.of_int;;
		let from_float = Default_FR.of_float;;
		let from_string_base = Default_FR.of_based_string;;
		let from_string = Default_FR.of_string;;
		let to_float = Default_FR.to_float;;
		let to_string_exp_base_digits ~mode ~base ~digits x =
			let mode =
				match mode with
				| GMP_RNDN -> `N
				| GMP_RNDZ -> `Z
				| GMP_RNDU -> `U
				| GMP_RNDD -> `D
			in
			Mpfr.fr_get_str ~mode ~base digits x;;
		let to_string_base_digits ~mode ~base ~digits x =
			let mantissa, exponent = to_string_exp_base_digits ~mode ~base ~digits x in
			let i = (if sgn x < 0 then 1 else 0) in
			let lm = String.length mantissa in
			(if lm > 1 then
				let tmp = Bytes.create (succ lm) in
				Bytes.blit (Bytes.unsafe_of_string mantissa) 0 tmp 0 (1+i);
				Bytes.blit (Bytes.unsafe_of_string mantissa) (1+i) tmp (2+i) ((pred lm)-i);
				Bytes.set tmp (1+i) '.';
				Bytes.unsafe_to_string tmp
			else mantissa)
			^ (if base <= 10 then "E" else "@")
			^ (string_of_int (pred exponent));;
		let to_string = to_string_base_digits ~mode:GMP_RNDN ~base:10 ~digits:10;;
	end;;
	exception Unimplemented of string;;
end;;
