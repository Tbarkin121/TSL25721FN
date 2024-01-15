/**
 * Methods to manage the pressure sensor and display
 */
#include <stdio.h>
#include <string.h> // memset
#include <stdbool.h>

#include "lightsns.h"
#include "TSL25721FN.h"
#include "drivers/dsPIC33CH/i2c_host/i2c2.h"
#include "drivers/timer_1ms.h"

#include "drivers/dsPIC33CH/system/pins.h"
#include "logging/ulog.h"

/* Private variables ---------------------------------------------------------*/
static uint8_t whoamI;
static tsl25721fn_enable_t enabled_state;
static tsl25721fn_ailt_t low_threshold_state;
static tsl25721fn_aiht_t high_threshold_state;
static tsl25721fn_pers_t persistance_state;
static tsl25721fn_control_t gain_state;
static tsl25721fn_atime_t atime_state;
static tsl25721fn_status_t status;
static uint16_t adc_data_0;
static uint16_t adc_data_1;
static uint8_t response[2];
static uint8_t lux_int_state;
static uint8_t lux_int_flag;
/*
 * initialize the TSL25751FN sensor
 */
void lightsns_initialize(void) 
{
    // Check that we can talk to the device
    tsl25721fn_dev_id_get(&whoamI);
    if (whoamI != TSL21721FN_ID_RESPONSE)
    {
        while (1); /* manage here device not found */
    }
    // Set up the interrupt and enable the device
    enabled_state.aien = 1;
    enabled_state.aen = 1;
    enabled_state.pon = 1;
    tsl25721fn_enable_write(&enabled_state);
    tsl25721fn_enable_read(&response);
    delay_ms(100);
//    if(response[0] != enabled_state)
//    {
//        while (1); /* manage bad write */
//    }

    
    // Set the sensitivity for the upper and lower thresholds
    uint16_t threshold = 0;
    low_threshold_state.ailtl = (uint8_t)(threshold & 0xFF);
    low_threshold_state.ailth  = (uint8_t)(threshold >> 8);
    tsl25721fn_lowthresh_write(&low_threshold_state);
    tsl25721fn_lowthresh_read(&response);
    if(response[0] != low_threshold_state.ailtl || response[1] != low_threshold_state.ailth) 
    {
        while (1); /* manage bad write */
    }
    threshold = 50;
    high_threshold_state.aihtl = (uint8_t)(threshold & 0xFF);
    high_threshold_state.aihth  = (uint8_t)(threshold >> 8);
    tsl25721fn_highthresh_write(&high_threshold_state);
    tsl25721fn_highthresh_read(&response);
    if(response[0] != high_threshold_state.aihtl || response[1] != high_threshold_state.aihth) 
    {
        while (1); /* manage bad write */
    }
    // Set up filtering
    persistance_state.apers = 0b100; // 5 consecutive readings outside threshold
    tsl25721fn_persistence_write(&persistance_state);
    tsl25721fn_persistence_read(&response);
    // Set up gain
    gain_state.again = AGAIN_120X; 
    tsl25721fn_gain_write(&gain_state);
    atime_state.atime = ATIME_1CYCLE;
    tsl25721fn_atime_write(&atime_state);
    
    tsl25721fn_clear_int();
}


void lightsns_check(void) 
{
//    tsl25721fn_clear_int();
    tsl25721fn_status_read(&status);
    Nop(); // For Breakpoint.... MPLABS!!!
    tsl25721fn_c0_read(&adc_data_0);
    Nop(); // For Breakpoint.... MPLABS!!!
    tsl25721fn_c1_read(&adc_data_1);
    Nop(); // For Breakpoint.... MPLABS!!!
    lightsns_event();
    ULOG_INFO("[LUX] c0: %d", adc_data_0);
    ULOG_INFO("[LUX] c1: %d", adc_data_1);
}

void lightsns_event(void)
{
    if(!lux_int_flag)
    {
        ULOG_INFO("Lux Int Activated");
        lux_int_flag = 1;
        tsl25721fn_clear_int();
    }
}


void LUX_INT_CallBack(void)
{
    lux_int_state = LUX_INT_GetValue();
    lux_int_flag = 0;
}