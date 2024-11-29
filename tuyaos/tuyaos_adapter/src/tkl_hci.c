/**
 * @file tkl_hci.c
 * @brief this file was auto-generated by tuyaos v&v tools, developer can add implements between BEGIN and END
 * 
 * @warning: changes between user 'BEGIN' and 'END' will be keeped when run tuyaos v&v tools
 *           changes in other place will be overwrited and lost
 *
 * @copyright Copyright 2020-2021 Tuya Inc. All Rights Reserved.
 * 
 */

// --- BEGIN: user defines and implements ---
#include "tkl_hci.h"
#include "tuya_error_code.h"
#include "hci.h"

#if !CFG_USE_BK_HOST
extern void ble_entry(void);

static BOOL_T m_tkl_hci_is_init = FALSE;
// --- END: user defines and implements ---

/**
 * @brief   Function for initializing the bluetooth host-controller interface
 * @param   void
 * @return  SUCCESS             Initialized successfully.
 *          ERROR
 * */
OPERATE_RET tkl_hci_init(void)
{
    // --- BEGIN: user implements ---
    if(m_tkl_hci_is_init){
        return OPRT_OK;
    }
    hci_driver_open();
    ble_entry();

    m_tkl_hci_is_init = TRUE;
    return OPRT_OK;
    // --- END: user implements ---
}

/**
 * @brief   Function for de-initializing the bluetooth host-controller interface
 * @param   void
 * @return  SUCCESS             De-initialized successfully.
 *          ERROR
 * */
OPERATE_RET tkl_hci_deinit(void)
{
    // --- BEGIN: user implements ---
    bk_printf("\r\ntkl_hci_deinit\r\n");
    return OPRT_OK;
    // --- END: user implements ---
}

/**
 * @brief   [Linux/Android] Function for reseting the bluetooth host-controller interface
 *          Try to recover socket or reopen uart/usb interface.
 * @param   void
 * @return  SUCCESS             Reset successfully.
 *          ERROR
 * @note    [Special Interface] If running in RTOS, we may not support this feature. 
 *          And you can report OPRT_NOT_SUPPORT if you dont need it.
 * */
OPERATE_RET tkl_hci_reset(void)
{
    // --- BEGIN: user implements ---
    bk_printf("\r\ntkl_hci_reset\r\n");
    return OPRT_OK;
    // --- END: user implements ---
}

/**
 * @brief   Send HCI-Command Packet to controller from host.
 *          The HCI Command packet is used to send commands to the Controller from
 *          the Host. The format of the HCI Command packet is shown @Rule
 *          Controllers shall be able to accept HCI Command packets with up to 255 bytes
 *          of data excluding the HCI Command packet header. The HCI Command packet
 *          header is the first 3 octets of the packet.
 *
 * @param   p_buf               Follow Core Spec. Refer to @Rule
 *          length              Indicate the length of the buffer. it can be "opcode + 1(len) + Parameter len";
 * @return  SUCCESS             Initialized successfully.
 *          ERROR
 *
 * @Spec    BLUETOOTH CORE SPECIFICATION Version 5.2 | Vol 4, Part E, 5-4.1
 * @Rule        2 bytes              1 byte              1 byte           N bytes
 *          OpCode(OCF+OGF) + Parameter Total Length + Parameter 0 ... + Parameter N
 * @Note    The OpCode Group Field (OGF), OpCode Command Field (OCF). 
 * */
OPERATE_RET tkl_hci_cmd_packet_send(const uint8_t *p_buf, uint16_t buf_len)
{
    // --- BEGIN: user implements ---
    return hci_driver_send(HCI_CMD_MSG_TYPE, buf_len, (uint8_t *)p_buf);
    // --- END: user implements ---
}

/**
 * @brief   Send HCI-Command Packet to controller from host.
 *           HCI ACL Data packets are used to exchange data between the Host and Controller.
 *           Hosts and Controllers shall be able to accept HCI ACL Data packets with up to
 *           27 bytes of data excluding the HCI ACL Data packet header on
 *           Connection_Handles associated with an LE-U logical link.The HCI ACL Data
 *           packet header is the first 4 octets of the packet.
 *
 * @param   p_buf               Follow Core Spec. Refer to @Rule
 *          length              Indicate the length of the buffer. it can be "Handle + PB Flag 
 *                              + PC Flag + Data Total Length";
 * @return  SUCCESS             Initialized successfully.
 *          ERROR
 *
 * @Spec    BLUETOOTH CORE SPECIFICATION Version 5.2 | Vol 4, Part E, 5-4.2
 * @Rule                                  2 bytes                             2 bytes         N bytes
 *          (Connection Handle + PB Flag(12-14bit) + PC Flag(14-16bit)) + Data Total Length + Data
 * @Note    PB Flag: Packet_Boundary_Flag; PB Flag: Broadcast_Flag;
 * */
OPERATE_RET tkl_hci_acl_packet_send(const uint8_t *p_buf, uint16_t buf_len)
{
    // --- BEGIN: user implements ---
    return hci_driver_send(HCI_ACL_MSG_TYPE, buf_len, (uint8_t *)p_buf);
    // --- END: user implements ---
}

/**
 * @brief   Register the hci callback, while receiving "hci-event" or "acl-packet" data from controller,
 *          we will post these data into host stack.
 *          hci_evt_cb: The Host shall be able to accept HCI Event packets with up to 255 octets of data
 *          excluding the HCI Event packet header
 *          acl_pkt_cb: Refer to @tkl_hci_acl_packet_send
 *
 * @param   hci_evt_cb          Indicate the HCI Event callback.
 *          acl_pkt_cb          Indicate the ACL packet callback.
 * @return  SUCCESS             Initialized successfully.
 *          ERROR
 *
 * @Spec    BLUETOOTH CORE SPECIFICATION Version 5.2 | Vol 4, Part E, 5-4.4
 *          For More Event And Commnad Details:
 *          BLUETOOTH CORE SPECIFICATION Version 5.2 | Vol 4, Part E, 7-x
 *
 * @Rule    hci_evt_cb:
               1 byte        1 byte                1 byte                       N bytes
 *          Event Code + Parameter Total Length+ Event Parameter 0 + ... + Event Parameter N
 * */
OPERATE_RET tkl_hci_callback_register(const TKL_HCI_FUNC_CB hci_evt_cb, const TKL_HCI_FUNC_CB acl_pkt_cb)
{
    // --- BEGIN: user implements ---
    bk_printf("\r\ntkl_hci_callback_register\r\n");
    hci_set_event_callback((hci_func_evt_cb)hci_evt_cb, (hci_func_evt_cb)acl_pkt_cb);
    return OPRT_OK;
    // --- END: user implements ---
}
#endif