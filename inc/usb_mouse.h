#ifndef _RJ_USB_H_
#define _RJ_USB_H_

#define OPEN_SOURCE_VID 0x1209
#define TEST_PID 0x1
#define N_USB_STRINGS 2

struct usb_hid_descriptor_full {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t bcdHID;
	uint8_t bCountryCode;
	uint8_t bNumDescriptors;
	uint8_t bDescriptorType;
	uint16_t wDescriptorLength;
} __attribute__((packed));

#endif
