open Gmp
open Format

let rng=RNG.randinit (RNG.GMP_RAND_ALG_LC 100);;

let random_matrix l c =
  let a = Array.create_matrix l c F.zero in
  for i=0 to pred l
  do
    for j=0 to pred c
    do
      a.(i).(j) <- F.urandomb ~state: rng ~nbits: 40
    done
  done;
  a

let matrix_mul a b =
  let m = Array.length a
  and l = Array.length a.(0)
  and l' = Array.length b
  and n = Array.length b.(0) in
  assert (l = l');
  let c = Array.create_matrix m n F.zero in
  for i=0 to pred m
  do
    for j=0 to pred n
    do
      let z = ref F.zero in (* missing in FR *)
      for k=0 to pred l
      do
        z := F.add !z  (F.mul a.(i).(k) b.(k).(j))
      done;
      a.(i).(j) <- !z
    done
  done;
  a;;

let pp_matrix formatter a =
  pp_open_vbox formatter 0;
  for i=0 to pred (Array.length a)
  do
    pp_open_hbox formatter ();
    pp_print_string formatter "[ ";
    for j=0 to pred (Array.length a.(0))
    do
      pp_print_string formatter ((F.to_string a.(i).(j))^" ")
    done;
    pp_print_string formatter " ]";
    pp_close_box formatter ()
  done;
  pp_close_box formatter ();;

let n = 1000 in
let a = random_matrix n n
and b = random_matrix n n in
();;

(* MPFR Athlon 850
   n    t(s) mem(Mb)
 100   0.059
 250               6
 300   1.122
 500   6.780      21
1000  97.763      85

   GMP PentiumIII 1GHz
   n   t(s)
1000  120
*)
