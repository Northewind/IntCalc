#include <stdio.h>
#include <stdlib.h>
#include "uinter.h"

void
ui_sndmes (msg_t type, char *mes)
{
	switch (type) {
		case MT_ERROR:
			fprintf (stderr, "Ошибка: %s\n", mes);
			//exit (1);
			break;
		case MT_WARN:
			fprintf (stderr, "Warning: %s\n", mes);
			break;
		case MT_RSLT:
			printf ("%s", mes);
			break;
		case MT_INFO:
			printf ("%s", mes);
			break;
	}
}

