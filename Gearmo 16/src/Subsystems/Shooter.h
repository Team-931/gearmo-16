#ifndef Shooter_H
#define Shooter_H

#include <WPILib.h>
#include "CANTalon.h"
#include "PIDRateCounter.h"

class Shooter : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	CANTalon launcher;
	CANTalon bubbler;
	PIDRateCounter launchSpd;
	float targetSpd;
	float bubbleSpd;
	float nomSpd;
	PIDController houston;
public:
	Shooter();
	void InitDefaultCommand();
	void SetSpd(float spd);
	void AddSpd(float diff);
	void RunShoot();
	float GetSpd();
	void ReadLaunchSpd();
	void ReloadParams();
};

#endif  // Shooter_H
