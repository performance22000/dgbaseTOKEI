/**
 * digibase library for Arduino: TOKEI temp 温度
 *
 * Create: 14/7/20
 * Author: a.ide
 *
 * Mar 07 2014: Added Arduino and C++ Library
 * License: GNU GPL v2 (see License.txt)
 *
 * (c)2014 digi-base
 */
#ifndef DGBASE_TEMP_H_
#define DGBASE_TEMP_H_

#include "dgbaseTOKEI.h"

class dgbaseTemp : public dgbaseTOKEI {
public:
	dgbaseTemp(uint8_t ledcnt, WS2812* LED, cRGB chh, cRGB cmm, cRGB css);
//	~dgbaseTemp();

	void execute(float mpl, float dht, int wait, int afterwait);	//temp
	void execute(float humi, int wait, int afterwait);				//humi

	float mTempMpl;
	float mTempDht;
	float mHumi;

private:
	void execTempPlus(int8_t mpl, int wait, int afterwait, cRGB color);	//0以上
	void execTempMinus(int8_t mpl, int wait, int afterwait);			//0より小さい

};

#endif /* DGBASE_TEMP_H_ */
