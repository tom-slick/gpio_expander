/*
 ___  _   _  _ __ ___    ___  | |_  ___   _   _ 
/ __|| | | || '_ ` _ \  / _ \ | __|/ _ \ | | | |
\__ \| |_| || | | | | || (_) || |_| (_) || |_| |
|___/ \__,_||_| |_| |_| \___/  \__|\___/  \__, |
                                          |___/ 
										  
	gpio_expander - An attemp to create a fast and universal library for drive many GPIO chips
	
model:			company:		pins:		protocol:		Special Features:
---------------------------------------------------------------------------------------------------------------------
mcp23016		Microchip		 16			I2C					INT
---------------------------------------------------------------------------------------------------------------------
Version history:
0.5b1: first release, just coded and never tested
0.5b2: fixed 2wire version, added portPullup, tested output mode (ok)
0.5b3: added some drivers
0.5b4: ability to include library inside other libraries.
---------------------------------------------------------------------------------------------------------------------
		Copyright (c) 2013-2014, s.u.m.o.t.o.y [sumotoy(at)gmail.com]
---------------------------------------------------------------------------------------------------------------------

    gpio_expander Library is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    gpio_expander Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

	
	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	Version:0.5b4
	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

/* ------------------------------ MCP23016 WIRING ------------------------------------

Basic Address:  00100 A2 A1 A0 (from 0x20 to 0x27)
A2,A1,A0 tied to ground = 0x20
				__ __
		GND   [|  U  |] IOA-7
		IOB-0 [|     |] IOA-6
		IOB-1 [|     |] IOA-5
		IOB-2 [|     |] IOA-4
		IOB-3 [|     |] IOA-3
		INT   [|     |] IOA-2
		IOB-4 [|     |] IOA-1
		GND   [|     |] IOA-0
		clk   [|     |] ++++
	test pin  [|     |] GND
		IOB-5 [|     |] A2
		IOB-6 [|     |] A1
		IOB-7 [|     |] A0
		scl   [|_____|] sda
		
Note: test pin must be float!
*/
#ifndef _MCP23016_H_
#define _MCP23016_H_

#include <inttypes.h>

#include "gpio_expander.h"


class mcp23016 : public gpio_expander
{

public:
	mcp23016(const uint8_t adrs);
	mcp23016();
	void			postSetup(const uint8_t adrs);
	virtual void 	begin(bool protocolInitOverride=false); //protocolInitOverride=true	will not init the SPI	

	
	void 			gpioPinMode(bool mode);						//set all pins to INPUT or OUTPUT
	void 			gpioPinMode(uint8_t pin, bool mode);		//set a unique pin as IN(1) or OUT (0)
	void 			gpioPort(uint16_t value);					//write data to all pins
	void			gpioPort(byte lowByte, byte highByte);		//same as abowe but uses 2 separate bytes
	uint16_t 		readGpioPort();								//read the state of the pins (all)
	uint16_t 		readGpioPortFast();							
	
	void 			gpioDigitalWrite(uint8_t pin, bool value);  //write data to one pin
	int 			gpioDigitalRead(uint8_t pin);				//read data from one pin
	unsigned int 	gpioRegisterRead(byte reg);					//read a chip register
	int 			gpioDigitalReadFast(uint8_t pin);
	void 			gpioRegisterWrite(byte reg,byte data);		//write a chip register
	//void			portPullup(bool data);						// true=pullup, false=pulldown all pins (gppu not for this chip)
	// direct access commands
    void			writeByte(byte addr, byte data);	
	void 			writeWord(byte addr, uint16_t data);
	uint16_t 		readAddress(byte addr);
	
	//------------------------- REGISTERS
	byte			IOCON;
	byte			IODIR;
	byte			GPIO;
	byte			IPOL;
	byte			INTCAP;
	byte			OLAT;
	
private:
	uint8_t 		_adrs;
	uint16_t		_gpioDirection;
	uint16_t		_gpioState;
	bool 			_error;
};
#endif