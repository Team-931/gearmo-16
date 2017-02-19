#include "RunShooter.h"

RunShooter::RunShooter() : CommandBase("Ball launcher"), spdRange(0)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(shooter);
}

// Called just before this Command runs the first time
void RunShooter::Initialize() {
}

float spdRanges[] = {43, 50, 60, 70, 80}; //XXX: what really?

// Called repeatedly when this Command is scheduled to run
void RunShooter::Execute() {
	shooter->RunShoot();
	  Joystick & joy = oi->OperatorStick();
	  if (robot->IsOperatorControl()) {{
		  bool onePushed = false, twoPushed = false;
		  int found = 0;
		  for(int btn = 1; btn <= 4; ++btn)
			  if(joy.GetRawButton(btn))
				  if(onePushed) {twoPushed = true; break;}
				  else {onePushed = true;
				  	  found = btn;}
		  if(onePushed && ! twoPushed) spdRange = found;}
	    float spd = spdRange ?
	    		(spdRanges[spdRange] + spdRanges[spdRange - 1])/2
	  			 	 + (spdRanges[spdRange] - spdRanges[spdRange - 1])/2 *
					 joy.GetRawAxis(1) : 0;
	    shooter->SetSpd(spd);//XXX: should there be a lag time?
	  }

}

// Make this return true when this Command no longer needs to run execute()
bool RunShooter::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void RunShooter::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunShooter::Interrupted() {

}
