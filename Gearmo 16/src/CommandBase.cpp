#include "CommandBase.h"
#include <Commands/Scheduler.h>

// Initialize a single static instance of all of your subsystems to NULL
RobotBase * CommandBase::robot = 0;
SwerveDrive* CommandBase::swerveDrive = NULL;
Shooter * CommandBase::shooter = 0;
//Elevator* CommandBase::elevator = NULL;
OI* CommandBase::oi = NULL;
BPM *CommandBase::bpm = 0;
Winch *CommandBase::winch = 0;

CommandBase::CommandBase(char const *name) :
		Command(name)
{
}

CommandBase::CommandBase() :
		Command()
{

}

CommandBase::CommandBase(double timeout) :
  Command(timeout)
 {
 }

void CommandBase::init(RobotBase *robo)
{
	// Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	robot = robo;

	swerveDrive = new SwerveDrive();
	SmartDashboard::PutData(swerveDrive);
//	SmartDashboard::PutNumber("Drive P", .125);
//	SmartDashboard::PutNumber("Drive I", 0);
//	SmartDashboard::PutNumber("Drive D", 0);

	shooter = new Shooter();
	SmartDashboard::PutData(shooter);

	bpm = new BPM();
	SmartDashboard::PutData(bpm);

	winch = new Winch();
	SmartDashboard::PutData(winch);
	oi = new OI();//This must come after the SubSystems.
}
