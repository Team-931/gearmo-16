#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("ExampleSubsystem"),
	launcher(9),
	bubbler(10),
	launchSpd(0),
	bubbleSpd(0),
	houston(.03,0,0,&launchSpd,&launcher),
	nomSpd(10)
{
	houston.SetOutputRange(0, 1); //the sensor cannot tell forward from backward,
									//so we require output always forward.
	houston.SetAbsoluteTolerance(1);
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
	houston.Enable();
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
	SetSpd(SmartDashboard::GetNumber("launch speed", 15));
}

void Shooter::ReloadParams() {
	nomSpd = SmartDashboard::GetNumber("minimum launcher speed", 10);
	bubbleSpd = - SmartDashboard::GetNumber("bubbler speed", .35);
}

void Shooter::WritePID() {
	SmartDashboard::PutNumber("Shooter P", houston.GetP());
	SmartDashboard::PutNumber("Shooter I", houston.GetI());
	SmartDashboard::PutNumber("Shooter D", houston.GetD());
}

void Shooter::ReadPID() {
	houston.SetPID(	SmartDashboard::GetNumber("Shooter P", houston.GetP()),
					SmartDashboard::GetNumber("Shooter I", houston.GetI()),
					SmartDashboard::GetNumber("Shooter D", houston.GetD()));
}
