#include "usb_rj_mouse.h"
//TODO: WAKE_UP SUPPORT
//TODO: STUDY USB INTERRUPTS AND CLK ENABLES

static usbd_device * rj_dev_p = 0;
static uint8_t rj_control_buffer[128];
static const struct usb_complete_hid_descriptor rj_complete_hid_descriptor;
static void rj_config_setup (usbd_device *dev, uint16_t wValue);
static enum usbd_request_return_codes rj_qualifier_control_request(usbd_device *dev, struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
			void (**complete)(usbd_device *, struct usb_setup_data *));
static enum usbd_request_return_codes rj_hid_control_request(usbd_device *dev, struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
			void (**complete)(usbd_device *, struct usb_setup_data *));

static int usb_descriptor_type(uint16_t wValue)
{
	return wValue >> 8;
}

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
       .wTotalLength = (USB_DT_CONFIGURATION_SIZE + USB_DT_INTERFACE_SIZE + USB_HID_DESCRIPTOR_SIZE + USB_DT_ENDPOINT_SIZE),
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

//    .endpoint = &hid_endpoint,
      .extra = &rj_complete_hid_descriptor,
      .extralen = sizeof(rj_complete_hid_descriptor),

};

static const struct usb_hid_descriptor rj_hid_descriptor = {
      .bLength = USB_HID_DESCRIPTOR_SIZE,
      .bDescriptorType = USB_HID_DT_HID,
      .bcdHID = 0x0111,
      .bCountryCode = 0,
      .bNumDescriptors = 1,
};

static const struct usb_complete_hid_descriptor rj_complete_hid_descriptor = 
{
   .hid_descriptor_fields = rj_hid_descriptor,
   .hid_report_fields =
   {
      .bDescriptorType = USB_HID_DT_REPORT,
      .wDescriptorLength = sizeof(rj_hid_descriptor)
   }
};

static const struct usb_endpoint_descriptor rj_endpoint_descriptor = {
      .bLength = USB_DT_ENDPOINT_SIZE,
      .bDescriptorType = USB_DT_ENDPOINT,
      .bEndpointAddress = USB_ENDPOINT_ADDR_IN(1),
      .bmAttributes = USB_ENDPOINT_ATTR_INTERRUPT,
      .wMaxPacketSize = 4,
      .bInterval = 50,
};

static const uint8_t rj_hid_report_descriptor[] = {
	0x05, 0x01, /* USAGE_PAGE (Generic Desktop)         */
	0x09, 0x02, /* USAGE (Mouse)                        */
	0xa1, 0x01, /* COLLECTION (Application)             */
	0x09, 0x01, /*   USAGE (Pointer)                    */
	0xa1, 0x00, /*   COLLECTION (Physical)              */
	0x05, 0x09, /*     USAGE_PAGE (Button)              */
	0x19, 0x01, /*     USAGE_MINIMUM (Button 1)         */
	0x29, 0x03, /*     USAGE_MAXIMUM (Button 3)         */
	0x15, 0x00, /*     LOGICAL_MINIMUM (0)              */
	0x25, 0x01, /*     LOGICAL_MAXIMUM (1)              */
	0x95, 0x08, /*     REPORT_COUNT (8)                 */
	0x75, 0x01, /*     REPORT_SIZE (1)                  */
	0x81, 0x02, /*     INPUT (Data,Var,Abs)             */
	0x05, 0x01, /*     USAGE_PAGE (Generic Desktop)     */
	0x09, 0x30, /*     USAGE (X)                        */
	0x09, 0x31, /*     USAGE (Y)                        */
	0x09, 0x38, /*     USAGE (Wheel)                    */
	0x15, 0x81, /*     LOGICAL_MINIMUM (-127)           */
	0x25, 0x7f, /*     LOGICAL_MAXIMUM (127)            */
	0x75, 0x08, /*     REPORT_SIZE (8)                  */
	0x95, 0x03, /*     REPORT_COUNT (3)                 */
	0x81, 0x06, /*     INPUT (Data,Var,Rel)             */
	0xc0,       /*   END_COLLECTION                     */
	0xc0        /* END_COLLECTION                       */
};


// ----------- BEGIN DECLS ------------

void usb_rj_init (void)
{
   rj_dev_p = usbd_init(&st_usbfs_v1_usb_driver, &rj_device_descriptor, &rj_config_descriptor, rj_strings, N_USB_STRINGS, rj_control_buffer, sizeof(rj_control_buffer));

   usbd_register_set_config_callback(rj_dev_p, rj_config_setup);
}

void usb_rj_poll (void)
{
   usbd_poll(rj_dev_p);
}

static void rj_config_setup (usbd_device *dev, uint16_t wValue)
{

   (void)wValue;
   (void)dev;

   usbd_ep_setup(dev, USB_ENDPOINT_ADDR_IN(1), USB_ENDPOINT_ATTR_INTERRUPT, 4, NULL);

   usbd_register_control_callback(
		       dev,
		       USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_INTERFACE,
		       USB_REQ_TYPE_TYPE | USB_REQ_TYPE_RECIPIENT,
		       rj_hid_control_request);
   usbd_register_control_callback(
		       dev,
		       USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE,
		       USB_REQ_TYPE_TYPE | USB_REQ_TYPE_RECIPIENT,
		       rj_qualifier_control_request);
}

static enum usbd_request_return_codes rj_hid_control_request(usbd_device *dev, struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
			void (**complete)(usbd_device *, struct usb_setup_data *))
{
	(void)complete;
	(void)dev;

	if((req->bmRequestType != 0x81) ||
	   (req->bRequest != USB_REQ_GET_DESCRIPTOR) ||
	   (req->wValue != 0x2200))
		return USBD_REQ_NOTSUPP;

	/* Handle the HID report descriptor. */
	*buf = (uint8_t *)rj_hid_report_descriptor;
	*len = sizeof(rj_hid_report_descriptor);

	return USBD_REQ_HANDLED;
}

static enum usbd_request_return_codes rj_qualifier_control_request(usbd_device *dev, struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
			void (**complete)(usbd_device *, struct usb_setup_data *))
{
	(void)complete;
	(void)dev;

      if ((usb_descriptor_type(req->wValue)) == USB_DT_DEVICE_QUALIFIER)
      {
	 return USBD_REQ_HANDLED;
      }

      return USBD_REQ_NEXT_CALLBACK;

}
