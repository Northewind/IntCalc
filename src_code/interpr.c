#include <stdio.h>
#include <string.h>
#include "main.h"
#include "instr.h"
#include "pars.h"
#include "cu.h"
#include "uinter.h"
#include "interpr.h"


#define INFO_HELP ("\
Usage: icalc [parameters]\n\
  Interval calculator-intepreter with assembly syntax.\n\
  It reads stdin and writes into stdout.\n\
    Parameters:\n\
    -h, --help      This help\n\
    -v, --version   Version info\n\
    -W              Exit on errors\n\
\n\
    Supported commands:\n\
      mov, xchg,\n\
      add, sub, mul, div, neg, sqrt, inv, inc, dec,\n\
      sin, cos, tan, cot, asin, acos, atan, acot,\n\
      jmp, cmp, je, jne, jgt, jge, jlt, jle, jin, jout,\n\
      nop, hlt, out, free, ret, call.\n\
")


extern mes_behav_t onerrors;


static void
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


static void
version ()
{
	printf ("%s %s\n%s\n%s\n",
		ABOUT_NAME, ABOUT_VERS, ABOUT_RIGHT, ABOUT_LICEN);
}


static void
help ()
{
	puts (INFO_HELP);
}


static void
invalpar ()
{
	help ();
}


int
main_interpr (int argc, char *argv[])
{
	int i;
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

