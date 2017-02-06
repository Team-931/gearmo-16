#include "Straightenup.h"

Straightenup::Straightenup()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
    Requires(swerveDrive);
    SetInterruptible(true);
}

// Called just before this Command runs the first time
void Straightenup::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void Straightenup::Execute()
{
  swerveDrive->Drive(0,1,0,true);
}

// Make this return true when this Command no longer needs to run execute()
bool Straightenup::IsFinished()
{
	return swerveDrive->OnTarget();
}

// Called once after isFinished returns true
void Straightenup::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Straightenup::Interrupted()
{

}
# if ! newdrivestick
SpeedToggle::SpeedToggle()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
    Requires(swerveDrive);
    SetInterruptible(true);
}

// Called just before this Command runs the first time
void SpeedToggle::Initialize()
{
   swerveDrive->Toggler();
}

// Called repeatedly when this Command is scheduled to run
void SpeedToggle::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool SpeedToggle::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void SpeedToggle::End()
{
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpeedToggle::Interrupted()
{
}
# endif
