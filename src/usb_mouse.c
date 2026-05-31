#include "usb_mouse.h"
//TODO: WAKE_UP SUPPORT
//TODO: STUDY USB INTERRUPTS AND CLK ENABLES

static usbd_device * rj_dev_p = 0;
static uint8_t rj_control_buffer[128];

static const struct usb_device_descriptor rj_device_descriptor = {
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

static const char *rj_strings[N_USB_STRINGS] = {
   "PepeFit Lab.",
   "USB RJ Mouse",
};

static const struct usb_config_descriptor rj_config_descriptor = {
       .bLength = USB_DT_CONFIGURATION_SIZE,
       .bDescriptorType = USB_DT_CONFIGURATION,
       .wTotalLength = 0, //TODO: Calculate total configuration length in Bytes EP + Interfaces ..
       .bNumInterfaces = 1,
       .bConfigurationValue = 1,
       .iConfiguration = 0,
       .bmAttributes = USB_CONFIG_ATTR_DEFAULT | USB_CONFIG_ATTR_REMOTE_WAKEUP,
       .bMaxPower = 0x50, //100 mA
};

static const struct usb_interface_descriptor rj_interface_descriptor = {
      .bLength = USB_DT_INTERFACE_SIZE,
      .bDescriptorType = USB_DT_INTERFACE,
      .bInterfaceNumber = 0,
      .bAlternateSetting = 0,
      .bNumEndpoints = 1,
      .bInterfaceClass = USB_CLASS_HID,
      .bInterfaceSubClass = USB_HID_SUBCLASS_BOOT_INTERFACE,
      .bInterfaceProtocol = USB_HID_INTERFACE_PROTOCOL_MOUSE,
      .iInterface = 0,
};

static const struct usb_hid_descriptor_full rj_hid_descriptor {
      .bLength = USB_HID_DESCRIPTOR_SIZE,
      .bDescriptorType = USB_HID_DT_HID,
      .bcdHID = 0x0111,
      .bCountryCode = 0,
      .bNumDescriptors = 1,

};

// ----------- BEGIN DECLS ------------

void usb_rj_init (void)
{
   rj_dev_p = usbd_init(&st_usbfs_v1_usb_driver, &rj_device_descriptor, &rj_config_descriptor, rj_strings, N_USB_STRINGS, rj_control_buffer, sizeof(rj_control_buffer));
}
