/**
 * digibase library for Arduino: TOKEI alarm pattern 2: 流れ星 右回り
 *
 * Create: 14/6/24
 * Author: a.ide
 *
 * Mar 07 2014: Added Arduino and C++ Library
 * License: GNU GPL v2 (see License.txt)
 *
 * (c)2014 digi-base
 */
#ifndef DGBASE_ALARM02_H_
#define DGBASE_ALARM02_H_

#include "dgbaseTOKEI.h"

class dgbaseAlarm02 : public dgbaseTOKEI {
public:
	dgbaseAlarm02(uint8_t, WS2812*, cRGB, cRGB, cRGB);
//	~dgbaseAlarm02();

};

#endif /* DGBASE_ALARM02_H_ */
