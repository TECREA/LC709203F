#include "LC709203F.h"

#define cmd_CRCpolynomial         0x07

/*
   @Brief         CRC Checker
   @Description   Needed byte for Cyclic Redundancy Check.
                  LC709203_DeviceID, Control Reg, LSB Byte, MSB Byte, CRC Byte
   @Parameter     uint8_t *rec_values -> array name for check
                  uint8_t len         -> lengt of array
   @Return value  uint8_t
 */
static  uint8_t check_crc(uint8_t *rec_values, uint8_t len);


static  uint8_t check_crc(uint8_t *rec_values, uint8_t len)
{
  uint8_t crc = 0x00                                                    ;
  uint8_t current_byte                                                  ;
  uint8_t bit                                                           ;
  for (current_byte = 0 ; current_byte < len ; current_byte++)
  {
   crc ^= (rec_values[current_byte])                                    ;
    for (bit = 8 ; bit > 0 ;bit--)
    {
     if (crc & 0x80)
       {
         crc = (crc << 1) ^ cmd_CRCpolynomial                           ;
       }
     else
       {
         crc = (crc << 1)                                               ;
       }
    }
  }
  return crc                                                            ;
}


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
  uint8_t buffer[5];
  buffer[0] = Obj->Address << 1;
  buffer[1] = Reg;
  buffer[2] = 0x00FF & data;
  buffer[3] = data >> 8;
  buffer[4] = check_crc(buffer,4);
  Obj->Write(Obj->Address, (void*)buffer+1, amount);
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

/** ==================== Get ID chip SOC  ===================================*/
uint16_t LC709203F_SLEEP_MODE(LC709203F_t *Obj){
	 LC709203F_Write(Obj, LC709203F_POWER_MODE,LC70920F_CMD_SLEEP, 4);
}

/** ==================== Get ID chip SOC  ===================================*/
uint16_t LC709203F_OP_MODE(LC709203F_t *Obj){
	 LC709203F_Write(Obj, LC709203F_POWER_MODE,LC70920F_CMD_OP, 4);
}


