

#include "peripheral_info_service.h"



uint32_t fv_char_add(ble_pis_t * p_service)  // function add firmware version characteristic 
{

    // OUR_JOB: Step 2.A, Add a custom characteristic UUID
	uint32_t            err_code;
ble_uuid_t          char_uuid;
ble_uuid128_t       base_uuid = BLE_UUID_MY_BASE_UUID;
char_uuid.uuid      = BLE_UUID_FIRMWARE_VERSION_CHARACTERISTIC_UUID;
err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid.type);
APP_ERROR_CHECK(err_code);

    
    // OUR_JOB: Step 2.F Add read/write properties to our characteristic
    ble_gatts_char_md_t char_md;
    memset(&char_md, 0, sizeof(char_md));
char_md.char_props.read = 1;
char_md.char_props.write = 0;



    
    // OUR_JOB: Step 3.A, Configuring Client Characteristic Configuration Descriptor metadata and add to char_md structure
    ble_gatts_attr_md_t cccd_md;
    memset(&cccd_md, 0, sizeof(cccd_md));
BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
cccd_md.vloc                = BLE_GATTS_VLOC_STACK;    
char_md.p_cccd_md           = &cccd_md;
char_md.char_props.notify   = 0;

   

    // OUR_JOB: Step 2.B, Configure the attribute metadata
    ble_gatts_attr_md_t attr_md;
    memset(&attr_md, 0, sizeof(attr_md));  
attr_md.vloc        = BLE_GATTS_VLOC_STACK;
	
    
    
    // OUR_JOB: Step 2.G, Set read/write security levels to our characteristic
BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.write_perm);
    
    // OUR_JOB: Step 2.C, Configure the characteristic value attribute
    ble_gatts_attr_t    attr_char_value;
    memset(&attr_char_value, 0, sizeof(attr_char_value));
attr_char_value.p_uuid      = &char_uuid;
attr_char_value.p_attr_md   = &attr_md;


    
    // OUR_JOB: Step 2.H, Set characteristic length in number of bytes
attr_char_value.max_len     = 4;
attr_char_value.init_len    = 4;
uint8_t value[4]            = {0x00,0x00,0x00,0x00};
attr_char_value.p_value     = value;

    // OUR_JOB: Step 2.E, Add our new characteristic to the service
err_code = sd_ble_gatts_characteristic_add(p_service->service_handle,
                                   &char_md,
                                   &attr_char_value,
                                   &p_service->fv_char_handles);
APP_ERROR_CHECK(err_code);

    return NRF_SUCCESS;
}
 
//===================================================================================================================
  
  
uint32_t battery_level_char_add(ble_pis_t * p_service)
{

    // OUR_JOB: Step 2.A, Add a custom characteristic UUID
	uint32_t            err_code;
ble_uuid_t          char_uuid;
ble_uuid128_t       base_uuid = BLE_UUID_MY_BASE_UUID;
char_uuid.uuid      = BLE_UUID_BATTERY_LEVEL_CHARACTERISTIC_UUID;
err_code = sd_ble_uuid_vs_add(&base_uuid, &char_uuid.type);
APP_ERROR_CHECK(err_code);

    
    // OUR_JOB: Step 2.F Add read/write properties to our characteristic
    ble_gatts_char_md_t char_md;
    memset(&char_md, 0, sizeof(char_md));
char_md.char_props.read = 1;
char_md.char_props.write = 0;



    
    // OUR_JOB: Step 3.A, Configuring Client Characteristic Configuration Descriptor metadata and add to char_md structure
    ble_gatts_attr_md_t cccd_md;
    memset(&cccd_md, 0, sizeof(cccd_md));
BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
cccd_md.vloc                = BLE_GATTS_VLOC_STACK;    
char_md.p_cccd_md           = &cccd_md;
char_md.char_props.notify   = 1;
 

    // OUR_JOB: Step 2.B, Configure the attribute metadata
    ble_gatts_attr_md_t attr_md;
    memset(&attr_md, 0, sizeof(attr_md));  
    attr_md.vloc   =  BLE_GATTS_VLOC_STACK;
	
    
    
    // OUR_JOB: Step 2.G, Set read/write security levels to our characteristic
BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS (&attr_md.write_perm);

   
    // OUR_JOB: Step 2.C, Configure the characteristic value attribute
    ble_gatts_attr_t    attr_char_value;
    memset(&attr_char_value, 0, sizeof(attr_char_value));
attr_char_value.p_uuid      = &char_uuid;
attr_char_value.p_attr_md   = &attr_md;


    
    // OUR_JOB: Step 2.H, Set characteristic length in number of bytes
attr_char_value.max_len     = 4;
attr_char_value.init_len    = 4;
uint8_t value[4]            = {0x00,0x00,0x00,0x00};
attr_char_value.p_value     = value;

    // OUR_JOB: Step 2.E, Add our new characteristic to the service
err_code = sd_ble_gatts_characteristic_add(p_service->service_handle,
                                   &char_md,
                                   &attr_char_value,
                                   &p_service->bl_char_handles);
APP_ERROR_CHECK(err_code);

    return NRF_SUCCESS;
}

  //======================================================================================================================

void peripheral_info_serv_init (ble_pis_t *p_service)
{
      uint32_t   err_code; // Variable to hold return codes from library and softdevice functions

    //  Declare 16-bit service and 128-bit base UUIDs and add them to the BLE stack
    ble_uuid_t        service_uuid;
    ble_uuid128_t     base_uuid = BLE_UUID_MY_BASE_UUID;
    service_uuid.uuid = BLE_UUID_PERIPHERAL_INFO_SERVICE_UUID;
    err_code = sd_ble_uuid_vs_add(&base_uuid, &service_uuid.type);
    APP_ERROR_CHECK(err_code);    
    
    //  Set our service connection handle to default value. I.e. an invalid handle since we are not yet in a connection.

    // : Add our service
    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &service_uuid, &p_service->service_handle);
    APP_ERROR_CHECK(err_code);
    
    // add characteristic 
    fv_char_add(p_service);
    //battery_level_char_add(p_service);
    
}


  
  void battery_level_char_update(ble_pis_t *p_service, uint16_t *conn_handle_in,  int32_t *value)
{
       uint16_t               len = 4;
       ble_gatts_hvx_params_t hvx_params;
       memset(&hvx_params, 0, sizeof(hvx_params));
       
       
       hvx_params.handle = p_service->bl_char_handles.value_handle;
       hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
       hvx_params.offset = 0;
       hvx_params.p_len  = &len;
       hvx_params.p_data = (uint8_t*)value;  
       
       uint32_t err_code;
       
       err_code = sd_ble_gatts_hvx(*conn_handle_in, &hvx_params);

}