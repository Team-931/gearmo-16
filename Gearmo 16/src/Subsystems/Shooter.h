#ifndef Shooter_H
#define Shooter_H

#include <WPILib.h>
#include "CANTalon.h"
#include "PIDRateCounter.h"

class Shooter : public Subsystem {
	CANTalon launcher;
	CANTalon bubbler;
	PIDRateCounter launchSpd;
	float bubbleSpd;
	float nomSpd;
	PIDController houston;
public:
	Shooter();
	void InitDefaultCommand();
	//target speed for the launcher wheel, in rotations per second
	void SetSpd(float spd);
	//as above but an increment
	void AddSpd(float diff);
	//Maintenance routine called per tick
	void RunShoot();
	//returns sensed speed, not target speed
	float GetSpd();
	//gets a target speed off the dashboard
	void ReadLaunchSpd();
	//dashboard also
	void WritePID();
	void ReadPID();
	//other info from dashboard
	void ReloadParams();
};

#endif  // Shooter_H
