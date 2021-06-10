#ifndef  INDICATION_SERVICE_H__
#define  INDICATION_SERVICE_H__

#include "my_services.h"

typedef struct 
{
  uint16_t service_handle;                            /**< Handle of Service (as provided by the BLE stack). */
  ble_gatts_char_handles_t    butt_char_handles;	      // button state characteristic handle 
  ble_gatts_char_handles_t    led_char_handles;	      //led state  characteristic handle
} ble_is_t;
//================================================================================
void indication_service_init(ble_is_t *p_service);


void button_char_update(ble_is_t *p_service, uint16_t *conn_handle_in,  _Bool *value);

uint8_t get_led_state(ble_is_t *p_service);

#endif // -  INDICATION_SERVICE_H__ - //