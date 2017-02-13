/*
 * PIDRateCounter.h
 *
 *  Created on: Feb 12, 2017
 *      Author: Developer
 */
#include "WPILib.h"
#ifndef SRC_PIDRATECOUNTER_H_
#define SRC_PIDRATECOUNTER_H_

class PIDRateCounter:public PIDSource,public Counter {
public:
	PIDRateCounter(int dio):Counter(dio){
		/*SetPIDSourceType(PIDSourceType::kRate);*/
	}
double PIDGet() override {
	return 1/GetPeriod();
}

};



#endif /* SRC_PIDRATECOUNTER_H_ */
