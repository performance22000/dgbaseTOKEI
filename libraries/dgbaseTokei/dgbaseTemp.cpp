/**
 * digibase library for Arduino: TOKEI temp 温度の表示
 *
 * Create: 14/7/20
 * Author: a.ide
 *
 * Mar 07 2014: Added Arduino and C++ Library
 * License: GNU GPL v2 (see License.txt)
 *
 * (c)2014 digi-base
 */
#include "dgbaseTemp.h"

dgbaseTemp::dgbaseTemp(uint8_t ledcnt, WS2812* LED, cRGB chh, cRGB cmm, cRGB css)
	: dgbaseTOKEI(ledcnt, LED, chh, cmm, css)
{
}

//温度
void dgbaseTemp::execute(float mpl, float dht, int wait, int afterwait) {
	mTempMpl = mpl;
	//LED処理
	if (mpl >= 0) {
		execTempPlus((int8_t)mpl, wait, afterwait, mColormm);
	}else{
		execTempMinus((int8_t)mpl, wait, afterwait);
	}
}

//湿度
void dgbaseTemp::execute(float humi, int wait, int afterwait) {
	mHumi = humi;
	humi = ((humi / 1.6) + 0.9);
	//LED処理(右回りの温度と同じ方向)
	execTempPlus(humi, wait, afterwait, mColorhh);
}


//private:

//温度(0度以上) LED処理は右回り
void dgbaseTemp::execTempPlus(int8_t mpl, int wait, int afterwait, cRGB color) {
	cRGB rgbs[mLedCount], tmps[mLedCount], cc;
	int8_t i = 0;
	for (; i < mpl; i++) {
		rgbs[i] = getColor(i);
		tmps[i] = changeColor(mColorbk, (i + 1), mColorbk, color);
	}
	for (; i < mLedCount; i++) {
		rgbs[i] = getColor(i);
		tmps[i] = mColorbk;
	}
	i = 0;
	for (; i < mLedCount; i++) {
		for (int8_t j = 0; j < mLedCount; j++) {
			rgbs[j] = changeColor(rgbs[j], -2, mColorbk, mColorss);
			if (j < i) {
				cc = margeColor(rgbs[j], tmps[j]);
			}else{
				cc = rgbs[j];
			}
			setColor(j, cc);
		}
		syncLED(wait);
	}
	delay(afterwait);
}

//温度(0より小さい) LED処理は左回り
void dgbaseTemp::execTempMinus(int8_t mpl, int wait, int afterwait) {
	cRGB rgbs[mLedCount], tmps[mLedCount], cc;
	int8_t i = 0;
	for (; i >= mpl; i--) {
		cc = getColor(i);
		rgbs[mLedPosition] = cc;
		tmps[mLedPosition] = changeColor(mColorbk, (mLedPosition + 1), mColorbk, mColormm);
	}
	for (; i >= (mLedCount * (-1)); i--) {
		cc = getColor(i);
		rgbs[mLedPosition] = cc;
		tmps[mLedPosition] = mColorbk;
	}
	i = -1;
	for (; i >= (mLedCount * (-1)); i--) {
		for (int8_t j = 0; j < mLedCount; j++) {
			rgbs[j] = changeColor(rgbs[j], -2, mColorbk, mColorss);
			if (j < (i * (-1))) {
				cc = margeColor(rgbs[j], tmps[j]);
			}else{
				cc = rgbs[j];
			}
			setColor(((j + 1) * (-1)), cc);
		}
		syncLED(wait);
	}
	delay(afterwait);
}

//dgbaseTemp::~dgbaseTemp() {
//}
