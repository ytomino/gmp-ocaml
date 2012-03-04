open Gmp;;

assert ((Z.from_int 578) = (Z.from_string_base ~base: 10 "578"));
assert ((Z.from_int 578) = (Z.from_float 578.));
assert ((Z.to_string_base ~base: 10 (Z.from_int 578)) = "578");
assert ((Z.to_int (Z.from_int 578)) = 578);
assert ((Z.to_float (Z.from_int 578)) = 578.);
assert ((Z.add (Z.from_int 45) (Z.from_int (- 51))) = (Z.from_int (- 6)));
assert ((Z.sub (Z.from_int 45) (Z.from_int (- 51))) = (Z.from_int 96));
assert ((Z.mul (Z.from_int 45) (Z.from_int (- 51))) = (Z.from_int (- 2295)));
assert ((Z.add_ui (Z.from_int 45) 37) = (Z.from_int 82));
assert ((Z.sub_ui (Z.from_int 45) 37) = (Z.from_int 8));
assert ((Z.to_int (Z.mul_ui (Z.from_int 45) 37)) = 1665);
assert ((Z.neg (Z.from_int 45)) = (Z.from_int (- 45)));
assert ((Z.abs (Z.from_int (- 45))) = (Z.from_int 45));
assert ((Z.modulo (Z.from_int 6502) (Z.from_int 45)) = (Z.from_int 22));
assert ((Z.mul_2exp (Z.from_int 45) 2) = (Z.from_int 180));
assert ((Z.fdiv_q_2exp (Z.from_int 45) 2) = (Z.from_int 11));
assert ((Z.powm (Z.from_int 3) (Z.from_int 57) (Z.from_int 4))
      = (Z.from_int 3));
assert ((Z.powm_ui (Z.from_int 3) 57 (Z.from_int 4))
      = (Z.from_int 3));
assert ((Z.cdiv_qr (Z.from_int 3) (Z.from_int 2)) =
	((Z.from_int 2), (Z.from_int (-1))));
assert (Z.equal (Z.mul2exp (Z.from_int 3) 2) (Z.from_int 12));
assert (Z.equal (Z.cdiv_q_2exp (Z.from_int 13) 1) (Z.from_int 7));
assert (Z.perfect_power_p (Z.pow_ui (Z.from_int 13) 45));
assert (Z.perfect_square_p ( Z.pow_ui (Z.from_string "134897980976978091") 2));
assert ((Z.legendre (Z.from_int 4) (Z.from_int 23)) = 1);
assert ((Z.legendre (Z.from_int 5) (Z.from_int 23)) = -1);
assert (Z.is_probab_prime (Z.nextprime (Z.from_string "1348913489791348979809769780980976978097980976978098097980979809809")) 30);


(* TODO: the rest of Z is missing *)

begin
assert ((Q.from_int 578) = (Q.from_z (Z.from_string_base ~base: 10 "578")));
let one = Q.from_int 1 in
let two = Q.add one one in
let three = Q.add one two in
let six = Q.mul two three in
let a = Q.inv two
and b = Q.div one three in
let c = Q.sub a b in
assert ((Q.from_float 1.5) = (Q.div three two));
assert ((Q.to_float (Q.div three two)) = 1.5);
assert (c = (Q.div one six));
assert ((Q.neg c) = (Q.neg (Q.div one six)));
assert ((Q.get_den c) = (Q.get_num six));
assert ((Q.cmp_ui a 1 2) = 0);
assert ((Q.compare (Q.inv b) (Q.from_ints 3 1)) = 0);
assert ((Q.compare b (Q.from_ints 1 3)) = 0);
assert ((Q.sgn a) > 0);
assert (not (Q.is_zero a));
assert (Q.is_zero (Q.sub c (Q.from_zs (Z.from_int 1) (Z.from_int 6))));
assert (Z.equal (Q.get_den c) (Z.from_int 6));
assert (Z.equal (Q.get_den c) (Q.get_num six));
assert (Q.equal c (Q.from_ints 1 6));
assert ((Q.to_string one) = "1");
assert ((Printf.sprintf "%a" Q.sprintf c) = "1/6");
end;

begin
assert ((F.from_int 578) = (F.from_string_base ~base: 10 "578"));
assert ((F.from_int 578) = (F.from_float 578.));
assert ((float_of_string (F.to_string (F.from_int 578))) = 578.);
assert ((F.to_float (F.from_int 578)) = 578.);

assert ((F.add (F.from_int 45) (F.from_int (- 51))) = (F.from_int (- 6)));
assert ((F.sub (F.from_int 45) (F.from_int (- 51))) = (F.from_int 96));
assert ((F.mul (F.from_int 45) (F.from_int (- 51))) = (F.from_int (- 2295)));
assert ((F.add_ui (F.from_int 45) 37) = (F.from_int 82));
assert ((F.sub_ui (F.from_int 45) 37) = (F.from_int 8));
assert ((F.to_float (F.mul_ui (F.from_int 45) 37)) = 1665.);
assert ((F.neg (F.from_int 45)) = (F.from_int (- 45)));
assert ((F.abs (F.from_int (- 45))) = (F.from_int 45));
assert ((F.floor (F.from_string "-2.2947E3")) = (F.from_int (- 2295)));
assert ((F.compare (F.from_string "478.99") (F.from_float 478.67)) > 0);
assert ((F.sgn (F.from_string "-478.99")) < 0);
assert (F.eq (F.from_string "478.99") (F.from_float 478.99) ~prec: 6);
end;

begin
try
assert ((FR.from_int 578) = (FR.from_string_base ~base: 10 "578"));
assert ((FR.from_int 578) = (FR.from_float 578.));
assert ((float_of_string (FR.to_string (FR.from_int 578))) = 578.);
assert ((FR.to_float (FR.from_int 578)) = 578.);
assert ((FR.add (FR.from_int 45) (FR.from_int (- 51))) = (FR.from_int (- 6)));
assert ((FR.sub (FR.from_int 45) (FR.from_int (- 51))) = (FR.from_int 96));
assert ((FR.mul (FR.from_int 45)(FR.from_int (- 51)))=(FR.from_int (- 2295)));
assert ((FR.add_ui (FR.from_int 45) 37) = (FR.from_int 82));
assert ((FR.sub_ui (FR.from_int 45) 37) = (FR.from_int 8));
assert ((FR.to_float (FR.mul_ui (FR.from_int 45) 37)) = 1665.);
assert ((FR.neg (FR.from_int 45)) = (FR.from_int (- 45)));
assert ((FR.abs (FR.from_int (- 45))) = (FR.from_int 45));
assert ((FR.floor (FR.from_string "-2.2947E3")) = (FR.from_int (- 2295)));
assert ((FR.compare (FR.from_string "478.99") (FR.from_float 478.67)) > 0);
assert ((FR.sgn (FR.from_string "-478.99")) < 0);
assert (FR.eq (FR.from_string "478.99") (FR.from_float 478.99) ~prec: 6);
assert ((FR.to_string_base_digits ~base:10 ~mode:GMP_RNDN ~digits:30 (FR.sin (FR.from_int 3))) = "1.41120008059867222100744802808E-1"); (*verified w/ Maple*)
assert ((FR.to_string_base_digits ~base:10 ~mode:GMP_RNDN ~digits:30 (FR.acosh (FR.from_int 3))) = "1.76274717403908605046521864996E0"); (*verified w/ Maple*)
assert ((FR.to_string_base_digits ~base:10 ~mode:GMP_RNDN
  ~digits:30 (FR.sqrt (FR.from_int 5))) =
  "2.23606797749978969640917366873E0"); (* verified w/ Mathematica *)
assert ((FR.to_string_base_digits ~base:10 ~mode:GMP_RNDN
  ~digits:30 (FR.exp (FR.from_int 5))) =
  "1.48413159102576603421115580041E2"); (* verified w/ Mathematica *)
assert ((FR.to_string_base_digits ~base:10 ~mode:GMP_RNDN
  ~digits:30 (FR.exp2 (FR.from_float 2.5))) =
  "5.65685424949238019520675489684E0"); (* verified w/ Mathematica *)
assert((FR.to_string (FR.pow_ui (FR.from_float 2.1) 6)) =
       "8.576612100E1"); (* verified w/ Mathematica *)

with Unimplemented _ -> ()
end;;

Gc.full_major ();;

