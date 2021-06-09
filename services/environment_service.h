#ifndef ENVIRONMENT_SERVICE_H__
#define ENVIRONMENT_SERVICE_H__

#include "my_services.h"


typedef struct 
{
  uint16_t service_handle;                            /**< Handle of Service (as provided by the BLE stack). */
  ble_gatts_char_handles_t    temp_char_handles;	      // tempreature version characteristic handle
  ble_gatts_char_handles_t    light_char_handles;	      // lightness characteristic handle 
} ble_es_t;


void enviroment_serv_init (ble_es_t *p_service);


void lightness_char_update(ble_es_t *p_service, uint16_t *conn_handle_in,  int16_t *value);

void temperature_char_update(ble_es_t *p_service, uint16_t *conn_handle_in,  int32_t *value);
#endif //ENVIRONMENT_SERVICE_H__