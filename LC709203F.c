#include "LC709203F.h"

/*
 ** ==================== Initialize library ====================
 */
void LC709203F_Init(LC709203F_t *Obj, Write_Fcn Write, Read_Fcn Read, uint8_t Addres_Device){
  Obj->Write = Write;
  Obj->Read = Read;
  Obj->Address = Addres_Device;
}

/*
 ** ==================== Write on any general two bytes register  ====================
 */
void LC709203F_Write(LC709203F_t *Obj, uint8_t Reg, uint16_t data, uint8_t amount){
  uint8_t buffer[3];    
  
  buffer[0] = Reg;
  buffer[1] = data >> 8;
  buffer[2] = data;
  Obj->Write(Obj->Address, (void*)buffer, (amount+1));
}

/*
 ** ==================== read two bytes register ====================
 */
uint16_t LC709203F_Read(LC709203F_t *Obj, uint8_t Reg, uint8_t amount){
  uint8_t buffer[3];
  buffer[0] = Reg;
  Obj->Read(Obj->Address, buffer, amount);
  return buffer[1] << 8 | buffer[0];
}

/*
 ** ==================== Get battery voltage ====================
 */
uint16_t LC709203F_Voltage(LC709203F_t *Obj){
	return (uint16_t) ((LC709203F_Read(Obj, LC709203F_VCELL, 2)));
}

/*
 ** ==================== Get battery SOC (State of charge) ====================
 */
uint16_t LC709203F_SOC(LC709203F_t *Obj){
	return (uint16_t) ((LC709203F_Read(Obj, LC709203F_RSOC, 2)));
}

/** ==================== Get ID chip SOC  ===================================*/
uint16_t LC709203F_ID(LC709203F_t *Obj){
	return (uint16_t) ((LC709203F_Read(Obj, LC709203F_REG_ID, 2)));
}


