/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"
//Check opcode is "DIV"
void div_reg_assm(void) {
	if (strcmp(OP_CODE, "DIV") != 0) {
		//If the op code doesn't match, this is the wrong command
		state = WRONG_COMMAND;
		return;
	}

	// check parameter types
	//first one must be a register (Rs)
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	//This must also be a register (Rt)
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	//Check the parameter values
	//Rs must be within valid register range(under 31)
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	//Rt must also be within the valid register range
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// create binary
	//Set the op code to 0
	setBits_str(31, "000000");
	//Set source register in the instruction(Rs)
	setBits_num(25, PARAM1.value, 5); //BUG FIX - changed 20 to 25 so Rs is the first paramter in the machine code
	//Set the target register (Rt)
	setBits_num(20, PARAM2.value, 5); //BUG FIX - changed 25 to 20 so Rt is the second parameter in the machine code
	//Set the code for DIV
	setBits_str(5, "011010");
	//Set the remaining bits to 0
	setBits_num(15, 0, 10);// Padding bits
	//Tell the system it is complete!
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


