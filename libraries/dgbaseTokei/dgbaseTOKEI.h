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
#ifndef DGBASE_TOKEI_H_
#define DGBASE_TOKEI_H_

#include "WS2812.h"

class dgbaseTOKEI {
public: 
	// for Time
	dgbaseTOKEI(uint8_t pin, uint8_t cnt, WS2812* led);
	// for Alarm
	dgbaseTOKEI(uint8_t, WS2812*, cRGB, cRGB, cRGB);
	~dgbaseTOKEI();

	/** fadeout */
	void fader(int wait);


//protected:
	/** LED position */
	void clearLED();

	/** led convert position */
	cRGB getColor(int8_t pos);
	
	void setColor(int8_t pos, cRGB color);
	void setColorBlack(int8_t pos);
	
	void setColorBlackAll();


	/** LED sync */
	void syncLED(int wait);
	void syncLED();

	/**
	 * utilities
	 */
	// convert from TIME to LED position
	uint8_t getLedPosition(int8_t tm) {
		if (tm < 0) {
			//LEDの並びが逆(-60:59,..., -4:3, -3:2, -2:1, -1:0)なのでマイナス値ほど左回り
			mLedPosition = ((tm + 1) * (-1)) % mLedCount;
//			return ((tm + 1) * (-1)) % mLedCount;
		}else{
			//LEDの並びが逆(0:59, 1:58, 2:57,...59:0)なので正の値ほど右回りにする
			mLedPosition = mLedCount - 1 - (tm % mLedCount);
//			return mLedCount - 1 - (tm % mLedCount);
		}
		return mLedPosition;
	}

	// marge A and B to color
	cRGB margeColor(cRGB cc1, cRGB cc2) const {
		cRGB cc;
		cc.r = cc1.r | cc2.r;
		cc.g = cc1.g | cc2.g;
		cc.b = cc1.b | cc2.b;
		return cc;
	}

	// condition A and B
	boolean isEqualColor(cRGB cc1, cRGB cc2) const {
		if (cc1.r != cc2.r) return false;
		if (cc1.g != cc2.g) return false;
		if (cc1.b != cc2.b) return false;
		return true;
	}

	// change Color
	cRGB changeColor(cRGB cc, int offset, cRGB cmin, cRGB cmax) {
		cc.r = getColorMinMax(cc.r, offset, cmin.r, cmax.r);
		cc.g = getColorMinMax(cc.g, offset, cmin.g, cmax.g);
		cc.b = getColorMinMax(cc.b, offset, cmin.b, cmax.b);
		return cc;
	}


	/** members */
	WS2812*	mLED;
	uint8_t	mLedCount;
	cRGB	mColorbk;
	cRGB	mColorhh;
	cRGB	mColormm;
	cRGB	mColorss;

	uint8_t mLedPosition;

private:
	// condition r and g and b
	boolean isEqualRGB(cRGB cc) const {
		return ((!isEqualColor(mColorbk, cc)) && (cc.r == cc.g) && (cc.r == cc.b));
	}

	// get Color Min or Max
	uint8_t getColorMinMax(uint8_t cc, int offset, uint8_t cmin, uint8_t cmax) {
		int c = cc + offset;
//		if (c < 0) return 0;
		if ((offset < 0)&&(c < cmin)) return cmin;
		if ((offset > 0)&&(c >= cmax)) return cmax;
		return c;
	}

};


#endif /* DGBASE_TOKEI_H_ */
