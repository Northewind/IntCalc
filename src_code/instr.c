#include <stdlib.h>
#include "instr.h"


// Double linked list for instructions storing
typedef struct prog_t {
        instr_t instr;
        struct prog_t *prev;
	struct prog_t *next;
} *prog_t;


// Handles for begin and end of instruction list
static prog_t prog     = NULL;
static prog_t prog_end = NULL;
// Handle for current instruction node
static prog_t in_pnt = NULL;


static void
in_free (prog_t p)
{
	if (! p)  return;
	prog_t rem = p -> prev;
	free (p);
	in_free (rem);
}


void
in_freeall ()
{
	in_free (prog_end);
	prog_end = in_pnt = NULL;
}


void
in_put (instr_t i)
{
	in_pnt = malloc (sizeof (struct prog_t));
	in_pnt -> instr = i;
	in_pnt -> prev = prog_end;
	in_pnt -> next = NULL;
	if (! prog_end) {
		prog = prog_end = in_pnt;
	}
	else {
		prog_end -> next = in_pnt;
		prog_end = in_pnt;
	}
}


static prog_t
in_srch (int addr)
{
	if (! prog_end)  return NULL;
	prog_t res = prog_end;
	do {
		if (res -> instr.addr == addr)  break;
	} while ((res = res -> prev));
	return res;
}


void
in_set (int addr)
{
	in_pnt = in_srch (addr);
}


instr_t *
in_getplay ()
{
	if (! in_pnt)  return NULL;
	instr_t *res = & in_pnt -> instr;
	in_pnt = in_pnt -> next;
	return  res;
}
