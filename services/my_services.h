#ifndef MY_SERVICES_H__
#define MY_SERVICES_H__
//include nrf libraries file
#include <string.h>
#include <stdint.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_gpio.h"
#include "app_error.h"

//include our file
#include "peripheral_info_service.h"
#include "distance_service.h"
#include "environment_service.h"




// defines services and characteristics UUIDs

#define BLE_UUID_MY_BASE_UUID              {{0x23, 0xD1, 0xBC, 0xEA, 0x5F, 0x78, 0x23, 0x15, 0xDE, 0xEF, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00}} // 128-bit base UUID

#define BLE_UUID_MY_DEVICE_SERVICE_UUID			     0x1523

#define BLE_UUID_PERIPHERAL_INFO_SERVICE_UUID                0x1526
#define BLE_UUID_FIRMWARE_VERSION_CHARACTERISTIC_UUID	     0x1530
#define BLE_UUID_BATTERY_LEVEL_CHARACTERISTIC_UUID	     0x1541

#define BLE_UUID_DISTANCE_SERVICE_UUID			     0x1528
#define BLE_UUID_CURRENT_DISTANCE_CHARACTERISTIC_UUID	     0x1544

#define BLE_UUID_ENVIRONMENT_SERVICE_UUID		     0x1527
#define BLE_UUID_TEMPERATURE_CHARACTERISTIC_UUID	     0x1542
#define BLE_UUID_LIGHTNESS_CHARACTERISTIC_UUID		     0x1533













#endif  MY_SERVICES_H__