#include"ICalib.h"
#include"IArucoMarkers.h"
int main()
{
	
	int cameraNum = 0;
	artem::ICalib C;
	/*C.setBoardSize(cv::Size2i(4, 4));
	if (!C.getCalibrationDataChess(cameraNum, 15))
		return 1;
	std::cout<<C.calibrate();*/
	C.loadCalibrationParameters();
	artem::IArucoMarkers detect;
	detect.generateAndSaveDict();
	detect.loadDictfromFile();
	detect.showDictMarkers();
	std::vector<cv::Vec3d> rvecs, tvecs;
	detect.getMarkers(C.getCameraMatrix(), C.getDistCoeffs(), cameraNum,rvecs,tvecs);
	return 0;
}