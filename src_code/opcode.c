#include <stdlib.h>
#include <string.h>
#include "opcode.h"


argset_t
oc_argset_type (opcode_t oc)
{
	argset_t res;
	switch (oc) {
		case INV_R:
		case INC_R:
		case DEC_R:
		case SIN_R:
		case COS_R:
		case TAN_R:
		case COT_R:
		case ASIN_R:
		case ACOS_R:
		case ATAN_R:
		case ACOT_R:
		case OUT_R:
			res = R;
			break;
		case MOV_RR:
		case XCHG_RR:
		case ADD_RR:
		case SUB_RR:
		case MUL_RR:
		case DIV_RR:
		case CMP_RR:
			res = RR;
			break;
		case MOV_RC:
		case ADD_RC:
		case SUB_RC:
		case MUL_RC:
		case DIV_RC:
		case CMP_RC:
			res = RC;
			break;
		case CMP_CC:
			res = CC;
			break;
		case OUT_C:
			res = C;
			break;
		case CMP_CR:
			res = CR;
			break;
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
		case OUT_A:
			res = A;
			break;
		case RET_NO:
		case HLT_NO:
			res = NO;
			break;
	}
	return res;
}


const char *STR_CMD_MOV = "mov";
const char *STR_CMD_XCHG = "xchg";
const char *STR_CMD_ADD = "add";
const char *STR_CMD_SUB = "sub";
const char *STR_CMD_MUL = "mul";
const char *STR_CMD_DIV = "div";
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
const char *STR_CMD_HLT = "hlt";

const char *
oc_cmdstr (cmdcode_t cc)
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
		case HLT:
			return STR_CMD_HLT;
		default:
			return NULL;
	}
}


//#define DEBUG_OPCODE
#ifdef DEBUG_OPCODE
int
main ()
{
	return 0;
}
#endif  //DEBUG_OPCODE
