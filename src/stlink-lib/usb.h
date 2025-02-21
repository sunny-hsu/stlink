/*
 * File:   usb.h
 * Author: karl
 */

#ifndef USB_H_
#define USB_H_

#include <stdbool.h>

#include <stlink.h>
#include <libusb_settings.h>
#include "logging.h"

#define STLINK_USB_VID_ST                   0x0483
#define STLINK_USB_PID_STLINK               0x3744
#define STLINK_USB_PID_STLINK_32L           0x3748
#define STLINK_USB_PID_STLINK_32L_AUDIO     0x374a
#define STLINK_USB_PID_STLINK_NUCLEO        0x374b
#define STLINK_USB_PID_STLINK_V2_1          0x3752
#define STLINK_USB_PID_STLINK_V3_USBLOADER  0x374d
#define STLINK_USB_PID_STLINK_V3E_PID       0x374e
#define STLINK_USB_PID_STLINK_V3S_PID       0x374f
#define STLINK_USB_PID_STLINK_V3_2VCP_PID   0x3753
#define STLINK_USB_PID_STLINK_V3_NO_MSD_PID 0x3754

#define STLINK_V1_USB_PID(pid) ((pid) == STLINK_USB_PID_STLINK)

#define STLINK_V2_USB_PID(pid) ((pid) == STLINK_USB_PID_STLINK_32L || \
                                (pid) == STLINK_USB_PID_STLINK_32L_AUDIO || \
                                (pid) == STLINK_USB_PID_STLINK_NUCLEO)

#define STLINK_V2_1_USB_PID(pid) ((pid) == STLINK_USB_PID_STLINK_V2_1)

#define STLINK_V3_USB_PID(pid) ((pid) == STLINK_USB_PID_STLINK_V3_USBLOADER || \
                                (pid) == STLINK_USB_PID_STLINK_V3E_PID || \
                                (pid) == STLINK_USB_PID_STLINK_V3S_PID || \
                                (pid) == STLINK_USB_PID_STLINK_V3_2VCP_PID || \
                                (pid) == STLINK_USB_PID_STLINK_V3_NO_MSD_PID)

#define STLINK_SUPPORTED_USB_PID(pid) (STLINK_V1_USB_PID(pid) || \
                                       STLINK_V2_USB_PID(pid) || \
                                       STLINK_V2_1_USB_PID(pid) || \
                                       STLINK_V3_USB_PID(pid))

#define STLINK_SG_SIZE 31
#define STLINK_CMD_SIZE 16

struct stlink_libusb {
    libusb_context* libusb_ctx;
    libusb_device_handle* usb_handle;
    unsigned int ep_req;
    unsigned int ep_rep;
    unsigned int ep_trace;
    int protocoll;
    unsigned int sg_transfer_idx;
    unsigned int cmd_len;
};

/**
 * Open a stlink
 * @param verbose Verbosity loglevel
 * @param connect Type of connect to target
 * @param serial  Serial number to search for, when NULL the first stlink found is opened (binary format)
 * @retval NULL   Error while opening the stlink
 * @retval !NULL  Stlink found and ready to use
 */
 
stlink_t *stlink_open_usb(enum ugly_loglevel verbose, enum connect_type connect, char serial[STLINK_SERIAL_BUFFER_SIZE], int freq);
size_t stlink_probe_usb(stlink_t **stdevs[], enum connect_type connect, int freq);
void stlink_probe_usb_free(stlink_t **stdevs[], size_t size);

#endif // USB_H_
