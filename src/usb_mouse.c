#include "usb_mouse.h"

static const struct usb_device_descriptor rj_dev = {
	.bLength = USB_DT_DEVICE_SIZE,
	.bDescriptorType = USB_DT_DEVICE,
	.bcdUSB = 0x0200,
	.bDeviceClass = 0,
	.bDeviceSubClass = 0,
	.bDeviceProtocol = 0,
	.bMaxPacketSize0 = 8,

	.idVendor = OPEN_SOURCE_VID,
	.idProduct = TEST_PID,
	.bcdDevice = 0x0001,
	.iManufacturer = 1,
	.iProduct = 2,
	.iSerialNumber = 0,
	.bNumConfigurations = 1,
};

static const char *usb_strings[] = {
   "PepeFit Lab.",
   "USB RJ Mouse",
};

static const struct usb_config_descriptor rj_config = {
       .bLength = USB_DT_CONFIGURATION_SIZE,
       .bDescriptorType = USB_DT_CONFIGURATION,
       .wTotalLength = 0, //TODO: Calculate total configuration length in Bytes EP + Interfaces ..
       .bNumInterfaces = 1, //TODO: assert this
       .bConfigurationValue = 1,
       .iConfiguration = 0,
       .bmAttributes = 0x80,
       .bMaxPower = 0x32,
       .interface = ifaces_sourcesink,
};

