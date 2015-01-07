#include <stdlib.h>
#include <stdio.h>
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

void
ot_prnall ()
{
	for (ot_list_t t = txt;  t;  t = t -> next) {
		printf ("addr: 0x%X   text: %s\n", t -> addr, t -> text);
	}
}


//#define DEBUG_OUTXT
#ifdef DEBUG_OUTXT
int
main ()
{
	char *t;
	char *t1 = "primer 1";
	char *t2 = "primer 2";
	char *t3 = "primer 3";
	char *t4 = "primer 4";
	char *t5 = "primer 5";
	char *t6 = "primer 6";
	char *t7 = "primer 7";
	ot_addtxt (t1);
	ot_addtxt (t2);
	ot_prnall ();
	ot_freeall ();
	t = ot_gettxt (2);
	if (t)
		printf ("addr-2: %s\n", t);
	else
		printf ("no text at addr 2\n");
	ot_addtxt (t4);
	ot_addtxt (t5);
	ot_addtxt (t6);
	t = ot_gettxt (1);
	if (t)
		printf ("addr-1: %s\n", t);
	else
		printf ("no text at addr 1\n");
	ot_addtxt (t7);
	ot_prnall ();
	ot_freeall ();
	return 0;
}
#endif  //OUTXT_H
