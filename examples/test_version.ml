open Gmp;;
open Mpfr;;
open Mpc;;

let check (major, minor, patchlevel) string = (
	Scanf.sscanf string "%d.%d.%d%s" (fun s_major s_minor s_patchlevel s ->
		assert (s_major = major);
		assert (s_minor = minor);
		assert (s_patchlevel = patchlevel);
		assert (s = "");
		()
	)
);;

check (gmp_compiled_version ()) (gmp_compiled_version_string ());;
check (mpfr_compiled_version ()) (mpfr_compiled_version_string ());;
check (mpc_compiled_version ()) (mpc_compiled_version_string ());;

prerr_endline "ok";;
