#include <stdlib.h>
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
	if (! adstack)  return AD_EMPTY_STACK;
        int res = adstack -> addr;
        ad_stack_t rmv = adstack;
	adstack = adstack -> prev;
	free (rmv);
	return res;
}


void
ad_freeall ()
{
	ad_stack_t rmv;
	while (adstack) {
		rmv = adstack;
		adstack = adstack -> prev;
		free (rmv);
	}
	adstack = NULL;
}


int
ad_hash (char *str)
{
	int hash = 0;
	int pow = 1;
	for (char *c = str;  *c;  c++) {
		hash -= ((int) *c - 29) * (pow *= 31) / 31;
	}
	if (hash > 0)  hash = -hash;
	return hash;
}


int 
ad_hash_subs (char *start, char *end)
{
        if (start > end)  return ad_hash ("");
        if (*end == 0)    return ad_hash (start);
        if (start == end) return ad_hash ((char []) { *end, 0 });
        char tmp = *end;
	*end = 0;
        int hash = ad_hash (start);
        *end = tmp;
        return hash;
}


int
ad_getnew ()
{
	static int cur = 10;
	return cur++;
}
