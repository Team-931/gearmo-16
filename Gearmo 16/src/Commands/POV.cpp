#include "POV.h"
#include "Facer.h"

POV::POV() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void POV::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void POV::Execute() {
	Joystick  &joy = oi->DriveStick();
	if(joy.GetPOV(0)>=0) {
		if(joy.GetPOV(0)%90==0) {
			float faced = (joy.GetPOV(0));
			(new Facer(faced))->Start();
		};
	};
}

// Make this return true when this Command no longer needs to run execute()
bool POV::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void POV::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void POV::Interrupted() {

}
