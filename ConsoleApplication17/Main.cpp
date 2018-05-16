#include"ICalib.h"
#include"IArucoMarkers.h"
#include<vector>
#include"RobotControl.h"
int main()
{
	
	int cameraNum =1;
	
	/*artem::ICalib C;
	C.setBoardSize(cv::Size2i(9, 6));
	if (!C.getCalibrationData(cameraNum,10, artem::ICalib::chessBoard))
		return 1;
	std::cout<<C.calibrate();
	
	C.saveCalibrationParameters("Calib.yml");
	C.showUndistorted(2);*/
	//C.loadCalibrationParameters();
	//artem::IArucoMarkers detect;
	//detect.generateDict(6, 8);
	//detect.showDictMarkers();
	//std::vector<cv::Vec3d> rvecs, tvecs;
	//detect.getMarkersCoordinates(C.getCameraMatrix(), C.getDistCoeffs(), cameraNum, rvecs, tvecs,0.05, true);

	artem::RobotControl robot;
	robot.prepareAndStartTracking(cameraNum, 8);
	
	return 0;
}