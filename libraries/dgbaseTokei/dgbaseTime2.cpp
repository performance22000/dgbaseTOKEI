/**
 * digibase library for Arduino: TOKEI: time h m s
 *
 * Create: 14/7/25 v0.1
 * Author: a.ide
 *
 * Mar 07 2014: Added Arduino and C++ Library
 * License: GNU GPL v2 (see License.txt)
 *
 * (c)2014 digi-base
 */
#include "dgbaseTime2.h"

dgbaseTime2::dgbaseTime2(uint8_t pin, uint8_t cnt, WS2812* led, cRGB chh, cRGB cmm, cRGB css)
	: dgbaseTime(pin, cnt, led, chh, cmm, css)
{
}


//時分秒のLEDをグラデーション変化させる準備
void dgbaseTime2::execute(int h, int m, int s, int wait) {
	mIsHour = (mHour != h);
	mIsMinute = (mMinute != m);

	//時間を保持
	mHour = h;
	mMinute = m;
	mSecond = s;
	
	//全クリア
	setColorBlackAll();
	
	//LED色を設定
	if (!mIsHour) {
		setColor2((h * TIME_HHCNT), mLedsHour, TIME_HHCNT, mLedsBeforeHour);
	}
	if (!mIsMinute) {
		setColor2(m, mLedsMinute, TIME_MMCNT, mLedsBeforeMinute);
	}
	setColor2(s, mLedsSecond, TIME_SSCNT, mLedsBeforeSecond);

//	syncLED();	//メイン処理で実行するのでここでは実行しない
	mCount = 0;
}

//LED色の設定(帯部分をグラデーション変化させる)
void dgbaseTime2::execGradation() {
	//LEDの帯部分を徐々に暗くする
	if (mIsHour) {
		//時(LED表示をズラすアニメーション)
		int8_t h = (mCount / 16) + 1;				//1～5
		int8_t p = ((mHour - 1) * TIME_HHCNT) + h;	//1時間前のLED位置からオフセット
		setColor3(p, mLedsHour, TIME_HHCNT, mLedsBeforeHour, mCount, mCount * (-1));
	}
	if (mIsMinute) {
		//分
		setColor3(mMinute, mLedsMinute, TIME_MMCNT, mLedsBeforeMinute, mCount, mCount * (-1));
	}
	//秒
	setColor3(mSecond, mLedsSecond, TIME_SSCNT, mLedsBeforeSecond, mCount, mCount * (-1));
	mCount++;
}


//LED色の設定処理(時分秒)
void dgbaseTime2::setColor3(int8_t tm, cRGB* leds, int8_t ledcnt, cRGB* beforeleds, int ccoffset1, int ccoffset2) {
	int8_t offset = ledcnt / 2;
	tm += offset;
	cRGB cc;
	for (int8_t i = 0; i < (ledcnt + 1); i++) {
		if (i == 0) {
			cc = changeColor(mColorbk, ccoffset1, leds[i], leds[i]);
		}else if (i <= offset) {
			cc = changeColor(leds[i - 1], ccoffset1, leds[i], leds[i]);
		}else{
			cc = changeColor(leds[i - 1], ccoffset2, leds[i], leds[i]);
		}
		cc = margeColor(cc, beforeleds[i]);
		setColor((tm - i), cc);
	}

}


//dgbaseTime2::~dgbaseTime2() {
//}
