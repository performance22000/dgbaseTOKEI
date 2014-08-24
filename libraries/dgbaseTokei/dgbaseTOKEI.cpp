/*
 * digibase libraries for Arduino: TOKEI
 *
 * Create: 14/06/21
 * Author: a.ide
 *
 * Mar 07 2014: Added Arduino and C++ Library
 * License: GNU GPL v2 (see License.txt)
 *
 * (c)2014 digi-base
 */

#include "dgbaseTOKEI.h"

/** constructor */
dgbaseTOKEI::dgbaseTOKEI(uint8_t pin, uint8_t cnt, WS2812* led) {
	mLedCount = cnt;
	mLED = led;
	mLED->setOutput(pin);

	cRGB cbk = { 0, 0, 0 };
	mColorbk = cbk;
}

/**
 * constructor for Alarm
 */
dgbaseTOKEI::dgbaseTOKEI(uint8_t cnt, WS2812* led, cRGB chh, cRGB cmm, cRGB css) {
	mLedCount = cnt;
	mLED = led;

	cRGB cbk = { 0, 0, 0 };
	mColorbk = cbk;

	mColorhh = chh;
	mColormm = cmm;
	mColorss = css;
}

/** destrustor */
dgbaseTOKEI::~dgbaseTOKEI() {
}

/** LED all clear */
void dgbaseTOKEI::clearLED() {
	for (uint8_t i = 0; i < mLedCount; i++) {
		setColorBlack(i);
	}
	syncLED();
}


/** LED get color */
cRGB dgbaseTOKEI::getColor(int8_t pos) {
	return mLED->get_crgb_at(getLedPosition(pos));
}


/** LED set all black */
void dgbaseTOKEI::setColorBlackAll() {
	for (uint8_t i = 0; i < mLedCount; i++) {
		setColorBlack(i);
	}
}

/** LED position */
void dgbaseTOKEI::setColor(int8_t pos, cRGB color) {
	if (isEqualRGB(color)) {	//R,G,B が同じ値の場合、LED発光が変なのでちょっとズラす。
		color.b++;
	}
	mLED->set_crgb_at(getLedPosition(pos), color);
}

void dgbaseTOKEI::setColorBlack(int8_t pos) {
	mLED->set_crgb_at(getLedPosition(pos), mColorbk);
}


/** LED sync and delay */
void dgbaseTOKEI::syncLED(int wait) {
	mLED->sync();
	delay(wait);
}

void dgbaseTOKEI::syncLED() {
	mLED->sync();
}


/** 徐々に消す */
void dgbaseTOKEI::fader(int wait) {
	int8_t cnt = 0;
	while((cnt++) < mLedCount) {
		for (int8_t i = 0; i < mLedCount; i++) {
			cRGB cc = getColor(i);
			cc = changeColor(cc, -1, mColorbk, mColorss);
			setColor(i, cc);
		}
		syncLED(wait);
	}
}

