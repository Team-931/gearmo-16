#include "RopeClimb.h"

RopeClimb::RopeClimb(bool running):
	CommandBase(running?"Climbing":"Not climbing"),
	onOff(running) {
	// Use Requires() here to declare subsystem dependencies
	Requires(winch);
}

// Called just before this Command runs the first time
void RopeClimb::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void RopeClimb::Execute() {
	winch->Climb(onOff);
}

// Make this return true when this Command no longer needs to run execute()
bool RopeClimb::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void RopeClimb::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RopeClimb::Interrupted() {
}
