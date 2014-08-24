/**
 * digibase library for Arduino: TOKEI alarm pattern 3
 *
 * Create: 14/6/24
 * Author: a.ide
 *
 * Mar 07 2014: Added Arduino and C++ Library
 * License: GNU GPL v2 (see License.txt)
 *
 * (c)2014 digi-base
 */
#ifndef DGBASE_ALARM03_H_
#define DGBASE_ALARM03_H_

#include "dgbaseTOKEI.h"

class dgbaseAlarm03 : public dgbaseTOKEI {
public:
	dgbaseAlarm03(uint8_t, WS2812*, cRGB, cRGB, cRGB);
//	~dgbaseAlarm03();

};

#endif /* DGBASE_ALARM03_H_ */
