#include "ThirdPerson.h"

ThirdPerson::ThirdPerson(bool isIt) : CommandBase("Turn to third person: "), onOff(isIt) {
	// Use Requires() here to declare subsystem dependencies
	Requires(swerveDrive);
	SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void ThirdPerson::Initialize() {
	swerveDrive->SetPerson(0, onOff);
}

// Called repeatedly when this Command is scheduled to run
void ThirdPerson::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ThirdPerson::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ThirdPerson::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ThirdPerson::Interrupted() {

}
