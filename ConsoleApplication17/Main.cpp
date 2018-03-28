#include"ICalib.h"
#include"AR.h"
int main()
{
	int cameraNum = 0;
	Artem::ICalib C;
	if (!C.GetCalibrationData_Chess(CameraNum))
		return 1;
	C.Calibrate();
	C.ShowUndistorted(CameraNum);
	std::cout << C.getCameraMatrix();

	 
	Artem::AR detect;
	cv::VideoCapture cam(cameraNum);
	cv::Mat frame;

	detect.GetMarkers(cameraNum);
	return 0;
}