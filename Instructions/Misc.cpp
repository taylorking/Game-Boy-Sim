#include "../gb.h"

/*
 * nop
 * No-OPeration. Spends 1 cycle doing nothing.
 */
void gb::nop(){
    return;
}

/*
 * halt
 * Stops the operation of the GB-CPU.
 */
void gb::halt(){
    status = false;
}

/*
 * stop
 * Stops the operation of the GB-CPU.
 */
void gb::stop(){
    status = false;
}

/*
 * scf
 * Sets the carry flag.
 */
void gb::scf(){
    getRegisters().clearFlag(FLAG_N);
    getRegisters().clearFlag(FLAG_H);
    getRegisters().setFlag(FLAG_C);
}

/*
 * ccf
 * Complements the carry flag.
 */
void gb::ccf(){
    getRegisters().clearFlag(FLAG_N);
    getRegisters().clearFlag(FLAG_H);
    if(getRegisters().getFlag(FLAG_C)){
        getRegisters().clearFlag(FLAG_C);
    }
    else getRegisters().setFlag(FLAG_C);
}

/*
 * di
 * Disables interrupts by clearing the Interrupt Master Enable flag.
 */
void gb::di(){
    ime = false;
}

/*
 * ei
 * Enables interrupts by setting the Interrupt Master Enable flag.
 */
void gb::ei(){
    ime = true;
}

/*
 * cpl
 * ComPLements the Accumulator.
 */
void gb::cpl(){
    getRegisters().setReg8(A, (~getRegisters().getReg8(A)));
    getRegisters().clearFlag(FLAG_H);
}

/*
 * daa
 * Decimal Adjusts the Accumulator.
 */
void gb::daa(){
    uint8_t newAcc = getRegisters().getReg8(A);

    //If a half-carry or carry occurred, or if the result is out of bounds, we will adjust.
    if (!getRegisters().getFlag(FLAG_N)){  // after an addition, adjust if (half-)carry occurred or if result is out of bounds
        if (getRegisters().getFlag(FLAG_C) || newAcc > 0x99){
            newAcc += 0x60; 
            getRegisters().setFlag(FLAG_C);
        }
        if (getRegisters().getFlag(FLAG_H) || (newAcc & 0x0f) > 0x09){
            newAcc += 0x06;
        }
    }
    //After a subtraction, we won't be out of bounds, so we can just adjust if a half-carry or carry occurred.
    else{ 
        if (getRegisters().getFlag(FLAG_C)){
            newAcc -= 0x60;
        }
        if (getRegisters().getFlag(FLAG_H)){
            newAcc -= 0x06; 
        }
    }
    
    // these flags are always updated
    if(newAcc) getRegisters().clearFlag(FLAG_Z); 
    else getRegisters().setFlag(FLAG_Z);
    getRegisters().clearFlag(FLAG_H); // h flag is always cleared
}