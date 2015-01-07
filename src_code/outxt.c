#include <stdlib.h>
#include "outxt.h"


typedef struct ot_list_t {
	int addr;
	char* text;
	struct ot_list_t *prev;
	struct ot_list_t *next;
} *ot_list_t;


static ot_list_t txt = NULL;
static ot_list_t txt_end = NULL;
static int addr_cnt = -1;


int
ot_addtxt (char *t)
{
	ot_list_t new = malloc (sizeof (struct ot_list_t));
	new -> addr = ++addr_cnt;
	new -> text = t;
	new -> prev = txt_end;
	new -> next = NULL;
	if (! txt) {
		txt = new;
	}
	else {
		txt_end -> next = new;
	}
	txt_end = new;
	return new -> addr;
}


char *
ot_gettxt (int addr)
{
	for (ot_list_t t = txt;  t;  t = t -> next) {
		if (t -> addr == addr)  return t -> text;
	}
	return NULL;
}


void
ot_freeall ()
{
	ot_list_t rmv;
	while (txt) {
		rmv = txt;
		txt = txt -> next;
		free (rmv);
	}
	txt = txt_end = NULL;
	addr_cnt = -1;
}
