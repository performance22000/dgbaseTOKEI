/**
 * digibase library for Arduino: TOKEI alarm pattern 1: 流れ星 左回り
 *
 * Create: 14/6/24
 * Author: a.ide
 *
 * Mar 07 2014: Added Arduino and C++ Library
 * License: GNU GPL v2 (see License.txt)
 *
 * (c)2014 digi-base
 */
#ifndef DGBASE_ALARM01_H_
#define DGBASE_ALARM01_H_

#include "dgbaseTOKEI.h"

class dgbaseAlarm01 : public dgbaseTOKEI {
public:
	dgbaseAlarm01(uint8_t, WS2812*, cRGB, cRGB, cRGB);
//	~dgbaseAlarm01();

};

#endif /* DGBASE_ALARM01_H_ */
