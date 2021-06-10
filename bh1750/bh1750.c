#include "bh1750.h"



static const nrf_drv_twi_t m_twi_0 = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);
static _Bool xfer_done = true ;
uint8_t data[2]; // TWI buffer
uint16_t m_light_data; // return data 
 /**
 * @brief TWI events handler.
 */
void bh_twi_handler(nrf_drv_twi_evt_t const * p_event, void * p_context)
{
      switch (p_event->type)
    {
        case NRF_DRV_TWI_EVT_DONE:
            if (p_event->xfer_desc.type == NRF_DRV_TWI_XFER_RX)
            {
		m_light_data = (data[0]<<8)+data[1];
		m_light_data = m_light_data/ 1.2;  //transform data
		xfer_done = true;
            }
          
            break;
        default:
            break;
    }
}
	
/**
 * @brief Function init TWI & BH1750.
 *
 * @param  enum, operating mode 

 */

void bh1750_init (bh_operating_mode_t in)
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_config = {
       .scl                = BH_SCL_PIN,
       .sda                = BH_SDA_PIN,
       .frequency          = NRF_DRV_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    nrf_drv_twi_init(&m_twi_0, &twi_config, bh_twi_handler, NULL);  //TWI init
    APP_ERROR_CHECK(err_code);

    nrf_drv_twi_enable(&m_twi_0);  // TWI enable 
    nrf_delay_us(BH_INIT_DELAY);
  
    // init BH1750
    uint8_t comm_buff = BH1750_ON; // buffer for sending command
    nrf_drv_twi_tx(&m_twi_0,BH_ADDR_L,&comm_buff,sizeof(comm_buff), false);  // transmit function
    nrf_delay_us(BH_INIT_DELAY);  //short delay, otherwise the device may miss the command
    
    comm_buff = BH1750_RESET;
    nrf_drv_twi_tx(&m_twi_0, BH_ADDR_L,&comm_buff,sizeof(comm_buff), false);
    nrf_delay_us(BH_INIT_DELAY);
      
    comm_buff = in;
    nrf_drv_twi_tx(&m_twi_0, BH_ADDR_L,&comm_buff,sizeof(comm_buff), false);
    nrf_delay_us(BH_INIT_DELAY);
   
}
  
  /**
 * @brief Function for get illumination measurements.
 *
 * 
 */

void bh1750_get_light (void)
{
  nrf_drv_twi_rx(&m_twi_0, BH_ADDR_L, &data, sizeof(data)); // read the value from the sensor
  xfer_done = false;
}

  /**
 * @brief Function for read illumination measurements.
 * @param  *out,  result
 * @retval ::xfer_done flage state
 */
_Bool bh1750_read (uint16_t *out)
{
  if (xfer_done == false)
  {
     return false;
  }
   else {
     *out = m_light_data;
     return true;
   }
}