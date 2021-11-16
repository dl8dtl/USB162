/*
 * config.h
 *
 * Created: 13.11.2021 16:49:38
 *  Author: Marvin
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

#include <avr/pgmspace.h>
#include <string.h>

/* Configurations for the setup */
#define STATUS_REMOTE_WAKEUP 0	// TODO not implemented, set to 0
#define STATUS_SELF_POWERED 1	// Set to 1 if the device is self powered (only as information for the host)

#define STRING_ID_MANUFACTURER 1
#define STRING_ID_PRODUCT 2
#define STRING_ID_SERIAL 3
#define STRING_ID_CONFIGURATION1 4

/* Device Descriptor, important informations for the host */
const __attribute__((packed)) USB_Device_Descriptor deviceDescriptor PROGMEM =
{
	.bLength = sizeof(USB_Device_Descriptor),
	.bDescriptorType = DESCRIPTOR_TYPE_DEVICE,
	.bcdUSB = 0x0110,
	.bDeviceClass = USB_CLASS_VENDOR_SPECIFIC,
	.bDeviceSubClass = USB_SUBCLASS_NONE,
	.bDeviceProtocol = USB_PROTOCOL_NONE,
	.bMaxPacketSize = CONTROL_ENDPOINT_SIZE,
	.idVendor = 0xFF,
	.idProduct = 0xFF,
	.bcdDevice = 0x0100,
	.iManufacturer = STRING_ID_MANUFACTURER,
	.iProduct = STRING_ID_PRODUCT,
	.iSerialNumber = STRING_ID_SERIAL,
	.bNumConfigurations = 1
};

/* Configuration, Interface, String and Endpoint-Descriptors (multiple possible) for the configurations */
const USB_Configuration_Descriptor configurationDescriptor PROGMEM =
{
	.bLength = sizeof(USB_Configuration_Descriptor),
	.bDescriptorType = DESCRIPTOR_TYPE_CONFIGURATION,
	.wTotalLength = sizeof(USB_Configuration_Descriptor) + sizeof(USB_Interface_Descriptor) + sizeof(USB_Endpoints_Descriptor),
	.bNumInterfaces = 1,
	.bConfigurationValue = 1,
	.iConfiguration = 0,
	.bmAttributes = CONFIGURATION_ATTRIBUTE_DEFAULT | CONFIGURATION_ATTRIBUTE_SELF_POWERED,
	.bMaxPower = 50
};

const USB_Interface_Descriptor interfaceDescriptor PROGMEM =
{
	.bLength = sizeof(USB_Interface_Descriptor),
	.bDescriptorType = DESCRIPTOR_TYPE_INTERFACE,
	.bInterfaceNumber = 0,
	.bAlternateSetting = 0,
	.bNumEndpoints = 1,
	.bInterfaceClass = USB_CLASS_VENDOR_SPECIFIC,
	.bInterfaceSubClass = 0,
	.bInterfaceProtocol = 0,
	.iInterface = 0
};

const USB_Endpoints_Descriptor endpointDescriptor PROGMEM =
{
	.bLength = sizeof(USB_Endpoints_Descriptor),
	.bDescriptorType = DESCRIPTOR_TYPE_ENDPOINT,
	.bEndpointAdress = 1 | ENDPOINT_ADDRESS_DIRECTION_IN,
	.bmAttributes = ENDPOINT_TYPE_BULK | ENDPOINT_SYNC_NONE | ENDPOINT_USAGE_DATA,
	.wMaxPacketSize = 64,
	.bInterval = 0
};

const USB_String_Descriptor manufacturerString PROGMEM = WCHAR_TO_STRING_DESCRIPTOR(L"TEST");
const USB_String_Descriptor productString PROGMEM = WCHAR_TO_STRING_DESCRIPTOR(L"AT90USB162 Test");
const USB_String_Descriptor serialString PROGMEM = WCHAR_TO_STRING_DESCRIPTOR(L"IDSJAKFHFS");
const USB_String_Descriptor configurationString PROGMEM = WCHAR_TO_STRING_DESCRIPTOR(L"KONFIGURATION 1");

/* Possible configuration structs, made with the descriptors from above (multiple possible) */
typedef struct
{
	USB_Configuration_Descriptor configurationDescriptor;
	USB_Interface_Descriptor interfaceDescriptor;
	USB_Endpoints_Descriptor endpointDescriptor;
} __attribute__((packed)) USB_Configuration1;

/* Possible configurations, made with the descriptors from above (multiple possible) */
const USB_Configuration1 configuration1 PROGMEM =
{
	.configurationDescriptor = configurationDescriptor,
	.interfaceDescriptor = interfaceDescriptor,
	.endpointDescriptor = endpointDescriptor
};

/* Getter for the possible Configurations and String descriptors, add new configurations to the switch cases */
const void* getConfigurationDescriptor(uint8_t type, uint8_t index, uint16_t* sizePointer)
{
	if (type == DESCRIPTOR_TYPE_CONFIGURATION)
	{
		switch (index)
		{
			/* All ConfigurationDescriptors */
			case 0: // Configuration 1
			*sizePointer = sizeof(USB_Configuration1);
			return &configuration1;
			break;
		}
	}
	else if (type == DESCRIPTOR_TYPE_STRING)
	{
		switch (index)
		{
 			/* All StringDescriptors */
			case STRING_ID_LANGUAGE: // Language descriptor, constant do not change
			*sizePointer = languageDescriptor.bLength;
			return &languageDescriptor;
			break;
			case STRING_ID_MANUFACTURER: // Example manufacturer descriptor
			*sizePointer = manufacturerString.bLength;
			return &manufacturerString;
			break;
			case STRING_ID_PRODUCT: // Example product descriptor
			*sizePointer = productString.bLength;
			return &productString;
			break;
			case STRING_ID_SERIAL: // Example serialnumber descriptor
			*sizePointer = serialString.bLength;
			return &serialString;
			break;
			case STRING_ID_CONFIGURATION1: // Example configuration descriptor
			*sizePointer = configurationString.bLength;
			return &configurationString;
			break;
		}
	}
	return 0;
}

/* Configuration of the described endpoints */
const void configureEndpoints()
{
	configEndpoint(1, 64, ENDPOINT_TYPE_BULK, true, false); // Example endpoint, ID 1 EPSIZE 16 EPTYPE bulk EPDIR in DOUBLEBANK false
}

#endif /* CONFIG_H_ */