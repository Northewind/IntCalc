#ifndef OPCODE_H
#define OPCODE_H

#include "alu.h"

typedef enum {
	MOV_RC,  MOV_RR,  XCHG_RR,
	ADD_RC,  ADD_RR,
	SUB_RC,  SUB_RR,
	MUL_RC,  MUL_RR,
	DIV_RC,  DIV_RR,
	INV_R,
	INC_R,   DEC_R,
	SIN_R,   COS_R,   TAN_R,   COT_R,
	ASIN_R,  ACOS_R,  ATAN_R,  ACOT_R,
	CMP_RC,  CMP_CR,  CMP_RR,  CMP_CC,
	JMP_A,
	JE_A,    JNE_A,
	JGT_A,   JGE_A,
	JLT_A,   JLE_A,
	JIN_A,   JOUT_A,
	CALL_A,  RET_NO,
	OUT_A,   OUT_R,   OUT_C,
	HLT_NO
} opcode_t;


typedef struct {
        int r;
} argset_r_t;

typedef struct  {
        int r1;
        int r2;
} argset_rr_t;

typedef struct {
        int r;
        dint_t c;
} argset_rc_t;

typedef struct {
        dint_t c1;
        dint_t c2;
} argset_cc_t;

typedef struct {
        dint_t c;
} argset_c_t;

typedef struct {
        dint_t c;
        int r;
} argset_cr_t;

typedef struct {
        int a;
} argset_a_t;


typedef enum {
	R, RR, RC, CC, C, CR, A, NO
} argset_t;


typedef enum {
	MOV,  XCHG, ADD, SUB, MUL,  DIV,  INV,  INC,  DEC,
	SIN,  COS,  TAN, COT, ASIN, ACOS, ATAN, ACOT,
	CMP,  JMP,  JE,  JNE, JGT,  JGE,  JLT,  JLE,  JIN, JOUT,
	CALL, RET,  OUT, HLT
} cmdcode_t;


argset_t
oc_argset_type (opcode_t oc);

const char *
oc_cmdstr (cmdcode_t cc);

#endif  // ! OPCODE_H
