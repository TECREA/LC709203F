#include "LC709203F.h"

/*
 ** ==================== Initialize library ====================
 */
void LC709203F_Init(LC709203F_t *Obj, LC709203F_Write_Fcn_t Write, LC709203F_Read_Fcn_t Read, uint8_t Addres_Device){
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
uint16_t LC709203F_Read(LC709203F_t *Obj, uint8_t Reg, uint8_t amount) {
  uint8_t buffer[3];
  buffer[0] = Reg;
  Obj->Read(Obj->Address, buffer, amount, LC709203F_SIZEREG);
  return buffer[1] << 8 | buffer[0];
}

/*
 ** ==================== Get battery voltage ====================
 */
uint16_t LC709203F_Voltage(LC709203F_t *Obj){
	uint16_t data;
	data = (uint16_t) ((LC709203F_Read(Obj, LC709203F_VCELL, 2)));
	 if ((data > 5000) || (data < 1000)) data=0;
	return data;
}

/*
 ** ==================== Get battery SOC (State of charge) ====================
 */
uint16_t LC709203F_SOC(LC709203F_t *Obj){
	uint16_t data;
	 data = (uint16_t) ((LC709203F_Read(Obj, LC709203F_RSOC, 2)));
	 if ((data > 100)||(data < 0)) data=0;
	return data;
}

/** ==================== Get ID chip SOC  ===================================*/
uint16_t LC709203F_ID(LC709203F_t *Obj){
	return (uint16_t) ((LC709203F_Read(Obj, LC709203F_REG_ID, 2)));
}
