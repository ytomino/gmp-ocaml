open Gmp

type t

external create: unit -> t = "mlgmp_random_create"
external create_lc_2exp: z -> int -> int -> t = "mlgmp_random_create_lc_2exp"
external create_lc_2exp_size: int -> t = "mlgmp_random_create_lc_2exp_size"
external create_mt: unit -> t = "mlgmp_random_create_mt"
external seed_int: t -> int -> unit = "mlgmp_random_seed_int"
external seed_z: t -> z -> unit = "mlgmp_random_seed_z"
val make_int: int -> t (* create and seed_int *)
val make_self_init: unit -> t (* make_int with a seed of O'Caml runtime *)
val make_z: z -> t (* create and seed_z *)
val make: int array -> t
external copy: t -> t = "mlgmp_random_copy"
(* generating *)
external int_bits: t -> int -> int = "mlgmp_random_int_bits"
val bits: t -> int
external int: t -> int -> int = "mlgmp_random_int"
external int32: t -> int32 -> int32 = "mlgmp_random_int32"
external int64: t -> int64 -> int64 = "mlgmp_random_int64"
external nativeint: t -> nativeint -> nativeint = "mlgmp_random_nativeint"
val bool: t -> bool
external float_bits: t -> int -> float = "mlgmp_random_float_bits"
val float: t -> float -> float (* [0,bound), unlike Stdlib.Random.float *)
val float_exclusive: t -> float -> float (* (0,bound) *)
val float_inclusive: t -> float -> float (* [0,bound] *)
external z: t -> z -> z = "mlgmp_random_z"
external f_bits: t -> int -> f = "mlgmp_random_f_bits"
external f: t -> prec:int -> f -> f = "mlgmp_random_f" (* [0,bound) *)
val f_exclusive: t -> prec:int -> f -> f (* (0,bound) *)
val f_inclusive: t -> prec:int -> f -> f (* [0,bound] *)
