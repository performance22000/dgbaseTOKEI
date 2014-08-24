/**
 * digibase library for Arduino: TOKEI alarm pattern: sample
 *
 * Create: 14/6/24
 * Author: a.ide
 *
 * Mar 07 2014: Added Arduino and C++ Library
 * License: GNU GPL v2 (see License.txt)
 *
 * (c)2014 digi-base
 */
#ifndef DGBASE_ALARM00_H_
#define DGBASE_ALARM00_H_

#include "dgbaseTOKEI.h"

class dgbaseAlarm00 : public dgbaseTOKEI {
public:
	dgbaseAlarm00(uint8_t, WS2812*, cRGB, cRGB, cRGB);
//	~dgbaseAlarm00();
};

#endif /* DGBASE_ALARM00_H_ */
