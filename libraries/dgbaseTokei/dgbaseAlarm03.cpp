/**
 * digibase library for Arduino: TOKEI alarm pattern3 : 流れ星 左右＋帯
 *
 * Create: 14/6/24
 * Author: a.ide
 *
 * Mar 07 2014: Added Arduino and C++ Library
 * License: GNU GPL v2 (see License.txt)
 *
 * (c)2014 digi-base
 */

#include "dgbaseAlarm03.h"

#define OBILEN 3
#define WAIT 25
#define EXECCNT 3

dgbaseAlarm03::dgbaseAlarm03(uint8_t ledcnt, WS2812* LED, cRGB chh, cRGB cmm, cRGB css)
	: dgbaseTOKEI(ledcnt, LED, chh, cmm, css)
{
	cRGB colors[OBILEN + 1];
	colors[0] = mColorbk;	//dgbaseTOKEI
	colors[1] = cmm;
	colors[2] = margeColor(cmm, chh);
	colors[3] = chh;

	//LED
	for (int8_t cnt = 0; cnt < EXECCNT; cnt++) {
		//左右
		int8_t obicnt = OBILEN;
		for (int8_t i = 0; i < mLedCount; i++) {
			//左へ
			setColor(i, css);

			//帯
			int8_t j = i;
			for (obicnt = OBILEN; ((obicnt >= 0) && ((j--) > 0)); obicnt--) {
				setColor(j, colors[obicnt]);
			}
			if ((obicnt < 0) && (j >= 0)) {
				setColorBlack(j);
			}

			//右へ
			setColor((int8_t)(mLedCount - i - 1), css);
			//帯
			j = ledcnt - i - 1;
			for (obicnt = OBILEN; ((obicnt >= 0) && ((++j) < mLedCount)); obicnt--) {
				setColor(j, colors[obicnt]);
			}
			if ((obicnt < 0) && (j < mLedCount)) {
				setColorBlack(j);
			}

			syncLED(WAIT);

		}

		//徐々に消す
		for (obicnt = OBILEN; obicnt >= 0; obicnt--) {
			//左へ、帯
			int8_t c = obicnt;
			int8_t j = mLedCount - 1;
			for (; j >= (mLedCount - obicnt); j--) {
				setColor(j, colors[(c--)]);
			}
			setColorBlack(j);

			//右へ、帯
			j = 0;
			for (; j < obicnt; j++) {
				setColor(j, colors[(obicnt - 1)]);
			}
			setColorBlack(j);

			syncLED(WAIT);
		}
	}
}

//dgbaseAlarm03::~dgbaseAlarm03() {
//}
