#ifndef INTR_H
#define INTR_H

#include "core.h"

typedef struct {
	char label[32];
	char opcode;
	union {
		unsigned r;
		struct {
			unsigned r1;
			unsigned r2;
		} argset1;
		struct {
			unsigned r;
			dint_t *c;
		} argset2;
	} args;
} parsed;

#endif // !INTR_H
