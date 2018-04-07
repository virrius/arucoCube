#include"ICalib.h"
#include"AR.h"
int main()
{
	
	int cameraNum = 1;
	artem::ICalib C;
	C.setBoardSize(cv::Size2i(4, 4));
	if (!C.getCalibrationDataChess(cameraNum, 15))
		return 1;
	std::cout<<C.calibrate();
	C.showUndistorted(cameraNum);
	std::cout << C.getCameraMatrix();

	 
	artem::AR detect;
	cv::VideoCapture cam(cameraNum);
	cv::Mat frame;

	detect.getMarkers(cameraNum);
	return 0;
}