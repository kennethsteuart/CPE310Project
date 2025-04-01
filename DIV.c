/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"
//Check opcode
void div_reg_assm(void) {
	if (strcmp(OP_CODE, "DIV") != 0) {
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
	setBits_num(25, PARAM1.value, 5); //BUG FIX - changed 20 to 25 so Rs is the first paramter in the machine code
	setBits_num(20, PARAM2.value, 5); //BUG FIX - changed 25 to 20 so Rt is the second parameter in the machine code
	setBits_str(5, "011010");
	setBits_num(15, 0, 10);// Padding bits
	
	state = COMPLETE_ENCODE;
}

void div_reg_bin(void) {
	// Verify opcode and function code 
	if (checkBits(31, "000000") != 0 || checkBits(5, "011010") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// find binary
	uint32_t Rs = getBits(25, 5); //Source Register
	uint32_t Rt = getBits(20, 5); //Target Register

	//Set decoded operation and parameters
	setOp("DIV");
	setParam(1, REGISTER, Rs); //BIG FIX - changed 2 to 1 so Rs is the first parameter in the instruction
	setParam(2, REGISTER, Rt); //BUG FIX - changed 1 to 2 so Rt is the second parameter in the instruction

	state = COMPLETE_DECODE;
}


