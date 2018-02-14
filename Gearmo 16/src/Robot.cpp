#include "WPILib.h"
#include "Commands/TeleopDrive.h"
#include "Commands/PickUp.h"
# define PIH 1
# if PIH
#include "Commands/autoPIH.h"
typedef autoPIH autoner;
# else
#include "Commands/autoner.h"
# endif
#include "CommandBase.h"
//#include "Subsystems/Winch.h"
#include "Commands/POV.h"

void VisionThread();

namespace LaunchGeom
{double goalHt = 8+1.0/12, //8 ft., 1 in.
 shooterHt = 1,
 exitAngle = 74,
 exitSlope,
 wheelDiam = 1.0/3;
 double g = 32,
 gslop = g/2*(exitSlope*exitSlope + 1),
 rpscvrt = 2/wheelDiam/M_PI;

 void ReadIn() {}
 void inline SetSlope() {exitSlope = tan(exitAngle);}
 double inline rps(double distance)
 {return rpscvrt * distance * sqrt(gslop / (distance * exitSlope - goalHt));}
}

typedef SendableChooser<Command*> AutoChooser;
void SetAutoChoices(AutoChooser&);

class Robot: public IterativeRobot {
private:
	//AnalogInput ultra;

	Command *autonomousCommand;
	AutoChooser autoChooser;
	LiveWindow *lw;
	void RobotInit() {
		std::thread visionThread(VisionThread);
		visionThread.detach();

		SmartDashboard::PutString("working", "Working");
		CommandBase::init(this);
		autonomousCommand = 0; //TODO: real autonomous
		SetAutoChoices(autoChooser);
/*
		SmartDashboard::PutNumber("launch speed", 55);
		SmartDashboard::PutNumber("minimum launcher speed", 10);
		SmartDashboard::PutNumber("bubbler speed", .35);
		CommandBase::shooter->WritePID();
*/
		lw = LiveWindow::GetInstance();
	}

	void DisabledInit() override
			{/*CommandBase::shooter->SetSpd(0);*/}
	void DisabledPeriodic() override {
		Scheduler::GetInstance()->Run();
	}

	void AutonomousInit() {
		autonomousCommand = /*dynamic_cast<Command*>*/(autoChooser.GetSelected());
		//if (!autonomousCommand) autonomousCommand = new PickUp(true);
		if (autonomousCommand != NULL)
			autonomousCommand->Start();
		CommandBase::shooter->ReloadParams();
	}

	void AutonomousPeriodic() {
		Scheduler::GetInstance()->Run();
//		CommandBase::shooter->RunShoot();
	}

	void TeleopInit() {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (autonomousCommand != NULL)
			autonomousCommand->Cancel();
		(new POV())->Start();
		CommandBase::shooter->ReloadParams();
	}

	void TeleopPeriodic() {
		Scheduler::GetInstance()->Run();
		if(CommandBase::oi->OperatorStick().GetRawButton(9)) CommandBase::shooter->ReadPID();
	}

	void TestPeriodic() {
		lw->Run();
	}
public:
};

START_ROBOT_CLASS(Robot);

