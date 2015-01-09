#ifndef INSTR_H
#define INSTR_H

#include "opcode.h"


typedef struct {
	int addr;
	opcode_t opcode;
	argset_t args;
} instr_t;


void
in_freeall ();

void
in_put (instr_t i);

void
in_set (int addr);

void
in_set_after (int addr);

instr_t *
in_getplay ();

#endif  // ! PROC_INSTR_H
