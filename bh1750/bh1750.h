#ifndef BH1750_H__
#define BH1750_H__

#include "nrf_drv_twi.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"

#define TWI_INSTANCE_ID     0
#define BH_SCL_PIN  27
#define BH_SDA_PIN  26
#define BH_INIT_DELAY 1000

#define BH_ADDR_L 0x23
#define BH_ADDR_H 0x5C

#define BH1750_DOWN   		0x00
#define BH1750_ON		0x01
#define BH1750_RESET		0x07

typedef enum 
{
  BH_CHR_MODE = 0x10,	// Continuously H-Resolution Mode
  BH_CHR_MODE2 = 0x11,	//Continuously H-Resolution Mode2
  BH_CLR_MODE = 0x13,	//Continuously L-Resolution Mode 
  BH_OTHR_MODE = 0x20,	//One Time H-Resolution Mode
  BH_OTHR_MODE2 = 0x21,	//One Time H-Resolution Mode2
  BH_OTLR_MODE = 0x23,	//One Time L-Resolution Mode 
}bh_operating_mode_t;

typedef struct 
{
  
}bh1750_t;

/**
 * @brief Function init TWI & BH1750.
 *
 * @param  enum, operating mode 

 */
void bh1750_init (bh_operating_mode_t in);

/**
 * @brief Function for illumination measurements.
 *
 * @return illumination value (in lux).
 */

void bh1750_get_light (void);

_Bool bh1750_read (uint16_t *out);


#endif //BH1750_H__