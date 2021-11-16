/*
 * usbl.cpp
 *
 * Created: 14.11.2021 12:33:25
 *  Author: Marvin
 */ 

#include <avr/interrupt.h>
#include "usbl.h"
#include "bits.h"
#include "constants.h"
#include "config.h"

uint8_t activeConfiguration = 0;

void setupUSB()
{
	
	// Reset USB controller
	clr(USBCON, USBE);
	set(USBCON, USBE);
	
	// Enable and configure PLL
	clr(USBCON, FRZCLK);
	clr(PLLCSR, PLLP0);
	clr(PLLCSR, PLLP1);
	clr(PLLCSR, PLLP2);
	set(PLLCSR, PLLE);
	while (!get(PLLCSR, PLOCK))
	
	// Enable EORSTI and SOFI interrupt
	set(UDIEN, EORSTE);
	set(UDIEN, SOFE);
	sei();
	
	// Enable data lines
	clr(UDCON, DETACH);
	
}

void configEndpoint(uint8_t num, uint8_t size, uint8_t type, bool inEP, bool doubleBank)
{
	uint8_t selectedEP = UENUM;
	
	// Enable EP
	UENUM = num;
	set(UECONX, EPEN);
	// Set EPDIR
	if (inEP) set(UECFG0X, EPDIR) else clr(UECFG0X, EPDIR);		
	// Set EPTYPE
	if (get(type, 0)) set(UECFG0X, EPTYPE0) else clr(UECFG0X, EPTYPE0);
	if (get(type, 1)) set(UECFG0X, EPTYPE1) else clr(UECFG0X, EPTYPE1);
	// EPSIZE 64 byte
	clr(UECFG1X, EPSIZE2);
	if (size == 16) {		// Size 16
	clr(UECFG1X, EPSIZE1);
	set(UECFG1X, EPSIZE0);
	} else if (size == 32) {// Size 32
	set(UECFG1X, EPSIZE1);
	clr(UECFG1X, EPSIZE0);
	} else if (size == 64) {// Size 64
	set(UECFG1X, EPSIZE1);
	set(UECFG1X, EPSIZE0);
	} else {				// Size 8
	clr(UECFG1X, EPSIZE1);
	clr(UECFG1X, EPSIZE0);
	};
	// EPBANK
	(UECFG1X, EPBK1);
	if (doubleBank) set(UECFG1X, EPBK0) else clr(UECFG1X, EPBK0);
	// Allocate memory
	set(UECFG1X, ALLOC);
	while (!get(UESTA0X, CFGOK));	// Wait for config OK
	
	UENUM = selectedEP;
}

ISR(USB_GEN_vect)
{
	uint8_t genint = UDINT;
	UDINT = 0;
	
	// On USB reset
	if (get(genint, EORSTI))
	{
		// Reset USB Address
		UDADDR = 0;
		
		// Configure EP0
		configEndpoint(0, CONTROL_ENDPOINT_SIZE, ENDPOINT_TYPE_CONTROL, false, false);
		// Configure device spezific endpoints
		configureEndpoints();
		
		// Enable RXSTPI interrupt for EP0
		set(UEIENX, RXSTPE);
		
		activeConfiguration = 0;
		
	}
	
}

ISR(USB_COM_vect)
{
	
	// Get interrupts only from EP0
	uint8_t selectedEP = UENUM;
	UENUM = 0;
	
	uint8_t comint = UEINTX;
	
	// On new setup request
	if (get(comint, RXSTPI))
	{
		// Read and handle request from buffer
		handleUSBSetupRequest();
	}
	
	UENUM = selectedEP;
	
}

// Read n bytes of the received data in the given buffer
void readUSB(uint8_t* buffer, uint16_t length)
{
	while (length--)
	{
		*buffer++ = UEDATX; // Read data in buffer
	}
}

// Send the content of the FIFO to the host, returns false if aborted from host
bool sendUSB()
{
	clr(UEINTX, TXINI);				// Clear TXINI byte to send data
	bool abort = waitForHost();		// Wait for acknowledge or abort from host
	return !abort;					// Return false if aborted from host
}

// Wait for the TXINI Bit or abort from host (
bool waitForHost()
{
	int timeout = 0;
	while (!(UEINTX & ((1 << TXINI) | (1 << RXOUTI))) && timeout < 6000) timeout++;
	return get(UEINTX, RXOUTI);
}

// Writes n bytes from the given buffer in the USB buffer (FIFO), and send it to the host
void writeUSB(const uint8_t* buffer, uint16_t length, uint8_t epsize, bool fromPROGMEM)
{
	uint8_t sentBytes = 0;
	while (length--)
	{
		// Write Data in FIFO
		if (fromPROGMEM) {
			UEDATX = pgm_read_byte(buffer++);
		}
		else
		{
			UEDATX = *buffer++;
		}
		sentBytes++;
		
		// Trigger send if FIFO full or all data written
		if (sentBytes == epsize || length == 0)
		{
			// Send data or return if aborted from host
			sentBytes = 0;
			if (!sendUSB()) return;
		}
	}
	
	// Wait for status
	bool abort = waitForHost();
	if (abort) return;
	clr(UEINTX, RXOUTI);
}

// Handles all standard requests, return false if the request is not a standard request
bool handleUSBSetupRequest()
{
	
	// Read request
	USB_Setup_Request request;
	readUSB((uint8_t*)&request, sizeof(USB_Setup_Request));
	
	// Clear interrupt bit to begin data stage
	clr(UEINTX, RXSTPI);
	
	// If standard request and recipient device
	if ((request.bmRequestType & SETUP_REQUEST_TYPE_BM) == SETUP_REQUEST_TYPE_STANDARD)
	{
		uint8_t validRequest = 1;
		switch (request.bRequest)
		{
			case STND_REQUEST_GET_STATUS: {
				uint16_t status = (STATUS_REMOTE_WAKEUP << 1) | (STATUS_SELF_POWERED << 0); // Make status word
				writeUSB((uint8_t*)&status, 2, CONTROL_ENDPOINT_SIZE, false);
				break;
			}
			case STND_REQUEST_SET_ADDRESS: {
				UDADDR = (UDADDR & (1 << ADDEN)) | (request.wValue & 0x7f);
				sendUSB(); // Set empty packet
				set(UDADDR, ADDEN);
				break;
			}
			case STND_REQUEST_GET_DESCRIPTOR: {
				// Read descriptor type and index
				uint8_t descriptorType = request.wValue >> 8;
				uint8_t descriptorIndex = request.wValue & 0xFF;
				
				// Get matching descriptor
				const uint8_t* descriptorPointer = 0;
				uint16_t descriptorSize = 0;
				switch (descriptorType)
				{
					case DESCRIPTOR_TYPE_DEVICE:
					descriptorPointer = (uint8_t*)&deviceDescriptor;
					descriptorSize = sizeof(USB_Device_Descriptor);
					break;
					case DESCRIPTOR_TYPE_STRING:
					case DESCRIPTOR_TYPE_CONFIGURATION:
					descriptorPointer = (uint8_t*)getConfigurationDescriptor(descriptorType, descriptorIndex, &descriptorSize);
					break;
				}
				
				if (descriptorSize == 0)
				{
					// If requested descriptor not implemented stall request
					validRequest = 0;
				}
				else
				{
					// Send descriptor to host
					uint16_t requestedLength = descriptorSize;
					if (request.wLength < requestedLength) requestedLength = request.wLength;
					writeUSB(descriptorPointer, requestedLength, CONTROL_ENDPOINT_SIZE, true);
				}
				break;
			}
			case STND_REQUEST_SET_CONFIGURATION: {
				activeConfiguration = request.wValue & 0xFF;
				sendUSB(); // Send empty packet
				break;
			}
// 			case STND_REQUEST_GET_CONFIGURATION: {
// 				writeUSB(&activeConfiguration, 1, CONTROL_ENDPOINT_SIZE, false);
// 				break;
// 			}
			default: {
				// Not implemented -> stall it
				validRequest = 0;
				break;
			}
		}
		
		// If a request was not valid, stall it
		if (!validRequest) set(UECONX, STALLRQ);
		
		return true;
	}
	return false; // Not a standard request, return false
}
