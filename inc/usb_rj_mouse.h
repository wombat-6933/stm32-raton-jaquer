#ifndef _RJ_USB_H_
#define _RJ_USB_H_

#include <stdint.h>
#include <libopencm3/usb/hid.h>
#include <libopencm3/usb/usbd.h>

#define OPEN_SOURCE_VID 0x1209
#define TEST_PID 0x1
#define N_USB_STRINGS 2
#define USB_HID_DESCRIPTOR_SIZE sizeof(struct usb_complete_hid_descriptor)

struct usb_hid_report_fields {
   uint8_t bDescriptorType;
   uint16_t wDescriptorLength;
}__attribute__((packed));

struct usb_complete_hid_descriptor {
   struct usb_hid_descriptor hid_descriptor_fields;
   struct usb_hid_report_fields hid_report_fields;
} __attribute__((packed));

// BEGIN DECLS -----------
void usb_rj_init (void);
#endif
