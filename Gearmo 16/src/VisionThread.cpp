/*
 * VisionThread.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: Developer: PIH
 */

#include "WPILib.h"

// For the cameras
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>

void VisionThread() {
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

