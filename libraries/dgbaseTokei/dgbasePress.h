/**
 * digibase library for Arduino: TOKEI press 気圧
 *
 * Create: 14/7/20
 * Author: a.ide
 *
 * Mar 07 2014: Added Arduino and C++ Library
 * License: GNU GPL v2 (see License.txt)
 *
 * (c)2014 digi-base
 */
#ifndef DGBASE_PRESS_H_
#define DGBASE_PRESS_H_

#include "dgbaseTOKEI.h"

class dgbasePress : public dgbaseTOKEI {
public:
	dgbasePress(uint8_t ledcnt, WS2812* LED, cRGB chh, cRGB cmm, cRGB css);
//	~dgbasePress();

	void execute(float hpa, int wait, int afterwait);
	void execute(float hpa, int wait, int afterwait, boolean isold);	//backup

	float mHpa;

private:

};

#endif /* DGBASE_PRESS_H_ */
