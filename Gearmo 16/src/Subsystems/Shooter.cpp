#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("Fuel Shooter"),
	launcher(9),
	bubbler(10),
	launchSpd(0),
	bubbleSpd(0),
	nomSpd(10),
	houston(.125, 0, 0 ,&launchSpd,&launcher)
{
	houston.SetOutputRange(0, 1); //the sensor cannot tell forward from backward,
									//so we require output always forward.
	houston.Enable();
	houston.SetAbsoluteTolerance(1);
	houston.SetToleranceBuffer(8);
}

void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::SetSpd(float spd) {
	if(spd < 0) spd = 0;// the shooter may not reverse.
						//see note in the constructor.
	houston.SetSetpoint(spd);
}

void Shooter::AddSpd(float diff) {
	SetSpd(houston.GetSetpoint() + diff); //because targetSpd is negative
}
void Shooter::RunShoot() {
	static bool bubblerOn;
	bubblerOn = (/*houston.GetSetpoint() */ GetSpd() >= nomSpd) &&
			(bubblerOn || houston.OnTarget());
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

void Shooter::WritePID() {
	SmartDashboard::PutNumber("Shooter P",
			SmartDashboard::GetNumber("Shooter P", houston.GetP()));
	SmartDashboard::PutNumber("Shooter I",
			SmartDashboard::GetNumber("Shooter I", houston.GetI()));
	SmartDashboard::PutNumber("Shooter D",
			SmartDashboard::GetNumber("Shooter D", houston.GetD()));
	SmartDashboard::PutNumber("Shooter tolerance",
			SmartDashboard::GetNumber("Shooter tolerance", 1));
}

void Shooter::ReadPID() {
	houston.SetPID(	SmartDashboard::GetNumber("Shooter P", houston.GetP()),
					SmartDashboard::GetNumber("Shooter I", houston.GetI()),
					SmartDashboard::GetNumber("Shooter D", houston.GetD()));
	houston.SetAbsoluteTolerance(
			SmartDashboard::GetNumber("Shooter tolerance", 1));
}
