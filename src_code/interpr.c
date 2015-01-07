#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pars.h"


int
main (int argc, char *argv[])
{
	char inpstr[256];
	while ( !feof (stdin) ) {
		fgets (inpstr, 256, stdin);
		parse (inpstr);
		inpstr[0] = 0;
	}
	return 0;
}

