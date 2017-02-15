#include "PickUp.h"

PickUp::PickUp(bool onOff) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(bpm);
}

// Called just before this Command runs the first time
void PickUp::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void PickUp::Execute() {
	bpm->Run(onOff);
}

// Make this return true when this Command no longer needs to run execute()
bool PickUp::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void PickUp::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PickUp::Interrupted() {

}
