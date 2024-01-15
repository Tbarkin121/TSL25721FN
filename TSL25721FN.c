/*
 *  TSL25721FN.c
 *  Driver source file for the TSL25721FN light sensor
 *  By: Tyler Barkin
 *  Created: 12-15-2023
 */

#include "TSL25721FN.h"
#include "drivers/dsPIC33CH/i2c_host/i2c2.h"

/* Private macro -------------------------------------------------------------*/
#define MAX_BUFFER_SIZE 10 // Define the maximum buffer size

/**
  * @defgroup    LIS2HH12_Interfaces_Functions
  * @brief       This section provide a set of functions used to read and
  *              write a generic register of the device.
  *              MANDATORY: return 0 -> no Error.
  * @{
  *
  */

/**
  * @brief  Read generic device register
  *
  * @param  ctx   read / write interface definitions(ptr)
  * @param  reg   register to read
  * @param  data  pointer to buffer that store the data read(ptr)
  * @param  len   number of consecutive register to read
  * @retval       interface status (MANDATORY: return 0 -> no Error)
  *
  */
uint8_t tsl25721fn_read_reg(uint8_t reg,
                                 uint8_t *data,
                                 uint16_t len)
{
  uint8_t command_word = (1 << 7) | (IncrementByteProtocol << 5) | reg;
  I2C2_Write(0b0111001, &command_word, 1);
  while (I2C2_IsBusy()) 
  {
    // wait for write transaction to finish
  }
  I2C2_Read(0b0111001, data, len);
  while (I2C2_IsBusy()) 
  {
      // wait for write transaction to finish
  }
  return 0;
}

/**
  * @brief  Write generic device register
  *
  * @param  ctx   read / write interface definitions(ptr)
  * @param  reg   register to write
  * @param  data  pointer to data to write in register reg(ptr)
  * @param  len   number of consecutive register to write
  * @retval       interface status (MANDATORY: return 0 -> no Error)
  *
  */
uint8_t tsl25721fn_write_reg(uint8_t reg,
                                  uint8_t *data,
                                  uint16_t len)
{
  

  if (len + 1 > MAX_BUFFER_SIZE) {
    // Handle the case where the buffer is too large
    return -1; // or some error code
  }
  
  uint8_t combinedBuf[MAX_BUFFER_SIZE];
  uint8_t command_word = (1 << 7) | (IncrementByteProtocol << 5) | reg;
  combinedBuf[0] = command_word; // Set the first byte to reg

  // Copy bufp into combinedBuf starting from the second byte
  memcpy(combinedBuf + 1, data, len);

  I2C2_Write(0b0111001, combinedBuf, len+1);
  while (I2C2_IsBusy()) {
      // wait for write transaction to finish
  }
  return 0;
}

uint8_t tsl25721fn_clear_int(void)
{
  uint8_t command_word = (1 << 7) | (SpecialFunction << 5) | ASLClearInt;
  I2C2_Write(0b0111001, &command_word, 1);
  while (I2C2_IsBusy()) {
      // wait for write transaction to finish
  }
  return 0;
}
uint8_t tsl25721fn_dev_id_get(uint8_t *buff)
{
    tsl25721fn_read_reg(TSL25721FN_ID, buff, 1);
    return 0;
}

uint8_t tsl25721fn_enable_read(uint8_t *buff)
{
    tsl25721fn_read_reg(TSL25721FN_ENABLE, buff, 1);
    return 0;
}

uint8_t tsl25721fn_enable_write(uint8_t *buff)
{
    tsl25721fn_write_reg(TSL25721FN_ENABLE, buff, 1);
    return 0;
}

uint8_t tsl25721fn_lowthresh_read(uint8_t *buff)
{
  tsl25721fn_read_reg(TSL25721FN_AILTL, buff, 2);
  return 0;
}

uint8_t tsl25721fn_lowthresh_write(uint8_t *buff)
{
  tsl25721fn_write_reg(TSL25721FN_AILTL, buff, 2);
  return 0;
}

uint8_t tsl25721fn_highthresh_read(uint8_t *buff)
{
  tsl25721fn_read_reg(TSL25721FN_AIHTL, buff, 2);
  return 0;
}

uint8_t tsl25721fn_highthresh_write(uint8_t *buff)
{
  tsl25721fn_write_reg(TSL25721FN_AIHTL, buff, 2);
  return 0;
}

uint8_t tsl25721fn_persistence_read(uint8_t *buff)
{
  tsl25721fn_read_reg(TSL25721FN_PERS, buff, 1);
  return 0;
}

uint8_t tsl25721fn_persistence_write(uint8_t *buff)
{
  tsl25721fn_write_reg(TSL25721FN_PERS, buff, 1);
  return 0;
}

uint8_t tsl25721fn_gain_read(uint8_t *buff)
{
  tsl25721fn_read_reg(TSL25721FN_CONTROL, buff, 1);
  return 0;
}

uint8_t tsl25721fn_gain_write(uint8_t *buff)
{
  tsl25721fn_write_reg(TSL25721FN_CONTROL, buff, 1);
  return 0;
}

uint8_t tsl25721fn_atime_read(uint8_t *buff)
{
  tsl25721fn_read_reg(TSL25721FN_ATIME, buff, 1);
  return 0;
}

uint8_t tsl25721fn_atime_write(uint8_t *buff)
{
  tsl25721fn_write_reg(TSL25721FN_ATIME, buff, 1);
  return 0;
}

uint8_t tsl25721fn_status_read(uint8_t *buff)
{
  tsl25721fn_read_reg(TSL25721FN_STATUS, buff, 1);
  return 0;
}

uint16_t tsl25721fn_c0_read(uint8_t *buff)
{
  tsl25721fn_read_reg(TSL25721FN_C0DATA, buff, 2);
  return 0;
}

uint16_t tsl25721fn_c1_read(uint8_t *buff)
{
  tsl25721fn_read_reg(TSL25721FN_C1DATA, buff, 2);
  return 0;
}

