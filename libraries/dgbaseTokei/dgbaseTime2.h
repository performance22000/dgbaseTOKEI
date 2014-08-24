/**
 * digibase library for Arduino: TOKEI: time h m s
 *
 * Create: 14/7/25 v0.1
 * Author: a.ide
 *
 * Mar 07 2014: Added Arduino and C++ Library
 * License: GNU GPL v2 (see License.txt)
 *
 * (c)2014 digi-base
 */
#ifndef DGBASE_TIME2_H_
#define DGBASE_TIME2_H_

#include "dgbaseTime.h"

class dgbaseTime2 : public dgbaseTime {
public:
	dgbaseTime2(uint8_t pin, uint8_t cnt, WS2812* led, cRGB chh, cRGB cmm, cRGB css);
//	~dgbaseTime2();

	void execute(int h, int m, int s, int wait);
	void execGradation();

private:
	boolean mIsHour;
	boolean mIsMinute;

	//gradation
	void setColor3(int8_t tm, cRGB* leds, int8_t ledcnt, cRGB* boforeleds, int ccoffset1, int ccoffset2);

};

#endif /* DGBASE_TIME2_H_ */
