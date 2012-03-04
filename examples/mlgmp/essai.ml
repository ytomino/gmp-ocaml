open Gmp;;

for a = -10 to 10
do
  for b = -10 to 10
  do
    (if (compare
	  (Z.neg (Z.add (Z.from_int a) (Z.from_int b)))
	  (Z.from_int (- (a + b)))) <> 0
    then Printf.fprintf stderr "A: %d + %d\n" a b)

  done
done;;

for a = -10 to 10
do
  for b = 0 to 10
  do
    (if (compare
	  (Z.neg (Z.add_ui (Z.from_int a) b))
	  (Z.from_int (- (a + b)))) <> 0
    then Printf.fprintf stderr "B: %d + %d\n" a b)
  done
done;;

for a = -100 to 100
do
  for b = -100 to 100
  do
    if (b <> 0) then
    (let (q, r) = Z.cdiv_qr (Z.from_int a) (Z.from_int b) in
    (if (compare
	  (Z.add (Z.mul q (Z.from_int b)) r)
	  (Z.from_int a)) <> 0
    then Printf.fprintf stderr "C: cdiv_qr %d %d\n" a b);
    (let q' = Z.cdiv_q (Z.from_int a) (Z.from_int b) in
    if (Z.compare q q') <> 0
    then Printf.fprintf stderr "C: cdiv_q %d %d\n" a b);
    (let r' = Z.cdiv_r (Z.from_int a) (Z.from_int b) in
    if (Z.compare r r') <> 0
    then Printf.fprintf stderr "C: cdiv_r %d %d\n" a b))
  done
done;;

(if not (Z.equal (Z.mul_2exp (Z.from_int 5) 3) (Z.from_string "40"))
 then Printf.fprintf stderr "E: mul_2exp\n");;

(if not (Z.equal_int (Z.fdiv_q_2exp (Z.from_string "-41") 3) ( -6))
 then Printf.fprintf stderr "F: fdiv_q_2exp\n");;

(if (Z.sqrtrem (Z.pow_ui (Z.from_string_base ~base: 8 "23") 2)) <>
    ((Z.from_int 19), (Z.from_int 0))
 then Printf.fprintf stderr "G: pow_ui, sqrtrem\n");;

(if (Z.root (Z.pow_ui (Z.from_float 17.) 3) 3) <>
    (Z.from_int 17)
 then Printf.fprintf stderr "H: pow_ui, root\n");;

(if (Z.perfect_power_p (Z.from_int 179199))
|| not (Z.perfect_square_p (Z.from_int 4225))
then Printf.fprintf stderr "I: perfect powers\n");;

(let a = (Z.from_int 4935) and b = (Z.from_int 2563) in
let (g, s, t) = (Z.gcdext a b)
in if g <> (Z.add (Z.mul a s) (Z.mul b t))
   then Printf.fprintf stderr "J: gcdext\n");;

(let modulus = Z.from_string "4098969870980986751"
 and x = Z.from_string "1657867867854181" in
 let (Some y) = Z.inverse x modulus in
 if (Z.modulo (Z.mul x y) modulus) <> Z.one
 then Printf.fprintf stderr "K: inverse\n");;

(let prime = Z.nextprime (Z.from_string "109897328754895897328732816617973")
 in if not (Z.is_prime prime)
    then Printf.fprintf stderr "L: primes\n");;

(if (Z.remove (Z.from_int 16132319) (Z.from_int 7))
 <> ((Z.from_int 6719), 4)
 then Printf.fprintf stderr "M: remove factor\n");;

let fibo =
  let rec fib a b n =
    if n <= 1
    then a
    else fib b (a + b) (pred n)
  in fib 1 1;;

(let n=14 in
 if (Z.to_int (Z.fib_ui n)) <> (fibo n)
 then Printf.fprintf stderr "N: Fibonacci\n");;

let fact =
  let rec fac x n =
    if n <= 1
    then x
    else fac (x * n) (pred n)
  in fac 1;;

(let n=8 in
 if (Z.to_int (Z.fac_ui n)) <> (fact n)
 then Printf.fprintf stderr "N: Factorial\n");;

(let n=13 and k=4 in
 if (Z.to_float (Z.bin_ui ~n: (Z.from_int n) ~k: k)) <> 715.0
 then Printf.fprintf stderr "N: Binomial\n");;

 (if (Z.sgn (Z.sub (Z.from_int 10) (Z.from_int 13))) >= 0
 then Printf.fprintf stderr "O: Sign\n");;

(if (Z.bior (Z.from_int 17) (Z.from_int 5)) <> (Z.from_int 21)
 then Printf.fprintf stderr "P: Binary ops\n");;

(if (Z.scan0 (Z.from_int 87) 0) <> 3 ||
    (Z.scan1 (Z.from_int 0x1562) 9) <> 10
then Printf.fprintf stderr "Q: Scan\n");;

(let max = Z.from_int 5000000
 and rand_state = RNG.randinit (RNG.GMP_RAND_ALG_LC 100)
 and n = 100000
 and sum = ref Z.zero
 in for i=1 to n
    do
      sum := Z.add !sum (Z.urandomm rand_state max)
    done;
    let ecart = Z.abs (Z.sub (Z.fdiv_q_ui !sum n)
			 (Z.fdiv_q_2exp max 1)) in
    if (Z.cmp ecart (Z.from_int 100000)) > 0
    then Printf.fprintf stderr "R: Zrandom %a\n" Z.output ecart);;

(let q1 = Q.from_si 1 2
 and q2 = Q.from_si 1 3
 and q3 = Q.div (Q.from_z (Z.from_int 1)) (Q.from_z (Z.from_int 6))
 in if (not (Q.equal (Q.sub q1 q2) q3))
    || (Q.mul q1 q2) <> q3
    || (Q.to_string (Q.div q1 q2)) <> "3/2"
    then Printf.fprintf stderr "S: rationals\n");;

let marshal_identity (x : 'a) =
  ((Marshal.from_string (Marshal.to_string x []) 0) : 'a);;

let test_marshal equal x =
  not (equal (marshal_identity x) x);;

(if (test_marshal Z.equal (Z.from_string "190709907897091"))
|| (test_marshal Q.equal (Q.from_ints 1688781 173))
|| (test_marshal F.equal (F.from_string "580967.1347"))
then Printf.fprintf stderr "T: marshalling\n");;
