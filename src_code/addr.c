#include <stdlib.h>
#include <stdio.h>
#include "addr.h"


typedef struct ad_stack_t {
        int addr;
        struct ad_stack_t *prev;
} *ad_stack_t;


static ad_stack_t adstack = NULL;


void
ad_push (int addr)
{
        ad_stack_t new = malloc (sizeof (struct ad_stack_t));
        new -> addr = addr;
        new -> prev = adstack;
        adstack = new;
}


int
ad_pop ()
{
	if (! adstack)  return -1;
        int res = adstack -> addr;
        ad_stack_t rmv = adstack;
	adstack = adstack -> prev;
	free (rmv);
	return res;
}


void
ad_free ()
{
	ad_stack_t rmv;
	while (adstack) {
		rmv = adstack;
		adstack = adstack -> prev;
		free (rmv);
	}
	adstack = NULL;
}


void
ad_prnall ()
{
	ad_stack_t cur = adstack;
	while (cur) {
		printf ("addr: 0x%X\n", cur -> addr);
		cur = cur -> prev;
	}
}


int
ad_hash (char *str)
{
	int hash = 0;
	int pow = 1;
	for (char *c = str;  *c;  c++) {
		hash += ((int) *c - 29) * (pow *= 31) / 31;
	}
	return hash;
}


//#define DEBUG_ADDR
#ifdef DEBUG_ADDR
int
main ()
{	
	ad_push (ad_hash("ba"));
	ad_push (6);
	ad_push (8);
	ad_push (11);
	ad_push (13);
	ad_push (16);
	ad_push (18);
	ad_push (21);
	ad_prnall ();
	char *mes = "4 raza POP, 2 raz PUSH";
	printf ("%s\n", mes);
	int a = ad_pop ();
	ad_pop ();
	ad_pop ();
	ad_pop ();
	ad_push (a);
	ad_push (ad_hash (mes));
	ad_prnall ();
	ad_free ();
	ad_prnall ();
}
#endif //DEBUG_ADDR
