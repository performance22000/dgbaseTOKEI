/**
 * digibase library for Arduino: TOKEI press 気圧の表示
 *
 * Create: 14/7/20
 * Author: a.ide
 *
 * Mar 07 2014: Added Arduino and C++ Library
 * License: GNU GPL v2 (see License.txt)
 *
 * (c)2014 digi-base
 */
#include "dgbasePress.h"

dgbasePress::dgbasePress(uint8_t ledcnt, WS2812* LED, cRGB chh, cRGB cmm, cRGB css)
	: dgbaseTOKEI(ledcnt, LED, chh, cmm, css)
{
	clearLED();	//消灯
}

//LED
void dgbasePress::execute(float hpa, int wait, int afterwait) {
	mHpa = hpa;

	if (hpa < 1000) {
		hpa = (((hpa - 984) / 2) - 0.9);	/** 0-6へ換算 29-23 */

	}else if (hpa < 1013) {
		hpa = ((hpa - 984 - 2) / 2);	/** 7-13へ換算 22-16 */

	}else if (hpa >= 1014.0) {
		hpa = ((hpa - 984) / 2);		/** 15-20へ換算 14-9 */

	}else if (hpa >= 1025.0) {
		hpa = (((hpa - 984) / 2) + 0.5);	/** 21-29へ換算 8-0 */

	}else{
		hpa = 14;	/** 1013hPa */
	}
	hpa = 29 - (int8_t)hpa;
	mHpa = hpa;

	//color
	cRGB c1 = {  0, 30,  0 };	//赤
	cRGB c2 = { 30, 30,  0 };	//黄
	cRGB c3 = { 30, 30, 30 };	//白
	cRGB c4 = { 30,  0, 30 };	//シアン
	cRGB c5 = {  0,  0, 30 };	//紺

	//backup
	cRGB rgbs[mLedCount], tmps[mLedCount], cc1, cc2;
	int8_t p1 = 29;
	for (; p1 >= 0; p1--) {
		int8_t p2 = mLedCount - 1 - p1;
		rgbs[p1] = getColor(p1);
		rgbs[p2] = getColor(p2);
		if (p1 > hpa) {
			if (p1 >= 23) {
				tmps[p1] = c5;
				tmps[p2] = c5;
			}else if (p1 >= 16) {
				tmps[p1] = c4;
				tmps[p2] = c4;
			}else if (p1 == 15) {
				tmps[p1] = c3;
				tmps[p2] = c3;
			}else if (p1 >= 9) {
				tmps[p1] = c2;
				tmps[p2] = c2;
			}else{
				tmps[p1] = c1;
				tmps[p2] = c1;
			}
		}else{
			tmps[p1] = mColorbk;
			tmps[p2] = mColorbk;
		}
	}
	//LED
	p1 = 29;
	for (; p1 >= 0; p1--) {
		int8_t p11 = 29;
		for (; p11 >= 0; p11--) {
			int8_t p21 = mLedCount - 1 - p11;
			cc1 = changeColor(rgbs[p11], -4, mColorbk, mColorss);
			cc2 = changeColor(rgbs[p21], -4, mColorbk, mColorss);
			if (p11 >= p1) {
				cc1 = margeColor(cc1, tmps[p11]);
				cc2 = margeColor(cc2, tmps[p21]);
			}
			setColor(p11, cc1);
			setColor(p21, cc2);
		}
		syncLED(wait);
	}
	
	delay(afterwait);
}


//LED
void dgbasePress::execute(float hpa, int wait, int afterwait, boolean isold) {
	mHpa = hpa;

	if (hpa < 1013) {
		hpa = ((hpa - 983) / 2) + 1;	/** 少数を四捨五入して、0-15へ換算 */
	}else if (hpa >= 1014.0) {
		hpa = ((hpa - 983) / 2) + 10.5;	/** 少数を切り上げて、17-29へ換算 */
	}else{
		hpa = 16;	/** 1013hPa */
	}

	//color
	cRGB c1 = {  0, 40,  0 };	//赤
	cRGB c2 = { 40, 40,  0 };	//黄
	cRGB c3 = { 40, 40, 40 };	//白
	cRGB c4 = { 40,  0, 40 };	//シアン
	cRGB c5 = {  0,  0, 40 };	//紺

	//LED
	uint8_t p1 = 30;
	uint8_t p2 = 30;
	for (int i = 0; i < hpa; i++) {
		if (i < 8) {
			setColor(p1, c5);
			setColor(p2, c5);

		}else if (i < 15) {
			setColor(p1, c4);
			setColor(p2, c4);

		}else if (i == 15) {
			setColor(p1, c3);
			setColor(p2, c3);

		}else if (i < 23) {
			setColor(p1, c2);
			setColor(p2, c2);

		}else if (i >= 23) {
			setColor(p1, c1);
			setColor(p2, c1);
		}
		syncLED(wait);
		p1--;
		p2++;
	}
	delay(afterwait);
}

//dgbasePress::~dgbasePress() {
//}
