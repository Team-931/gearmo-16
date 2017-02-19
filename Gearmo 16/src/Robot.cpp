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

class Robot: public IterativeRobot {
private:
	//AnalogInput ultra;

	Command *autonomousCommand;
	SendableChooser<Command*> autoChooser;
	LiveWindow *lw;
	void RobotInit() {
		std::thread visionThread(VisionThread);
		visionThread.detach();

		CommandBase::init(this);
		autonomousCommand = 0; //TODO: real autonomous
		//autoChooser.AddObject("totefield", new autoner(2.65)/*new Auto1*/);
		//autoChooser.AddObject("toteramp", new autoner(3)/*new Auto2*/);
		//autoChooser.AddObject("totebinfield", new autonerbot(2.85)/*new Auto3*/);
		//autoChooser.AddObject("totebinramp", new autonerbot(3.25)/*new Auto4*/);
		//autoChooser.AddDefault("nothing",0);
		//SmartDashboard::PutData("Which autonomous?", &autoChooser);
		SmartDashboard::PutNumber("launch speed", 55);
		SmartDashboard::PutNumber("minimum launcher speed", 10);
		SmartDashboard::PutNumber("bubbler speed", .35);
		CommandBase::shooter->WritePID();
		lw = LiveWindow::GetInstance();
	}

	void DisabledInit() override
			{CommandBase::shooter->SetSpd(0);}
	void DisabledPeriodic() override {
		Scheduler::GetInstance()->Run();
	}

	void AutonomousInit() {
		autonomousCommand = static_cast<Command*>(autoChooser.GetSelected());
		if (!autonomousCommand) autonomousCommand = new PickUp(true);
		if (autonomousCommand != NULL)
			autonomousCommand->Start();
		CommandBase::shooter->ReloadParams();
	}

	void AutonomousPeriodic() {
		Scheduler::GetInstance()->Run();
		CommandBase::shooter->RunShoot();
	}

	void TeleopInit() {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (autonomousCommand != NULL)
			autonomousCommand->Cancel();
		CommandBase::shooter->ReloadParams();
	}

	void TeleopPeriodic() {
		Scheduler::GetInstance()->Run();
		CommandBase::shooter->RunShoot();

		if(CommandBase::oi->OperatorStick().GetRawButton(9)) CommandBase::shooter->ReadPID();

		bool latched = CommandBase::oi->OperatorStick().GetRawButton(6);
		if (latched)
			CommandBase::shooter->SetSpd(
					80 * CommandBase::oi->OperatorStick().GetRawAxis(1));
		else if (CommandBase::oi->OperatorStick().GetRawButton(8))
			CommandBase::shooter->ReadLaunchSpd();
		else
			CommandBase::shooter->AddSpd(
					2 * (CommandBase::oi->OperatorStick().GetRawButton(5)
						- CommandBase::oi->OperatorStick().GetRawButton(7)));

		new POV();

		SmartDashboard::PutNumber("launchspd", CommandBase::shooter->GetSpd());
	}

	void TestPeriodic() {
		lw->Run();
	}
public:
};

START_ROBOT_CLASS(Robot);

