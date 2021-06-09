#ifndef DISTANCE_SERVICE_H__
#define DISTANCE_SERVICE_H__

#include "my_services.h"

typedef struct 
{
  uint16_t service_handle;                            /**< Handle of Service (as provided by the BLE stack). */
  ble_gatts_char_handles_t    cd_char_handles;	      // current distance characteristic handle 
} ble_ds_t;
//================================================================================

void distance_serv_init (ble_ds_t *p_service);

 void current_distance_char_update(ble_ds_t *p_service, uint16_t *conn_handle_in,  int32_t *value);

#endif // - DISTANCE_SERVICE_H__ - //