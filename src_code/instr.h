#ifndef INSTR_H
#define INSTR_H

#include "opcode.h"

typedef struct {
	int addr;
	opcode_t opcode;
	union {
		argset_r_t   as_r;
		argset_rr_t  as_rr;
		argset_rc_t  as_rc;
		argset_cc_t  as_cc;
		argset_c_t   as_c;
		argset_cr_t  as_cr;
		argset_a_t   as_a;
	};
} instr_t;


void
in_freeall ();

void
in_put (instr_t i);

void
in_set (int addr);

instr_t *
in_getplay ();

char *
in_asstr ();

void
in_prnall ();


#endif  // !PROC_INSTR_H
