#ifndef BPM_H
#define BPM_H

#include "WPILib.h"
#include "CANTalon.h"
#include <Commands/Subsystem.h>
//Ball Pickup Mechanism
class BPM : public Subsystem {
private:
	CANTalon bpMotor;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

public:
	BPM();
	void InitDefaultCommand();
	void Run(bool runMotor);
};

#endif  // BPM_H
