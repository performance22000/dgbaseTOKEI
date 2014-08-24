/**
 * digibase library for Arduino: TOKEI: time h m s & alarm
 *
 * Create: 14/7/13
 * Author: a.ide
 *
 * Mar 07 2014: Added Arduino and C++ Library
 * License: GNU GPL v2 (see License.txt)
 *
 * (c)2014 digi-base
 */
#include "dgbaseTime.h"
#include <dgbaseAlarm01.h>
#include <dgbaseAlarm02.h>
#include <dgbaseAlarm03.h>

dgbaseTime::dgbaseTime(uint8_t pin, uint8_t cnt, WS2812* led, cRGB chh, cRGB cmm, cRGB css)
	: dgbaseTOKEI(pin, cnt, led)
{
	mColorhh = chh;
	mColormm = cmm;
	mColorss = css;

	clearLED();	//消灯

	//点灯チェック
	for (int8_t i = 0; i < mLedCount; i++) {
		setColor(i, mColorss);
		syncLED(10);
		setColorBlack(i);
	}
	syncLED(10);

	//LED色の設定(デフォルト値)
	setColor2(mLedsHour, mColorhh, TIME_HHCNT);
	setColor2(mLedsMinute, mColormm, TIME_MMCNT);
	setColor2(mLedsSecond, mColorss, TIME_SSCNT);

	mHour = 0;
	mMinute = 0;
	mSecond = 0;
	mCount = 0;
	mAlarmCnt = 0;
}

//時間のLED表示
void dgbaseTime::execute(int h, int m, int s, int wait) {
	//時間を保持
	mHour = h;
	mMinute = m;
	mSecond = s;
	
	//全クリア
	setColorBlackAll();
	
	//LED色を設定
	setColor2((h * TIME_HHCNT), mLedsHour, TIME_HHCNT, mLedsBeforeHour);
	setColor2(m, mLedsMinute, TIME_MMCNT, mLedsBeforeMinute);
	setColor2(s, mLedsSecond, TIME_SSCNT, mLedsBeforeSecond);

	//LEDの表示
	syncLED(wait);
	mCount = 0;
}


//初期処理(LED色の設定)
void dgbaseTime::setColor2(cRGB* leds, cRGB color, int8_t ledcnt) {
	int8_t center = ledcnt / 2;
	for (int8_t i = 0; i < ledcnt; i++) {
		cRGB cc = color;
		if (i != center) {
			//周囲はちょっと暗く
			cc.r /= TIME_RGB2;
			cc.g /= TIME_RGB2;
			cc.b /= TIME_RGB2;
		}
		leds[i] = cc;
	}
	leds[ledcnt] = mColorbk;	//帯部分のLED色
}

//LED色の設定処理
void dgbaseTime::setColor2(int8_t tm, cRGB* leds, int8_t ledcnt, cRGB* beforeleds) {
	tm += ledcnt / 2;
	for (int8_t i = 0; i < ledcnt; i++) {
		//LED設定前の色を保持
		beforeleds[i] = getColor((int8_t)tm - i);
		//LED設定する色(既に設定済の色とマージする)
		cRGB cc = margeColor(beforeleds[i], leds[i]);
		setColor((int8_t)(tm - i), cc);
	}
	//帯部分のLED色を保持
	beforeleds[ledcnt] = getColor(tm - ledcnt);
}


//アラームの表示(LED表示)
boolean dgbaseTime::isAlarm(int h, int m, int s) {
	//1時間に1回
//	if (m == 0) {
//		executeAlarm();
//		return true;
//	}
	//1分に1回
	if (s == 0) {
		executeAlarm();
		return true;
	}
	//20秒に1回
//	if (s%20 == 0) {
//		executeAlarm();
//		return true;
//	}
	return false;
}

void dgbaseTime::executeAlarm() {
	if (mAlarmCnt == 0) {
		dgbaseAlarm01 alarm(mLedCount, mLED, mColorhh, mColormm, mColorss);
	}else if (mAlarmCnt == 1) {
		dgbaseAlarm02 alarm(mLedCount, mLED, mColorhh, mColormm, mColorss);
	}else if (mAlarmCnt == 2) {
		dgbaseAlarm03 alarm(mLedCount, mLED, mColorhh, mColormm, mColorss);
	}
	if ((++mAlarmCnt) >= 3) {
		mAlarmCnt = 0;
	}
}

//dgbaseTime::~dgbaseTime() {
//}
