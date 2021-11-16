/*
 * usbl.h
 *
 * Created: 14.11.2021 12:47:22
 *  Author: Marvin
 */ 

#ifndef USBL_H_
#define USBL_H_

void setupUSB();
void configEndpoint(uint8_t num, uint8_t size, uint8_t type, bool inEP, bool doubleBank);

void readUSB(uint8_t* buffer, uint16_t length);
bool sendUSB();
void writeUSB(const uint8_t* buffer, uint16_t length, uint8_t epsize, bool fromPROGMEM);
bool waitForHost();
bool handleUSBSetupRequest();

#endif /* USBL_H_ */
