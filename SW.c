/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void sw_immd_assm(void) {
	if (strcmp(OP_CODE, "SW") != 0) {
		state = WRONG_COMMAND;
		return;
	}
	//Check parameter
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	//Check register
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	//Check immediate
	if (PARAM2.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	// setBits_str(31, "101010");
	// setBits_num(15, PARAM1.value, 5);
	// setBits_num(25, PARAM2.value, 16);
	// setBits_num(20, PARAM3.value, 5);
	//Encode instruction
	setBits_str(31, "101011"); //Opcode for SW
	setBits_num(20, PARAM1.value, 5); //Source
	setBits_num(15, PARAM2.value, 16); // Immediate offset
	setBits_num(25, PARAM3.value, 5);//Base register

	state = COMPLETE_ENCODE;
}

void sw_immd_bin(void) {

	if (checkBits(31, "101011") != 0) {
		state = WRONG_COMMAND;
		return;
	}
	//Extract register values and immediate offset
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t offset = getBits(15, 16);

	setOp("SW");
	setParam(1, REGISTER, Rt); 
	setParam(3, REGISTER, Rs);  // BUG FIX - changed the order of the parameters (2 to 3)
	setParam(2, IMMEDIATE, offset); // BUG FIX - changed the order of the parameters (3 to 2)

	state = COMPLETE_DECODE;
}