#include "GearForward.h"

GearForward::GearForward() : CommandBase("Gear forward"){
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(swerveDrive);
}

// Called just before this Command runs the first time
void GearForward::Initialize() {
	swerveDrive->SetPerson(SwerveDrive::GearForward, false);
}

// Make this return true when this Command no longer needs to run execute()
bool GearForward::IsFinished() {
	return true;
}
