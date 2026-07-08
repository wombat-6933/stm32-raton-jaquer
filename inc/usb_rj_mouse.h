#ifndef _RJ_USB_H_
#define _RJ_USB_H_

#include <stdint.h>
#include <stddef.h>
#include <libopencm3/usb/hid.h>
#include <libopencm3/usb/usbd.h>

#define OPEN_SOURCE_VID 0x1209
#define TEST_PID 0x1
#define N_USB_STRINGS 2
#define USB_HID_DESCRIPTOR_SIZE 9
#define USB_QUALIFIER_DESCRIPTOR_SIZE 10

struct usb_hid_report_fields {
   uint8_t bDescriptorType;
   uint16_t wDescriptorLength;
}__attribute__((packed));

struct usb_complete_hid_descriptor {
   struct usb_hid_descriptor hid_descriptor_fields;
   struct usb_hid_report_fields hid_report_fields;
} __attribute__((packed));

struct usb_qualifier_descriptor {
   uint8_t bLength;
   uint8_t bDescriptorType;
   uint16_t bcdUSB;
   uint8_t bDeviceClass;
   uint8_t bDeviceSubClass;
   uint8_t bDeviceProtocol;
   uint8_t bMaxPacketSize0;
   uint8_t bNumConfigurations;
   uint8_t bReserved;
}__attribute__((packed));


// BEGIN DECLS -----------
void usb_rj_init (void);
void usb_rj_poll (void);
#endif
