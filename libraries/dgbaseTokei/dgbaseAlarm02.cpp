/**
 * digibase library for Arduino: TOKEI alarm pattern2
 *
 * Create: 14/6/24
 * Author: a.ide
 *
 * Mar 07 2014: Added Arduino and C++ Library
 * License: GNU GPL v2 (see License.txt)
 *
 * (c)2014 digi-base
 */

#include "dgbaseAlarm02.h"

#define OBILEN 3
#define WAIT 25
#define EXECCNT 3

dgbaseAlarm02::dgbaseAlarm02(uint8_t ledcnt, WS2812* LED, cRGB chh, cRGB cmm, cRGB css)
	: dgbaseTOKEI(ledcnt, LED, chh, cmm, css)
{
	cRGB colors[OBILEN + 1];
	colors[0] = mColorbk;	//dgbaseTOKEI
	colors[1] = cmm;
	colors[2] = margeColor(cmm, chh);
	colors[3] = chh;

	//LED
	for (int8_t cnt = 0; cnt < EXECCNT; cnt++) {
		int8_t obicnt = 0;
		for (int8_t i = (mLedCount - 1); i >= 0; i--) {
			setColor(i, css);

			int8_t j = i;
			for (obicnt = OBILEN; ((obicnt >= 0) && ((++j) < mLedCount)); obicnt--) {
				setColor(j, colors[obicnt]);
			}
			if ((obicnt < 0) && (j < mLedCount)) {
				setColorBlack(j);
			}
			syncLED(WAIT);
		}
		//
		for (obicnt = OBILEN; obicnt >= 0; obicnt--) {
			int8_t j = 0;
			for (; j < obicnt; j++) {
				setColor(j, colors[(obicnt - j)]);
			}
			setColorBlack(j);
			syncLED(WAIT);
		}
	}
}

//dgbaseAlarm02::~dgbaseAlarm02() {
//}
