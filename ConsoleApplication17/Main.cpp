#include"ICalib.h"
#include"IArucoMarkers.h"
#include<iostream>
#include<vector>
#include"RobotControl.h"

int main()
{
	
	int cameraNum =0;
	
	artem::ICalib C;
	/*C.setBoardSize(cv::Size2i(4, 11));
	if (!C.getCalibrationData(cameraNum,10, artem::ICalib::assymetricCircleGrid))
		return 1;
	std::cout<<C.calibrate(artem::ICalib::assymetricCircleGrid);*/
	
	//C.saveCalibrationParameters("Calib.yml");
	//C.showUndistorted(cameraNum);
	//C.loadCalibrationParameters();
	artem::IArucoMarkers detect;
	detect.generateDict(6,4);
	//detect.showDictMarkers();
	//std::vector<cv::Vec3d> rvecs, tvecs;
	//detect.getMarkersCoordinates(C.getCameraMatrix(), C.getDistCoeffs(), cameraNum, rvecs, tvecs,0.05, true);

	//artem::RobotControl robot;


	//artem::IArucoMarkers cube;
	//cube.showDictMarkers(8);
	//cv::waitKey();
	//robot.prepareAndStartTracking(cameraNum, 8);
	
	return 0;
} 