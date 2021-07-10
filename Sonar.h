/*
 * Sonar.h
 *
 *  Created on: May 1, 2021
 *      Author: kacpe
 */

#ifndef SRC_SONAR_H_
#define SRC_SONAR_H_
#include "stdint.h"

class Sonar {
	public:
		 uint32_t start = 0;
		 uint32_t end = 0;
		 uint8_t state = 0;
		 uint32_t ticks = 0;
		 uint16_t TIM2_OVC = 0;
		 uint32_t distance = 0;
		Sonar();
	virtual ~Sonar();
};

#endif /* SRC_SONAR_H_ */
