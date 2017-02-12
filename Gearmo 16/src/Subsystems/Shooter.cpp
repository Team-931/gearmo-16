#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("ExampleSubsystem"),
	launcher(9),
	bubbler(10),
	launchSpd(0),
	bubbleSpd(0),
	targetSpd(0),
	houston(3,0,1,&launchSpd,&launcher),
	nomSpd(10)
{
houston.SetAbsoluteTolerance(1);
}

void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::SetSpd(float spd) {
	houston.SetSetpoint(spd);
}

void Shooter::AddSpd(float diff) {
	SetSpd(houston.GetSetpoint() + diff); //because targetSpd is negative
}
void Shooter::RunShoot() {
	bool bubblerOn = (houston.GetSetpoint()>=nomSpd&&houston.OnTarget());
	bubbler.Set(bubblerOn*bubbleSpd);
}

float Shooter::GetSpd() {
	return 1 / launchSpd.GetPeriod();
}

void Shooter::ReadLaunchSpd() {
	SetSpd(SmartDashboard::GetNumber("launch speed", 55));
}

void Shooter::ReloadParams() {
	nomSpd = SmartDashboard::GetNumber("minimum launcher speed", 10);
	bubbleSpd = - SmartDashboard::GetNumber("bubbler speed", .35);
}
