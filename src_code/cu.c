#include <stdlib.h>
#include "cu.h"
#include "vars.h"
#include "addr.h"
#include "outxt.h"
#include "uinter.h"

#define ADDR_NOSPEC  (-1)

static cmp_status_t cmp_reg = CMP_UNK;
static int srch_addr = ADDR_NOSPEC;


static void
jmp (int addr)
{
	in_set (srch_addr = addr);
}


static void
call (int addr, int retaddr)
{
	ad_push (retaddr);
	jmp (addr);
}


static void
ret ()
{
	int retaddr = ad_pop ();
	if (retaddr == AD_EMPTY_STACK)
		ui_sndmes (MT_ERROR, "RET found, but CALL was not present");
	else
		in_set_after (retaddr);
}


static void
out (dint_t *i)
{
	char *str = i_asstr (i);
	ui_sndmes (MT_RSLT, str);
	free (str);
}


static void
free_ ()
{
	ad_freeall ();
	in_freeall ();
	ot_freeall ();
	var_freeall ();
}


static void
hlt () {
	free_ ();
	exit (0);
}


static void
execu (instr_t i)
{
	srch_addr = ADDR_NOSPEC;
	int a, s;
	dint_t c, c1, c2, *r, *r1, *r2;
	switch (oc_argset_type (i.opcode)) {
		case AS_R:
			r = var_get (i.args.as_r.r);
			break;
		case AS_RR:
			r1 = var_get (i.args.as_rr.r1);
			r2 = var_get (i.args.as_rr.r2);
			break;
		case AS_RC:
			r = var_get (i.args.as_rc.r);
			c = i.args.as_rc.c;
			break;
		case AS_CC:
			c1 = i.args.as_cc.c1;
			c2 = i.args.as_cc.c2;
			break;
		case AS_S:
			s = i.args.as_s.s;
			break;
		case AS_CR:
			c = i.args.as_cr.c;
			r = var_get (i.args.as_cr.r);
			break;
		case AS_A:
			a = i.args.as_a.a;
			break;
		case AS_NO:
			break;
		case AS_ERROR:
			ui_sndmes (MT_ERROR, "Unknown argset");
			return;
	}
	switch (i.opcode) {
		case MOV_RC:
			*r = c;
			break;
		case MOV_RR:
			*r1 = *r2;
			break;
		case XCHG_RR:
			i_xchg (r1, r2);
			break;
		case ADD_RC:
			i_add (r, &c);
			break;
		case ADD_RR:
			i_add (r1, r2);
			break;
		case SUB_RC:
			i_sub (r, &c);
			break;
		case SUB_RR:
			i_sub (r1, r2);
			break;
		case MUL_RC:
			i_mul (r, &c);
			break;
		case MUL_RR:
			i_mul (r1, r2);
			break;
		case DIV_RC:
			i_div (r, &c);
			break;
		case DIV_RR:
			i_div (r1, r2);
			break;
		case INV_R:
			i_inv (r);
			break;
		case INC_R:
			i_inc (r);
			break;
		case DEC_R:
			i_dec (r);
			break;
		case SIN_R:
			i_sin (r);
			break;
		case COS_R:
			i_cos (r);
			break;
		case TAN_R:
			i_tan (r);
			break;
		case COT_R:
			i_cot (r);
			break;
		case ASIN_R:
			i_asin (r);
			break;
		case ACOS_R:
			i_acos (r);
			break;
		case ATAN_R:
			i_atan (r);
			break;
		case ACOT_R:
			i_acot (r);
			break;
		case CMP_RC:
			cmp_reg = i_cmp (r, &c);
			break;
		case CMP_CR:
			cmp_reg = i_cmp (&c, r);
			break;
		case CMP_RR:
			cmp_reg = i_cmp (r1, r2);
			break;
		case CMP_CC:
			cmp_reg = i_cmp (&c1, &c2);
			break;
		case JMP_A:
			jmp (a);
			break;
		case JE_A:
			if (cmp_reg & CMP_EQ)  jmp (a); 
			break;
		case JNE_A:
			if (cmp_reg & CMP_NE)  jmp (a); 
			break;
		case JGT_A:
			if (cmp_reg & CMP_GT)  jmp (a); 
			break;
		case JGE_A:
			if (cmp_reg & CMP_GE)  jmp (a); 
			break;
		case JLT_A:
			if (cmp_reg & CMP_LT)  jmp (a); 
			break;
		case JLE_A:
			if (cmp_reg & CMP_LE)  jmp (a); 
			break;
		case JIN_A:
			if (cmp_reg & CMP_IN)  jmp (a); 
			break;
		case JOUT_A:
			if (cmp_reg & CMP_OUT)  jmp (a); 
			break;
		case CALL_A:
			call (a, i.addr);
			break;
		case RET_NO:
			ret ();
			break;
		case OUT_S:
			ui_sndmes (MT_RSLT, ot_gettxt (s));
			break;
		case OUT_R:
			out (r);
			break;
		case NOP_NO:
			break;
		case FREE_NO:
			free_ ();
			break;
		case HLT_NO:
			hlt ();
			break;
		case OPCODE_ERROR:
			break;
	}
}


void
proc (instr_t i)
{
	in_put (i);
	if (srch_addr == ADDR_NOSPEC  ||  srch_addr == i.addr) {
		instr_t *ipnt;
		while ((ipnt = in_getplay ())) {
			execu (*ipnt);
		}
	}
}
