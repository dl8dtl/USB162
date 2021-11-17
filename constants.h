/*
 * constants.h
 *
 * Created: 13.11.2021 15:54:24
 *  Author: Marvin
 */ 


#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <avr/pgmspace.h>

#define CONTROL_ENDPOINT_SIZE 64

/* bmRequestType Values */
#define SETUP_REQUEST_DATA_DIRECTION_BM 0x80
#define SETUP_REQUEST_DATA_DIRECTION_HOST_TO_DEVICE 128
#define SETUP_REQUEST_DATA_DIRECTION_DEVICE_TO_HOST 0
#define SETUP_REQUEST_TYPE_BM 0x60
#define SETUP_REQUEST_TYPE_STANDARD 0
#define SETUP_REQUEST_TYPE_CLASS 32
#define SETUP_REQUEST_TYPE_VENDOR 64
#define SETUP_REQUEST_RECIPIENT_BM 0x1F
#define SETUP_REQUEST_RECIPIENT_DEVICE 0
#define SETUP_REQUEST_RECIPIENT_INTERFACE 1
#define SETUP_REQUEST_RECIPIENT_ENDPOINT 2
#define SETUP_REQUEST_RECIPIENT_OTHER 3

/* bRequest Standard request ids */
#define STND_REQUEST_GET_STATUS 0x00
#define STND_REQUEST_SET_ADDRESS 0x05
#define STND_REQUEST_GET_DESCRIPTOR 0x06
#define STND_REQUEST_SET_CONFIGURATION 0x09
#define STND_REQUEST_GET_CONFIGURATION 0x08

typedef struct
{
	uint8_t		bmRequestType;	// Type of the setup request (data direction, recipient, type)
	uint8_t		bRequest;		// Request (get descriptor, set address, ...)
	uint16_t	wValue;			// Request specific value
	uint16_t	wIndex;			// Request specific value
	uint16_t	wLength;		// Length of data to send as answer of this request
} __attribute__((packed)) USB_Setup_Request;

/* bDescriptorType Descriptor types */
#define DESCRIPTOR_TYPE_DEVICE 0x01
#define DESCRIPTOR_TYPE_CONFIGURATION 0x02
#define DESCRIPTOR_TYPE_STRING 0x03
#define DESCRIPTOR_TYPE_INTERFACE 0x04
#define DESCRIPTOR_TYPE_ENDPOINT 0x05

/* Type classes of USB Devices */
#define USB_CLASS_DEVICE 0x0
#define USB_CLASS_AUDIO 0x1
#define USB_CLASS_COM_AND_CDCC 0x2
#define USB_CLASS_HID 0x3
#define USB_CLASS_PHYSICAL 0x5
#define USB_CLASS_STILL_IMAGING_SC1_P1 0x6
#define USB_CLASS_PRINTER 0x7
#define USB_CLASS_MASS_STORAGE 0x8
#define USB_CLASS_HUB_SC0_PX 0x9
#define USB_CLASS_CDC_DATA 0xA
#define USB_CLASS_SMART_CARD 0xB
#define USB_CLASS_CONTENT_SECURITY_SC0_P0 0xD
#define USB_CLASS_VIDEO 0xE
#define USB_CLASS_HEALTHCARE 0xF
#define USB_CLASS_AUDIO_VIDEO_DEVICE_SCX_P0 0x10
#define USB_CLASS_AUDIO_BILLBOARD_SC0_P0 0x11
#define USB_CLASS_TYPE_C_BRIDGE_DEVICE_SC0_P0 0x12
#define USB_CLASS_DIAGNOSTIC_DEVICE_SCX_PX 0xDC
#define USB_CLASS_WIRELESS_CONTROLLER_SCX_PX 0xE0
#define USB_CLASS_MISCELLANEOUS_SCX_PX 0xEF
#define USB_CLASS_APPLICATION_SPECIFIC_SCX_PX 0xFE
#define USB_CLASS_VENDOR_SPECIFIC 0xFF

/* Default value if no specific Protocol or Subclass is needed (Used by the USB Device types) */
#define USB_SUBCLASS_NONE 0x0
#define USB_PROTOCOL_NONE 0x0

typedef struct
{
	uint8_t		bLength;			// Byte count of this descriptor
	uint8_t		bDescriptorType;	// Type of the Descriptor
	uint16_t	bcdUSB;				// USB Specification number in 0xJJMN format
	uint8_t		bDeviceClass;		// Device type class code
	uint8_t		bDeviceSubClass;	// Device subtype class code
	uint8_t		bDeviceProtocol;	// Protocol code
	uint8_t		bMaxPacketSize;		// Maximum Packet size for EP0
	uint16_t	idVendor;			// Vendor id
	uint16_t	idProduct;			// Product id
	uint16_t	bcdDevice;			// Device release number in 0xJJMN format
	uint8_t		iManufacturer;		// Index of manufacturer string descriptor
	uint8_t		iProduct;			// Index of product string descriptor
	uint8_t		iSerialNumber;		// Index of serial number string descriptor
	uint8_t		bNumConfigurations;	// Number of possible configurations
} __attribute__((packed)) USB_Device_Descriptor;

/* bmAttributes Configuration attributes */
#define CONFIGURATION_ATTRIBUTE_DEFAULT 0x80
#define CONFIGURATION_ATTRIBUTE_SELF_POWERED 0x40
#define CONFIGURATION_ATTRIBUTE_REMOTE_WAKEUP 0x20

typedef struct  
{
	uint8_t		bLength;			// Byte count of this descriptor
	uint8_t		bDescriptorType;	// Type of the Descriptor
	uint16_t	wTotalLength;		// Byte count of configuration + all interface descriptors of this configuration
	uint8_t		bNumInterfaces;		// Number of interfaces for this configuration
	uint8_t		bConfigurationValue;// ID of this configuration
	uint8_t		iConfiguration;		// Index of configuration string descriptor
	uint8_t		bmAttributes;		// Attributes of this configuration
	uint8_t		bMaxPower;			// Power consumption in 2mA units
} __attribute__((packed)) USB_Configuration_Descriptor;

typedef struct
{
	uint8_t		bLength;			// Byte count of this descriptor
	uint8_t		bDescriptorType;	// Type of the Descriptor
	uint8_t		bInterfaceNumber;	// ID of this interface
	uint8_t		bAlternateSetting;	// Alternate interface id
	uint8_t		bNumEndpoints;		// Number of endpoints
	uint8_t		bInterfaceClass;	// Device type class code, zero if already defined in device descriptor
	uint8_t		bInterfaceSubClass;	// Device subtype class code, zero if already defined in device descriptor
	uint8_t		bInterfaceProtocol;	// Protocol, zero if already defined in device descriptor
	uint8_t		iInterface;			// Index of the interface string descriptor
} __attribute__((packed)) USB_Interface_Descriptor;

/* bEndpointAdress Endpoint addresses */
#define ENDPOINT_ADDRESS_DIRECTION_IN 0x80
#define ENDPOINT_ADDRESS_DIRECTION_OUT 0x00

/* bmAttributes Endpoint attributes */
#define ENDPOINT_TYPE_CONTROL 0x0
#define ENDPOINT_TYPE_ISOCHRONOUS 0x1
#define ENDPOINT_TYPE_BULK 0x2
#define ENDPOINT_TYPE_INTERRUPT 0x3
#define ENDPOINT_SYNC_NONE 0x00
#define ENDPOINT_SYNC_ASYNCHRONOUS 0x04
#define ENDPOINT_SYNC_ADAPTIVE 0x08
#define ENDPOINT_SYNC_SYNCHRONOUS 0x12
#define ENDPOINT_USAGE_DATA 0x00
#define ENDPOINT_USAGE_FEEDBACK 0x16
#define ENDPOINT_USAGE_FEEDBACK_DATA 0x32

typedef struct  
{
	uint8_t		bLength;			// Byte count of this descriptor
	uint8_t		bDescriptorType;	// Type of the Descriptor
	uint8_t		bEndpointAdress;	// Endpoint address and direction
	uint8_t		bmAttributes;		// Endpoint configurations
	uint16_t	wMaxPacketSize;		// Endpoints size
	uint8_t		bInterval;			// Interval in frames to poll data from this EP, ignored for control bulk and =1 for isochronous EPs
} __attribute__((packed)) USB_Endpoints_Descriptor;

/* Helper function tho define string descriptors */
#define WCHAR_TO_STRING_DESCRIPTOR(wchar) { \
    sizeof(USB_String_Descriptor) + sizeof(wchar) - 2, \
      DESCRIPTOR_TYPE_STRING, \
      wchar \
}

typedef struct  
{
	uint8_t			bLength;			// Byte count of this descriptor
	uint8_t			bDescriptorType;	// Type of the Descriptor
	const wchar_t wString[];			// List of chars representing the string
} __attribute__((packed)) USB_String_Descriptor;

/* Language ids for string descriptors */
#define LANG_ID_ENGLISH 0x0409
/* Language string descriptor id */
#define STRING_ID_LANGUAGE 0

/* Language descriptor */
typedef struct
{
	uint8_t			bLength;			// Byte count of this descriptor
	uint8_t			bDescriptorType;	// Type of the Descriptor
	uint16_t		wLANGID[1];			// Language ID as word
} __attribute__((packed)) USB_Lang_Descriptor;
const USB_Lang_Descriptor languageDescriptor PROGMEM =
{
	.bLength = 4,
	.bDescriptorType = DESCRIPTOR_TYPE_STRING,
	.wLANGID = {
		[0] = LANG_ID_ENGLISH
	}
};

#endif /* CONSTANTS_H_ */
