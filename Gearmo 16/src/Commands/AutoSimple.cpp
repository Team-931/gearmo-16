#include "AutoSimple.h"
#include "Subsystems/SwerveDrive.h"

AutoSimple::AutoSimple() {
	// Use Requires() here to declare subsystem dependencies
	Requires(swerveDrive);
}

// Called just before this Command runs the first time
void AutoSimple::Initialize() {
swerveDrive->Drive(.125, -.25, 0);
}

// Make this return true when this Command no longer needs to run execute()
bool AutoSimple::IsFinished() {
	return true;
}
