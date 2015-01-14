#include <stdlib.h>
#include <string.h>
#include "opcode.h"


argset_type
oc_argset_type (opcode_t oc)
{
	switch (oc) {
		case INV_R:
		case INC_R:
		case DEC_R:
		case NEG_R:
		case SQRT_R:
		case SIN_R:
		case COS_R:
		case TAN_R:
		case COT_R:
		case ASIN_R:
		case ACOS_R:
		case ATAN_R:
		case ACOT_R:
		case OUT_R:
			return AS_R;
		case MOV_RR:
		case XCHG_RR:
		case ADD_RR:
		case SUB_RR:
		case MUL_RR:
		case DIV_RR:
		case CMP_RR:
			return AS_RR;
		case MOV_RC:
		case ADD_RC:
		case SUB_RC:
		case MUL_RC:
		case DIV_RC:
		case CMP_RC:
			return AS_RC;
		case CMP_CC:
			return AS_CC;
		case CMP_CR:
			return AS_CR;
		case JMP_A:
		case JE_A:
		case JNE_A:
		case JGT_A:
		case JGE_A:
		case JLT_A:
		case JLE_A:
		case JIN_A:
		case JOUT_A:
		case CALL_A:
			return AS_A;
		case OUT_S:
			return AS_S;
		case RET_NO:
		case NOP_NO:
		case FREE_NO:
		case HLT_NO:
			return AS_NO;
		case OPCODE_ERROR:
			return AS_ERROR;
	}
	return AS_ERROR;
}


int
cmd_argset_type (cmdcode_t cc)
{
	switch (cc) {
		case INV:
		case INC:
		case DEC:
		case NEG:
		case SQRT:
		case SIN:
		case COS:
		case TAN:
		case COT:
		case ASIN:
		case ACOS:
		case ATAN:
		case ACOT:
			return AS_R;
		case MOV:
		case ADD:
		case SUB:
		case MUL:
		case DIV:
			return AS_RR | AS_RC;
		case XCHG:
			return AS_RR;
		case CMP:
			return AS_RR | AS_RC | AS_CR | AS_CC;
		case OUT:
			return AS_R | AS_S;
		case JMP:
		case JE:
		case JNE:
		case JGT:
		case JGE:
		case JLT:
		case JLE:
		case JIN:
		case JOUT:
		case CALL:
			return AS_A;
		case RET:
		case NOP:
		case FREE:
		case HLT:
			return AS_NO;
		case CMD_ERROR:
			return AS_ERROR;
	}
	return AS_ERROR;
}


const char *STR_CMD_MOV = "mov";
const char *STR_CMD_XCHG = "xchg";
const char *STR_CMD_ADD = "add";
const char *STR_CMD_SUB = "sub";
const char *STR_CMD_MUL = "mul";
const char *STR_CMD_DIV = "div";
const char *STR_CMD_NEG = "neg";
const char *STR_CMD_SQRT = "sqrt";
const char *STR_CMD_INV = "inv";
const char *STR_CMD_INC = "inc";
const char *STR_CMD_DEC = "dec";
const char *STR_CMD_SIN = "sin";
const char *STR_CMD_COS = "cos";
const char *STR_CMD_TAN = "tan";
const char *STR_CMD_COT = "cot";
const char *STR_CMD_ASIN = "asin";
const char *STR_CMD_ACOS = "acos";
const char *STR_CMD_ATAN = "atan";
const char *STR_CMD_ACOT = "acot";
const char *STR_CMD_CMP = "cmp";
const char *STR_CMD_JMP = "jmp";
const char *STR_CMD_JE = "je";
const char *STR_CMD_JNE = "jne";
const char *STR_CMD_JGT = "jgt";
const char *STR_CMD_JGE = "jge";
const char *STR_CMD_JLT = "jlt";
const char *STR_CMD_JLE = "jle";
const char *STR_CMD_JIN = "jin";
const char *STR_CMD_JOUT = "jout";
const char *STR_CMD_CALL = "call";
const char *STR_CMD_RET = "ret";
const char *STR_CMD_OUT = "out";
const char *STR_CMD_NOP = "nop";
const char *STR_CMD_FREE = "free";
const char *STR_CMD_HLT = "hlt";

const char *
cmd_str (cmdcode_t cc)
{
	switch (cc) {
		case MOV:
			return STR_CMD_MOV;
		case XCHG:
			return STR_CMD_XCHG;
		case ADD:
			return STR_CMD_ADD;
		case SUB:
			return STR_CMD_SUB;
		case MUL:
			return STR_CMD_MUL;
		case DIV:
			return STR_CMD_DIV;
		case NEG:
			return STR_CMD_NEG;
		case SQRT:
			return STR_CMD_SQRT;
		case INV:
			return STR_CMD_INV;
		case INC:
			return STR_CMD_INC;
		case DEC:
			return STR_CMD_DEC;
		case SIN:
			return STR_CMD_SIN;
		case COS:
			return STR_CMD_COS;
		case TAN:
			return STR_CMD_TAN;
		case COT:
			return STR_CMD_COT;
		case ASIN:
			return STR_CMD_ASIN;
		case ACOS:
			return STR_CMD_ACOS;
		case ATAN:
			return STR_CMD_ATAN;
		case ACOT:
			return STR_CMD_ACOT;
		case CMP:
			return STR_CMD_CMP;
		case JMP:
			return STR_CMD_JMP;
		case JE:
			return STR_CMD_JE;
		case JNE:
			return STR_CMD_JNE;
		case JGT:
			return STR_CMD_JGT;
		case JGE:
			return STR_CMD_JGE;
		case JLT:
			return STR_CMD_JLT;
		case JLE:
			return STR_CMD_JLE;
		case JIN:
			return STR_CMD_JIN;
		case JOUT:
			return STR_CMD_JOUT;
		case CALL:
			return STR_CMD_CALL;
		case RET:
			return STR_CMD_RET;
		case OUT:
			return STR_CMD_OUT;
		case NOP:
			return STR_CMD_NOP;
		case FREE:
			return STR_CMD_FREE;
		case HLT:
			return STR_CMD_HLT;
		case CMD_ERROR:
			return NULL;
	}
	return NULL;
}


opcode_t
cmd_to_opcode (cmdcode_t cc, argset_type ast)
{
	switch (cc) {
		case MOV:
			if (ast == AS_RR) return MOV_RR;
			else if (ast == AS_RC)  return MOV_RC;
			else return OPCODE_ERROR;
		case XCHG:
			return (ast == AS_RR) ? XCHG_RR : OPCODE_ERROR;
		case ADD:
			if (ast == AS_RR) return ADD_RR;
			else if (ast == AS_RC)  return ADD_RC;
			else return OPCODE_ERROR;
		case SUB:
			if (ast == AS_RR) return SUB_RR;
			else if (ast == AS_RC)  return SUB_RC;
			else return OPCODE_ERROR;
		case MUL:
			if (ast == AS_RR) return MUL_RR;
			else if (ast == AS_RC)  return MUL_RC;
			else return OPCODE_ERROR;
		case DIV:
			if (ast == AS_RR) return DIV_RR;
			else if (ast == AS_RC)  return DIV_RC;
			else return OPCODE_ERROR;
		case NEG:
			return (ast == AS_R) ? NEG_R : OPCODE_ERROR;
		case SQRT:
			return (ast == AS_R) ? SQRT_R : OPCODE_ERROR;
		case INV:
			return (ast == AS_R) ? INV_R : OPCODE_ERROR;
		case INC:
			return (ast == AS_R) ? INC_R : OPCODE_ERROR;
		case DEC:
			return (ast == AS_R) ? DEC_R : OPCODE_ERROR;
		case SIN:
			return (ast == AS_R) ? SIN_R : OPCODE_ERROR;
		case COS:
			return (ast == AS_R) ? COS_R : OPCODE_ERROR;
		case TAN:
			return (ast == AS_R) ? TAN_R : OPCODE_ERROR;
		case COT:
			return (ast == AS_R) ? COT_R : OPCODE_ERROR;
		case ASIN:
			return (ast == AS_R) ? ASIN_R : OPCODE_ERROR;
		case ACOS:
			return (ast == AS_R) ? ACOS_R : OPCODE_ERROR;
		case ATAN:
			return (ast == AS_R) ? ATAN_R : OPCODE_ERROR;
		case ACOT:
			return (ast == AS_R) ? ACOT_R : OPCODE_ERROR;
		case CMP:
			if (ast == AS_RR)  return CMP_RR;
			else if (ast == AS_RC)  return CMP_RC;
			else if (ast == AS_CR)  return CMP_CR;
			else if (ast == AS_CC)  return CMP_CC;
			else return OPCODE_ERROR;
		case JMP:
			return (ast == AS_A) ? JMP_A : OPCODE_ERROR;
		case JE:
			return (ast == AS_A) ? JE_A : OPCODE_ERROR;
		case JNE:
			return (ast == AS_A) ? JNE_A : OPCODE_ERROR;
		case JGT:
			return (ast == AS_A) ? JGT_A : OPCODE_ERROR;
		case JGE:
			return (ast == AS_A) ? JGE_A : OPCODE_ERROR;
		case JLT:
			return (ast == AS_A) ? JLT_A : OPCODE_ERROR;
		case JLE:
			return (ast == AS_A) ? JLE_A : OPCODE_ERROR;
		case JIN:
			return (ast == AS_A) ? JIN_A : OPCODE_ERROR;
		case JOUT:
			return (ast == AS_A) ? JOUT_A : OPCODE_ERROR;
		case CALL:
			return (ast == AS_A) ? CALL_A : OPCODE_ERROR;
		case RET:
			return (ast == AS_NO) ? RET_NO : OPCODE_ERROR;
		case OUT:
			if (ast == AS_R)  return OUT_R;
			else if (ast == AS_S)  return OUT_S;
			else return OPCODE_ERROR;
		case NOP:
			return (ast == AS_NO) ? NOP_NO : OPCODE_ERROR;
		case FREE:
			return (ast == AS_NO) ? FREE_NO : OPCODE_ERROR;
		case HLT:
			return (ast == AS_NO) ? HLT_NO : OPCODE_ERROR;
		case CMD_ERROR:
			return OPCODE_ERROR;
	}
	return OPCODE_ERROR;
}
