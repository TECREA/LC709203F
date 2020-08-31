/*
 * LC709203F.h Device driver
 * Author : Ing. Adimaro Montoya
 * 
 *  Created on: Aug 31, 2020
 */

#ifndef DRIVERS_HD_LC709203F_H_
#define DRIVERS_HD_LC709203F_H_

  #include <stdint.h>

   
  /* EXAMPLE FOR I2C READ/WRITE wrappers
   **
   **   void Write_I2C(uint8_t Address, void *data, uint8_t amount){
   **   	uint8_t *DatatoSend = (uint8_t *)data;
   **   	HAL_I2C_Master_Transmit(&hi2c1,Address,DatatoSend,amount,10);
   **   }
   **
   **   void Read_I2C(uint8_t Address, void *Register, uint8_t amount){
   **   	uint8_t *DatatoSend = (uint8_t *)Register;
   **   	HAL_I2C_Master_Transmit(&hi2c1,Address,DatatoSend, 1, 10);
   **   	HAL_I2C_Master_Receive(&hi2c1,Address,DatatoSend, amount, 10);
   **   }
  */   


  #define LC709203F_ADDR_SLAVE                   ( 0x0Bu )             /*address slave*/
  #define LC709203F_VCELL                        ( 0x09u )            /*cell voltage*/
  #define LC709203F_RSOC                         ( 0x0Du )            /*Relative state of charge*/
  #define LC709203F_REG_ITE                      ( 0x0Fu )         /*Indicator to empty*/



  /* CONFIG Register Format*/
  #define LC709203F_CONFIG_SLEEP_BIT		        ( 07u )

  /*Resolution for calculate Vcell*/
  #define LC709203F_VCELL_RESOLUTION	            ( 78125 )


  typedef void (*Write_Fcn )(uint8_t, void*, uint8_t);    // Pointer to functions type
  typedef void (*Read_Fcn  )(uint8_t, void*, uint8_t);    //

  typedef struct {
    Write_Fcn Write;
    Read_Fcn  Read;
    uint8_t   Address;
  }LC709203F_t;

  /*============================================================================*/
  void LC709203F_Init(LC709203F_t *Obj, Write_Fcn Write, Read_Fcn Read, uint8_t Addres_Device);
  /*============================================================================*/
  void LC709203F_Write(LC709203F_t *Obj, uint8_t Reg, uint16_t data, uint8_t amount);
  /*============================================================================*/
  uint16_t LC709203F_Read(LC709203F_t *Obj, uint8_t Reg, uint8_t amount);
  /*============================================================================*/
  uint16_t LC709203F_Voltage(LC709203F_t *Obj);
  /*============================================================================*/
   uint16_t LC709203F_SOC(LC709203F_t *Obj);
  /*============================================================================*/



#endif /* DRIVERS_HD_LC709203F_H_ */
