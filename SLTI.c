/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

// give this to the intern

#include "Instruction.h"

void slti_immd_assm(void) {
	if (strcmp(OP_CODE, "SLTI") != 0) {
		// If the op code doesnt match, this isnt the correct command
		state = WRONG_COMMAND;
		return;
	}
	// The first parameter should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Param 2 needs to be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	// Param 3 needs to be an immediate
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}


	/*
		Checking the value of parameters
	*/

	// Rt should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// The immediate value is limited to 16 bits, this is 0xFFFF
	if (PARAM3.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}
	// Set the opcode
	setBits_str(31, "001010");


	// set Rt
	setBits_num(20, PARAM1.value, 5);

	// set Rs
	setBits_num(25, PARAM2.value, 5);

	// set immediate
	setBits_num(15, PARAM3.value, 16);

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void slti_immd_bin(void) {
	if (checkBits(31, "001010") != 0) {
		state = WRONG_COMMAND;
		return;
	}
	// getBits(start_bit, width)
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);


	/*
		Setting Instuciton values
	*/

	setOp("SLTI");
	//setCond_num(cond);
	//setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rt); //destination
	setParam(2, REGISTER, Rs); //first source register operand
	setParam(3, IMMEDIATE, imm16); //second source register operand


	// tell the system the decoding is done
	state = COMPLETE_DECODE;
}


