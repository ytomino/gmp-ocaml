open Gmp;;
open Mpfr;;
open Mpc;;

let check (major, minor, patchlevel) string = (
	Scanf.sscanf string "%d.%d%s" (fun s_major s_minor string' ->
		assert (s_major = major);
		assert (s_minor = minor);
		if string' = "" then assert (patchlevel = 0)
		else
			Scanf.sscanf string' ".%d%s" (fun s_patchlevel string'' ->
				assert (s_patchlevel = patchlevel);
				assert (string'' = "")
			)
	)
);;

check (gmp_compiled_version ()) (gmp_compiled_version_string ());;
check (mpfr_compiled_version ()) (mpfr_compiled_version_string ());;
check (mpc_compiled_version ()) (mpc_compiled_version_string ());;

prerr_endline "ok";;
