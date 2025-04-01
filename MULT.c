#include "Instruction.h"



void mult_reg_assm(void) {
	
	if (strcmp(OP_CODE, "MULT") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// check par
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// create binary
	setBits_str(31, "000000");
	setBits_num(25, PARAM1.value, 5); 
	setBits_num(20, PARAM2.value, 5); 
	setBits_str(5, "011000");
	setBits_num(15, 0, 10);
	
	state = COMPLETE_ENCODE;
}

void mult_reg_bin(void) {
	//Verify opcode
	if (checkBits(31, "000000") != 0 || checkBits(5, "011000") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// find binary
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);

	setOp("MULT");
	setParam(1, REGISTER, Rs);
	setParam(2, REGISTER, Rt); 

	state = COMPLETE_DECODE;
}

