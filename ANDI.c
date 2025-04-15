#include "Instruction.h"

void andi_immd_assm(void) {
	// Check for "ANDI"
	if (strcmp(OP_CODE, "ANDI") != 0) {
		//Incorrect opcode, it doesnt match 
		state = WRONG_COMMAND;
		return;
	}

	// check params
	//first one shoudl eb a destination register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	//this should also be a register but a source register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	//The third parameter should be the immediate to be used
	if (PARAM3.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}
	//Check the values of the paramet
	//First one should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	//This one should also be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}
	//The immediate should be a 16 bit value of 0xFFFF or less
	if (PARAM3.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	// putting the binary together
	setBits_str(31, "001100"); // Set opcode
	setBits_num(20, PARAM1.value, 5); //Set destination
	setBits_num(25, PARAM2.value, 5); // Set source
	setBits_num(15, PARAM3.value, 16); // Set immediate
	//tell the system that the encoding is complete
	state = COMPLETE_ENCODE;
}

void andi_immd_bin(void) {
	//Verify opcode matches
	if (checkBits(31, "001100") != 0 ) {
		state = WRONG_COMMAND;
		return;
	}

	// get binary values
	uint32_t Rs = getBits(25, 5);//get source register
	uint32_t Rt = getBits(20, 5);//get destination register
	uint32_t imm16 = getBits(15, 16);//get immediate value

	// set instruction values
	setOp("ANDI");//set the operation name
	setParam(1, REGISTER, Rt); //set destination register
	setParam(2, REGISTER, Rs); //set source register
	setParam(3, IMMEDIATE, imm16);//set immediate value
	//tell the system decoding is done
	state = COMPLETE_DECODE;
}



