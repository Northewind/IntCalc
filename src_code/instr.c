#include <stdlib.h>
#include <stdio.h>
#include "instr.h"


// Hranenie instrukciy programmi - dvusvyazniy spisok
typedef struct prog_t {
        instr_t instr;
        struct prog_t *prev;
	struct prog_t *next;
} *prog_t;


// Ukazateli na nachalo i konec spiska instrukciy
static prog_t prog     = NULL;
static prog_t prog_end = NULL;
// Ukazatel na tekushuu instrukciyu
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


#define STR_SZ 100
#define ARG_STR_SZ 50
char *
in_asstr (instr_t i)
{
	char *argstr = malloc (ARG_STR_SZ);
	char *c1str, *c2str;
	switch (oc_argset_type (i.opcode)) {
		case R:
			snprintf (argstr, ARG_STR_SZ, "R%d", i.as_r.r);
			break;
		case RR:
			snprintf (argstr, ARG_STR_SZ, "R%d, R%d", i.as_rr.r1, i.as_rr.r2);
			break;
		case RC:
			c2str = i_asstr(& i.as_rc.c);
			snprintf (argstr, ARG_STR_SZ, "R%d, %s", i.as_rc.r, c2str);
			free (c2str);
			break;
		case CC:
			c1str = i_asstr (& i.as_cc.c1);
			c2str = i_asstr (& i.as_cc.c2);
			snprintf (argstr, ARG_STR_SZ, "%s, %s", c1str, c2str);
			free (c1str);
			free (c2str);
			break;
		case C:
			c1str = i_asstr (& i.as_c.c);
			snprintf (argstr, ARG_STR_SZ, "%s", c1str);
			free (c1str);
			break;
		case CR:
			c1str = i_asstr (& i.as_cr.c);
			snprintf (argstr, ARG_STR_SZ, "%s, R%d", c1str, i.as_cr.r);
			free (c1str);
			break;
		case A:
			snprintf (argstr, ARG_STR_SZ, "0x%X", i.as_a.a);
			break;
		case NO:
			snprintf (argstr, ARG_STR_SZ, "(no)");
			break;
		default:
			snprintf (argstr, ARG_STR_SZ, "(unknown argset)");
	}
	char *res    = malloc (STR_SZ);
	char *ocstr  = oc_asstr (i.opcode);
	snprintf (res, STR_SZ, "addr: 0x%X \t oper: %s \t args: %s",
		i.addr, ocstr, argstr);
	free (ocstr);
	free (argstr);
	return res;
}
#undef STR_SZ
#undef ARG_STR_SZ


void
in_prnall ()
{
	if (! prog)  return;
	prog_t iter = prog;
	char *tmp;
	do {
		tmp = in_asstr (iter -> instr);
		if (iter == in_pnt)
			printf ("%s ***\n", tmp);
		else
			printf ("%s\n", tmp);
		free (tmp);
	} while ((iter = iter -> next));
}


//#define DEBUG_INSTR
#ifdef DEBUG_INSTR
int
main ()
{
	instr_t i;
	for (int k = 0;  k < 5;  k++) {
		i.addr = 10000 + k;
		i.opcode = MOV_RC;
		i.as_rc.r = (k + 1) % 3;
		i.as_rc.c = i_crt2 (10+k, 10.2*k);
		in_put (i);
	}
	in_prnall ();
	// Ustanovka instrukcii tekushey po adresu 10002
	in_set (10002);
	char *instr = in_asstr (* in_getplay ());
	printf ("Tekushaya instrukciya #10002:\n%s\n", instr);
	free (instr);
	printf ("Vse instrukcii:\n");
	in_prnall ();
	// Dobavim novuu instrukciu
	i.addr = 11111;
	i.opcode = JGE_A;
	i.as_a.a = 10001;
	in_put (i);
	printf ("Novaya instrukciya dobavlena:\n");
	in_prnall ();
	in_freeall ();
	return 0;
}
#endif  //DEBUG_INSTR
