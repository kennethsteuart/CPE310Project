/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/


#include "Instruction.h"
//Check opcode
void lui_immd_assm(void) {
	if (strcmp(OP_CODE, "LUI") != 0) {
		state = WRONG_COMMAND;
		return;
	}
	//Validate Parameters
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}
	//Check register and immediate value
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}
	if (PARAM3.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}
	//Encode instruction
	setBits_str(31, "001111"); //Set OpCode 
	setBits_num(20, PARAM1.value, 5);//Set destination
	setBits_num(25, PARAM2.value, 5);//Set source
	setBits_num(15, PARAM3.value, 16);//Set immediate

	state = COMPLETE_ENCODE;
}

void lui_immd_bin(void) {
	//Verify opcode in binary
	if (checkBits(31, "001111") != 0) {
		state = WRONG_COMMAND;
		return;
	}
	//Extract register
	uint32_t Rs = getBits(25, 5); //Source
	uint32_t Rt = getBits(20, 5); //Destination
	uint32_t imm16 = getBits(15, 16); //Immediate
	//Set decoded operation and param
	setOp("LUI");
	setParam(1, REGISTER, Rt); 
	setParam(2, REGISTER, Rs); 
	setParam(3, IMMEDIATE, imm16); 

	state = COMPLETE_DECODE;
}



