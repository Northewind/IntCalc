#include <stdio.h>
#include "instr.h"
#include "pars.h"
#include "cu.h"


int
main (int argc, char *argv[])
{
	char inpstr [256];
	instr_t instr;
	while ( !feof (stdin) ) {
		fgets (inpstr, 256, stdin);
		instr = parse (inpstr);
		if (instr.addr != ADDR_NOEXEC)
			proc (instr);
		inpstr [0] = 0;
	}
	return 0;
}

