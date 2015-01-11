#include <stdio.h>
#include <stdlib.h>
#include "uinter.h"


#ifdef UINTER_CLI
mes_behav_t onerrors = MB_PRINT;


void
ui_sndmes (msg_t type, char *mes)
{
	switch (type) {
		case MT_ERROR:
			switch (onerrors) {
				case MB_PRINT:
					fprintf (stderr, "Error: %s\n", mes);
					break;
				case MB_PRINT_EXIT:
					fprintf (stderr, "Error: %s\n", mes);
					exit (1);
			}
			break;
		case MT_WARN:
			fprintf (stderr, "Warning: %s\n", mes);
			break;
		case MT_RSLT:
			printf ("%s\n", mes);
			//fflush (stdout);
			break;
		case MT_INFO:
			printf ("%s", mes);
			break;
	}
}
#endif  // UINTER_CLI

