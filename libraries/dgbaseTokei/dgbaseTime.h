/**
 * digibase library for Arduino: TOKEI: time h m s & alarm
 *
 * Create: 14/7/13 v0
 * Author: a.ide
 *
 * Mar 07 2014: Added Arduino and C++ Library
 * License: GNU GPL v2 (see License.txt)
 *
 * (c)2014 digi-base
 */
#ifndef DGBASE_TIME_H_
#define DGBASE_TIME_H_

#include "dgbaseTOKEI.h"

#define TIME_HHCNT 5	//短針のLED数(通常は5)
#define TIME_MMCNT 3	//長針のLED数
#define TIME_SSCNT 1	//秒針のLED数

#define TIME_RGB2  4	//周囲の暗さ度合い(この場合、4分の1の明るさにする)

class dgbaseTime : public dgbaseTOKEI {
public:
	dgbaseTime(uint8_t pin, uint8_t cnt, WS2812* led, cRGB chh, cRGB cmm, cRGB css);
//	~dgbaseTime();

	void execute(int h, int m, int s, int wait);
	
	void setColor2(cRGB* leds, cRGB color, int8_t ledcnt);
	void setColor2(int8_t tm, cRGB* leds, int8_t ledcnt, cRGB* beforeleds);
	
	cRGB mLedsHour[TIME_HHCNT + 1];
	cRGB mLedsMinute[TIME_MMCNT + 1];
	cRGB mLedsSecond[TIME_SSCNT + 1];

	cRGB mLedsBeforeHour[TIME_HHCNT + 1];
	cRGB mLedsBeforeMinute[TIME_MMCNT + 1];
	cRGB mLedsBeforeSecond[TIME_SSCNT + 1];

	/** debug */
	int8_t mHour;
	int8_t mMinute;
	int8_t mSecond;
	int mCount;

	uint8_t mAlarmCnt;
	boolean isAlarm(int h, int m, int s);
	void executeAlarm();

//private:
	
};

#endif /* DGBASE_TIME_H_ */
