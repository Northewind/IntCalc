#include <stdio.h>
#include <string.h>
#include "instr.h"
#include "pars.h"
#include "cu.h"
#include "uinter.h"
#include "interpr.h"


extern mes_behav_t onerrors;


void
interprete ()
{
	char inpstr [256];
	instr_t instr;
	while ( !feof (stdin) ) {
		fgets (inpstr, 256, stdin);
		inpstr [255] = 0;
		instr = parse (inpstr);
		if (instr.addr != ADDR_NOEXEC)
			proc (instr);
		inpstr [0] = 0;
	}
}


void
version ()
{
	puts (INFO_VERSION);
}


void
help ()
{
	puts (INFO_HELP);
}


void
invalpar ()
{
	help ();
}


int
main (int argc, char *argv[])
{
	int i, j;
	for (i = 1;  i < argc;  i++) {
		if (!strcmp (argv [i], "-v")) {
			version ();
			return 0;
		}
		else if (!strcmp (argv [i], "-h")) {
			help ();
			return 0;
		}
		else if (!strcmp (argv [i], "-W")) {
			onerrors = MB_PRINT_EXIT;
		}
		else if (!strcmp (argv [i], "--version")) {
			version ();
			return 0;
		}
		else if (!strcmp (argv [i], "--help")) {
			help ();
			return 0;
		}
		else {	// Invalid parameter
			invalpar ();
			return 1;
		}
	}
	interprete ();
	return 0;
}

