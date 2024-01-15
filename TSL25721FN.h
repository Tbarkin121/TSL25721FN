/*
 *  TSL25721FN.h
 *  Driver header file for the LIS2HH12 Accelerometer
 *  Derived from STM32 driver source code : https://github.com/STMicroelectronics/lis2hh12-pid
 *  By: Tyler Barkin
 *  Created: 12-15-2023
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef TSL25721FN_H
#define TSL25721FN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>
#include <math.h>

typedef enum
{
  RepeatedByteProtocol              = 0x00,
  IncrementByteProtocol             = 0x01,
  SpecialFunction                   = 0x03,
} tsl25721fn_command_t;

typedef enum
{
  NoAction                = 0x00,
  ASLClearInt             = 0b00110,
} tsl25721fn_functions_t;

#define TSL25721FN_ENABLE                   0x00U
typedef struct
{
  uint8_t pon                               : 1;
  uint8_t aen                               : 1;
  uint8_t reserved3                         : 1;
  uint8_t wen                               : 1;
  uint8_t aien                              : 1;
  uint8_t reserved2                         : 1;
  uint8_t sai                               : 1;
  uint8_t reserved1                         : 1;
} tsl25721fn_enable_t;

#define TSL25721FN_ATIME                    0x01U
#define ATIME_1CYCLE                        0xFFU // 2.73 ms
#define ATIME_10CYCLE                       0xF6U // 27.3 ms
#define ATIME_37CYCLE                       0xDBU // 101  ms
#define ATIME_64CYCLE                       0xC0U // 175  ms
#define ATIME_256CYCLE                      0x00U // 699  ms
typedef struct
{
  uint8_t atime                             : 8;
} tsl25721fn_atime_t;


#define TSL25721FN_WTIME                    0x03U
typedef struct
{
  uint8_t wtime                             : 8;
} tsl25721fn_wtime_t;

#define TSL25721FN_AILTL                    0x04U
#define TSL25721FN_AILTH                    0x05U
typedef struct
{
  uint8_t ailtl                           : 8;
  uint8_t ailth                           : 8;

} tsl25721fn_ailt_t;


#define TSL25721FN_AIHTL                    0x06U
#define TSL25721FN_AIHTH                    0x07U
typedef struct
{
  uint8_t aihtl                             : 8;
  uint8_t aihth                             : 8;

} tsl25721fn_aiht_t;

#define TSL25721FN_PERS                     0x0CU
typedef struct
{
  uint8_t apers                             : 4;
  uint8_t reserved                          : 4;  
} tsl25721fn_pers_t;

#define TSL25721FN_CONFIG                   0x0DU
typedef struct
{
  uint8_t reserved2                         : 1;
  uint8_t wlong                             : 1;
  uint8_t agl                               : 1;
  uint8_t reserved1                         : 5;  
} tsl25721fn_config_t;

#define TSL25721FN_CONTROL                  0x0FU
#define AGAIN_1X                            0x00U
#define AGAIN_8X                            0x01U
#define AGAIN_16X                           0x10U
#define AGAIN_120X                          0x11U

typedef struct
{
  uint8_t again                             : 2;
  uint8_t reserved1                         : 6;  
} tsl25721fn_control_t;

#define TSL25721FN_ID                       0x12U
#define TSL21721FN_ID_RESPONSE              0x34U
typedef struct
{
  uint8_t id                                : 8;
} tsl25721fn_id_t;

#define TSL25721FN_STATUS                   0x13U
typedef struct
{
  uint8_t avalid                            : 1;
  uint8_t reserved2                         : 3;
  uint8_t aint                              : 1;
  uint8_t reserved1                         : 3;
  
} tsl25721fn_status_t;

#define TSL25721FN_C0DATA                   0x14U
#define TSL25721FN_C0DATAH                  0x15U
typedef struct
{
  uint8_t c0datal                               : 8;
  uint8_t c0datah                               : 8;
} tsl25721fn_c0data_t;

#define TSL25721FN_C1DATA                   0x16U
#define TSL25721FN_C1DATAH                  0x17U
typedef struct
{
  uint8_t c1datal                               : 8;
  uint8_t c1datah                               : 8;
} tsl25721fn_c1data_t;


typedef union
{
  tsl25721fn_enable_t      enable;
  tsl25721fn_atime_t       atime;
  tsl25721fn_wtime_t       wtime;
  tsl25721fn_ailt_t        ailt;
  tsl25721fn_aiht_t        aiht;
  tsl25721fn_pers_t        pers;
  tsl25721fn_config_t      config;
  tsl25721fn_control_t     control;
  tsl25721fn_id_t          id;
  tsl25721fn_status_t      status;
  tsl25721fn_c0data_t      c0data;
  tsl25721fn_c1data_t      c1data;
  uint8_t                  byte;
} lis2hh12_reg_t;


/** @addtogroup TSL25721FN
  * @{
  *
  */


/** @addtogroup  Interfaces_Functions
  * @brief       This section provide a set of functions used to read and
  *              write a generic register of the device.
  *              MANDATORY: return 0 -> no Error.
  * @{
  *
  */

/*
 * These are the basic platform dependent I/O routines to read
 * and write device registers connected on a standard bus.
 * The driver keeps offering a default implementation based on function
 * pointers to read/write routines for backward compatibility.
 * The __weak directive allows the final application to overwrite
 * them with a custom implementation.
 */

uint8_t tsl25721fn_read_reg(uint8_t reg,
                          uint8_t *data,
                          uint16_t len);
                          
uint8_t tsl25721fn_write_reg(uint8_t reg,
                           uint8_t *data,
                           uint16_t len);

uint8_t tsl25721fn_clear_int(void);

uint8_t tsl25721fn_dev_id_get(uint8_t *buff);
uint8_t tsl25721fn_enable_read(uint8_t *buff);
uint8_t tsl25721fn_enable_write(uint8_t *buff);
uint8_t tsl25721fn_lowthresh_read(uint8_t *buff);
uint8_t tsl25721fn_lowthresh_write(uint8_t *buff);
uint8_t tsl25721fn_highthresh_read(uint8_t *buff);
uint8_t tsl25721fn_highthresh_write(uint8_t *buff);
uint8_t tsl25721fn_persistence_read(uint8_t *buff);
uint8_t tsl25721fn_persistence_write(uint8_t *buff);
uint8_t tsl25721fn_gain_read(uint8_t *buff);
uint8_t tsl25721fn_gain_write(uint8_t *buff);
uint8_t tsl25721fn_atime_read(uint8_t *buff);
uint8_t tsl25721fn_atime_write(uint8_t *buff);

uint8_t tsl25721fn_status_read(uint8_t *buff);
uint16_t tsl25721fn_c0_read(uint8_t *buff);
uint16_t tsl25721fn_c1_read(uint8_t *buff);




#endif