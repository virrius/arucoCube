#include"Calibration.h"

Artem::Calibration::Calibration(){
		 boardSize =  cv::Size(4, 4);
		 cv::Mat cameraMatrix = cv::Mat(3, 3, CV_32FC1);
		for (int i = 0; i < boardSize.width; i++)
			for (int j = 0; j < boardSize.height; j++)
			{
				points3D.push_back(cv::Point3f(i,j, 0));

			}
	}
void Artem::Calibration::Calibrate()
{
	
	std::vector<cv::Mat> rvecs;
	std::vector<cv::Mat> tvecs;
	cv::calibrateCamera(objPoints3D, imgPoints2D, boardSize, cameraMatrix, distCoeffs, rvecs, tvecs);
	
}
