#ifndef PERIPHERAL_INFO_SERVICE_H__
#define PERIPHERAL_INFO_SERVICE_H__


#include "my_services.h"


typedef struct 
{
  uint16_t service_handle;                            /**< Handle of Service (as provided by the BLE stack). */
  ble_gatts_char_handles_t    fv_char_handles;	      // firmware version characteristic handle
  ble_gatts_char_handles_t    bl_char_handles;	      // battery level characteristic handle 
} ble_pis_t;


void peripheral_info_serv_init (ble_pis_t *p_service);	//

void battery_level_char_update(ble_pis_t *p_service, uint16_t *conn_handle_in, int32_t *value);

#endif  /* PERIPHERAL_INFO_SERVICE_H__ */