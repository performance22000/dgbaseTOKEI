/**
 * digibase library for Arduino: TOKEI alarm pattern: sample
 *
 * Create: 14/6/24
 * Author: a.ide
 *
 * Mar 07 2014: Added Arduino and C++ Library
 * License: GNU GPL v2 (see License.txt)
 *
 * (c)2014 digi-base
 */

#include "dgbaseAlarm00.h"

dgbaseAlarm00::dgbaseAlarm00(uint8_t ledcnt, WS2812* LED, cRGB chh, cRGB cmm, cRGB css)
	: dgbaseTOKEI(ledcnt, LED, chh, cmm, css)
{
  //alarm executeion
  cRGB colors[3];
  colors[0] = chh;
  colors[1] = cmm;
  colors[2] = css;
  for (int8_t i = 0; i < 3; i++) {
    for (int8_t j = 0; j < ledcnt; j++) {
/*
      LED->set_crgb_at(j, colors[i]);
      LED->sync();
      delay(20);
      LED->set_crgb_at(j, colorbk);
      LED->sync();
      delay(20);
 */
		setColor(j, colors[i]);
		syncLED(20);
		setColorBlack(j);
		syncLED(20);

    }
  }

}

//dgbaseAlarm00::~dgbaseAlarm00() {
//}
