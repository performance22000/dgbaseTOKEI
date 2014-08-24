/**
 * digibase library for Arduino: TOKEI alarm pattern1
 *
 * Create: 14/6/24
 * Author: a.ide
 *
 * Mar 07 2014: Added Arduino and C++ Library
 * License: GNU GPL v2 (see License.txt)
 *
 * (c)2014 digi-base
 */

#include "dgbaseAlarm01.h"

#define OBILEN 3
#define WAIT 25
#define EXECCNT 3

dgbaseAlarm01::dgbaseAlarm01(uint8_t ledcnt, WS2812* LED, cRGB chh, cRGB cmm, cRGB css)
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
		for (int8_t i = 0; i < mLedCount; i++) {
			setColor(i, css);

			int8_t j = i;
			for (obicnt = OBILEN; ((obicnt >= 0) && ((j--) > 0)); obicnt--) {
				setColor(j, colors[obicnt]);
			}
			if ((obicnt < 0) && (j >= 0)) {
				setColorBlack(j);
			}
			syncLED(WAIT);
		}
		//
		for (obicnt = OBILEN; obicnt >= 0; obicnt--) {
			int8_t c = obicnt;
			int8_t j = mLedCount - 1;
			for (; j >= (mLedCount - obicnt); j--) {
				setColor(j, colors[(c--)]);
			}
			setColorBlack(j);
			syncLED(WAIT);
		}
	}
}

//dgbaseAlarm01::~dgbaseAlarm01() {
//}
