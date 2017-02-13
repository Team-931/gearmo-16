#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/TeleopDrive.h"
# define PIH 1
# if PIH
#include "Commands/autoPIH.h"
typedef autoPIH autoner;
# else
#include "Commands/autoner.h"
# endif
#include "CommandBase.h"

// For the cameras
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>

namespace LaunchGeom
{double goalHt = 8+1.0/12, //8 ft., 1 in.
 shooterHt = 1,
 exitAngle = 74,
 exitSlope,
 wheelDiam = 1.0/3;

 void ReadIn() {}
 void inline SetSlope() {exitSlope = tan(exitAngle);}
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

	static void VisionThread() {
		// Get the USB camera from CameraServer  :  PIH -- this version captures the next uncaptured camera
		cs::UsbCamera camera =
				CameraServer::GetInstance()->StartAutomaticCapture();
		cs::UsbCamera camera1 =
				CameraServer::GetInstance()->StartAutomaticCapture();
		// Set the resolution
		camera.SetResolution(640, 480);
		camera1.SetResolution(640, 480);

		// Get a CvSink. This will capture Mats from the Camera : PIH -- only using this one
		cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo(camera);
		// Setup a CvSource. This will send images back to the Dashboard : PIH -- emulates a camera named "Rectangle"
		cs::CvSource outputStream = CameraServer::GetInstance()->PutVideo(
				"Rectangle", 640, 480);

		// Mats are very memory expensive. Lets reuse this Mat.
		cv::Mat mat, greymat;
		cv::Mat red2black(cv::Vec<float, 4> { .25, .25, -.5, 128 });//{1, 1, -2, 512};
		/*typedef std::vector<cv::Vec2f> ptVec;
		 ptVec corners;
		 std::vector<ptVec> cornersList;*/
		std::vector<cv::KeyPoint> keypts;
		int iters = 0; //for timing chess grid
		auto blobfinder = cv::BRISK::create();
		//blobfinder->setHarrisDetector(true);
		cv::Size2i gridSize(SmartDashboard::GetNumber("Grid Width", 8),
				SmartDashboard::GetNumber("Grid Height", 5));
		/*
		 SmartDashboard::PutNumber("Grid Width",  gridSize.width),
		 SmartDashboard::PutNumber("Grid Height", gridSize.height);
		 */
		bool wholeGridFound(false);
		uint16_t tries = 0;
		while (true) {
			// Tell the CvSink to grab a frame from the camera and put it
			// in the source mat.  If there is an error notify the output.
			if (cvSink.GrabFrame(mat) == 0) {
				// Send the output the error.
				outputStream.NotifyError(cvSink.GetError());
				// skip the rest of the current iteration
				continue;
			}
			if (++iters == 10) {
				++tries;
				iters = 0;
				/*
				 cv::cvtColor(mat, greymat, CV_BGR2GRAY);
				 cv::adaptiveThreshold(greymat, greymat, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 3, 20);
				 *///cv::inRange(mat, cv::Scalar(180,180,0),cv::Scalar(255,255,60), greymat);
				cv::transform(mat, greymat, red2black);
				blobfinder->detect(greymat, keypts);
				//cv::findContours(keypts, mat, mat);
				/*wholeGridFound = cv::findChessboardCorners(mat, gridSize, corners,
				 CV_CALIB_CB_FAST_CHECK |
				 CV_CALIB_CB_ADAPTIVE_THRESH |
				 CV_CALIB_CB_NORMALIZE_IMAGE);*/
				//SmartDashboard::PutNumber("corners", corners.size());
				//if(wholeGridFound) cornersList.push_back(corners);
				SmartDashboard::PutNumber("key points", keypts.size());
				SmartDashboard::PutNumber("tries", tries);
			}
			if (/*corners*/keypts.empty())
				// Put a rectangle on the image
				rectangle(mat, cv::Point(100, 100), cv::Point(400, 400),
						cv::Scalar(255, 255, 255), 1);
			else
				// draw the results
//				cv::drawChessboardCorners(mat, gridSize, corners, wholeGridFound);
				cv::drawKeypoints(mat, keypts, mat);

			// Give the output stream a new image to display
			outputStream.PutFrame(mat);
		}
	}
	void DisabledPeriodic() {
		Scheduler::GetInstance()->Run();
	}

	void AutonomousInit() {
		autonomousCommand = static_cast<Command*>(autoChooser.GetSelected());
		if (autonomousCommand != NULL)
			autonomousCommand->Start();
		CommandBase::shooter->ReloadParams();
	}

	void AutonomousPeriodic() {	//SmartDashboard::PutNumber("elev on target", CommandBase::elevator->OnTarget());
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

		SmartDashboard::PutNumber("launchspd", CommandBase::shooter->GetSpd());
	}

	void TestPeriodic() {
		lw->Run();
	}
public:
};

START_ROBOT_CLASS(Robot);

