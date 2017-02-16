#include "ToggleThirdPerson.h"

ToggleThirdPerson::ToggleThirdPerson() :
	CommandBase("Toggle {First | Third} Person")
// Use Requires() here to declare subsystem dependencies
	{Requires(swerveDrive);
	 SetInterruptible(false);}

// Called just before this Command runs the first time
void ToggleThirdPerson::Initialize()
	{swerveDrive->SetPerson(0, !swerveDrive->IsThirdPerson());}

// Make this return true when this Command no longer needs to run execute()
bool ToggleThirdPerson::IsFinished()
	{return true;}
