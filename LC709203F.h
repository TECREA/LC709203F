/*
 * LC709203F.h Device driver
 * Author : Ing. Adimaro Montoya
 * 
 *  Created on: Aug 31, 2020
 */

#ifndef DRIVERS_HD_LC709203F_H_
#define DRIVERS_HD_LC709203F_H_

  #include <stdint.h>

  #define LC709203F_ADDR_SLAVE                   ( 0x0Bu )            /* address slave */
  #define LC709203F_VCELL                        ( 0x09u )            /* cell voltage */
  #define LC709203F_RSOC                         ( 0x0Du )            /* Relative state of charge */
  #define LC709203F_REG_ITE                      ( 0x0Fu )            /* Indicator to empty */
  #define LC709203F_REG_ID                       ( 0x11u )            /* chip id */

/**
 * Pointer to functions type
 */
  typedef void (*Write_Fcn )(uint8_t, void*, uint8_t);
  typedef void (*Read_Fcn  )(uint8_t, void*, uint8_t);

  typedef struct {
    Write_Fcn Write;
    Read_Fcn  Read;
    uint8_t   Address;
  }LC709203F_t;

  /**
   * @brief Initialize LC709203F module to work
   * @param Obj Obj Structure containing all data from the LC709203F module.
   * @param Write pointer to function i2c write
   * @param Read  pointer to function i2c read
   * @param Addres_Device slave addres device
   */
  void LC709203F_Init(LC709203F_t *Obj, Write_Fcn Write, Read_Fcn Read, uint8_t Addres_Device);

  /**
   * @brief this function read register
   * @param Obj     Obj Structure containing all data from the LC709203F module.
   * @param Reg     address register to write
   * @param data    data to write
   * @param amount  length bytes to write
   */
  void LC709203F_Write(LC709203F_t *Obj, uint8_t Reg, uint16_t data, uint8_t amount);

  /**
   * @brief this function read register
   * @param Obj     Obj Structure containing all data from the LC709203F module.
   * @param Reg     address register to read
   * @param amount  length bytes to read
   * @return        data received in 2 bytes
   */
  uint16_t LC709203F_Read(LC709203F_t *Obj, uint8_t Reg, uint8_t amount);

  /**
   * @param this function read voltage from battery
   * @param Obj Obj Structure containing all data from the LC709203F module.
   * @return Voltage read on battery in mV
   */
  uint16_t LC709203F_Voltage(LC709203F_t *Obj);

  /**
   * @brief this function read soc in float
   * @param Obj Obj Structure containing all data from the LC709203F module.
   * @return state of charge float
   */
  uint16_t LC709203F_SOC(LC709203F_t *Obj);

  /**
   * @brief This function request ID
   * @param Obj Obj Structure containing all data from the LC709203F module.
   * @return version module
   */
  uint16_t LC709203F_ID (LC709203F_t *Obj);


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

#endif /* DRIVERS_HD_LC709203F_H_ */
