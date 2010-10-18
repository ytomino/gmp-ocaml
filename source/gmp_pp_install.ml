module Longident = struct
	type t =
		| Lident of string
		| Ldot of t * string
		| Lapply of t * t;;
end;;
open Longident;;
Topdirs.dir_install_printer Format.std_formatter (Obj.magic (Ldot (Lident "Gmp_pp", "pp_z")));;
Topdirs.dir_install_printer Format.std_formatter (Obj.magic (Ldot (Lident "Gmp_pp", "pp_q")));;
Topdirs.dir_install_printer Format.std_formatter (Obj.magic (Ldot (Lident "Gmp_pp", "pp_f")));;
