/*
 Operation codes

 Copyright (c) 2015
 Loshkin A.A. <alswayer@ya.ru>
*/



#ifndef OPCODE_H
#define OPCODE_H

#include "alu.h"

typedef enum {
	OPCODE_ERROR = -1,
	MOV_RC,  MOV_RR,  XCHG_RR,
	ADD_RC,  ADD_RR,
	SUB_RC,  SUB_RR,
	MUL_RC,  MUL_RR,  NEG_R,   SQRT_R,
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
	OUT_S,   OUT_R,
	NOP_NO,  FREE_NO, HLT_NO
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
        int s;
} argset_s_t;

typedef struct {
        dint_t c;
        int r;
} argset_cr_t;

typedef struct {
        int a;
} argset_a_t;


typedef union {
	argset_r_t   as_r;
	argset_s_t   as_s;
	argset_a_t   as_a;
	argset_rr_t  as_rr;
	argset_rc_t  as_rc;
	argset_cc_t  as_cc;
	argset_cr_t  as_cr;
} argset_t;


typedef enum {
	AS_ERROR = 0,
	AS_R = 1,  AS_RR = 2,  AS_RC = 4,  AS_CC = 8,
	AS_S = 16, AS_CR = 32, AS_A = 64,  AS_NO = 128
} argset_type;


typedef enum {
	CMD_ERROR = -1,
	MOV,  XCHG, ADD, SUB, MUL,  NEG,  SQRT, DIV,  INV,  INC,  DEC,
	SIN,  COS,  TAN, COT, ASIN, ACOS, ATAN, ACOT,
	CMP,  JMP,  JE,  JNE, JGT,  JGE,  JLT,  JLE,  JIN, JOUT,
	CALL, RET,  OUT, NOP, FREE, HLT
} cmdcode_t;


argset_type
oc_argset_type (opcode_t oc);

int
cmd_argset_type (cmdcode_t cc);

const char *
cmd_str (cmdcode_t cc);

opcode_t
cmd_to_opcode (cmdcode_t cc, argset_type ast);

#endif  // ! OPCODE_H
