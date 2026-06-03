#ifndef _RJ_USB_H_
#define _RJ_USB_H_

#define OPEN_SOURCE_VID 0x1209
#define TEST_PID 0x1
#define N_USB_STRINGS 2

struct usb_complete_hid_descriptor {
   struct usb_hid_descriptor;
   struct usb_hid_report_fields {
      uint8_t bDescriptorType;
      uint16_t wDescriptorLength;
   }__attribute__((packed));
} __attribute__((packed));

#endif
