#include "Facer.h"

Facer::Facer(float facing):face(facing/360) {
	// Use Requires() here to declare subsystem dependencies
	Requires(swerveDrive);
}

// Called just before this Command runs the first time
void Facer::Initialize() {
swerveDrive->SetPerson(face,false);
}

// Called repeatedly when this Command is scheduled to run
void Facer::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool Facer::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void Facer::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Facer::Interrupted() {

}
