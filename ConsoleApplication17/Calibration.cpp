#include"Calibration.h"

Calibration::Calibration(){
		for (int i = 0; i < boardSize.height*boardSize.width; i++)
		{
			points3D.push_back(cv::Point3f(i / boardSize.width, i%boardSize.height, 0));
		}
		cameraMatrix.ptr<float>(0)[0] = 1;
		cameraMatrix.ptr<float>(1)[1] = 1;
	}
void Calibration::Calibrate()
{
	std::cout << "start calibration \n";
	GetCalibrationData_Chess();
	cv::calibrateCamera(objPoints3D, imgPoints2D, boardSize, cameraMatrix, distCoeffs, rvecs, tvecs);
	std::cout << "Calibrated succesfully  \n";
}

