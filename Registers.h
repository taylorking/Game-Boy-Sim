//Registers.h
//Authors: Joe Story, Hunter King

#ifndef REGISTERS_H
#define REGISTERS_H

#include <cstdint>
#include "Sim.h"

class Registers{
	//Private Data
		uint8_t regs[NUM_REGISTERS + 2];
		uint16_t* bigRegs[NUM_16REGISTERS] = {&regs[regA], &regs[regB], &regs[regD], &regs[regH]};

	//Private functions
	public:		
		Registers();
		void setReg(int, uint8_t);
		uint8_t getReg(int);
		uint16_t getBigReg(int);
		void setBigReg(int, uint16_t);
		void reset(void);
}