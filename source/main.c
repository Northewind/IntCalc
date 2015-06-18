#include "main.h"
#include "interpr.h"


int
main (int argc, char *argv[])
{
#ifdef UINTER_CLI
	return main_interpr (argc, argv);
#else
	return 0;
#endif
}

