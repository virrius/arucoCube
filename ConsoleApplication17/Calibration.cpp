#include"Calibration.h"

Artem::Calibration::Calibration():_boardSize(cv::Size(4,4)), _cameraMatrix(cv::Mat(3,3,CV_32FC1)){
		
		for (int i = 0; i < _boardSize.width; i++)
			for (int j = 0; j < _boardSize.height; j++)
			{
				_points3D.push_back(cv::Point3f(i,j, 0));

			}
	}
void Artem::Calibration::calibrate()
{
	
	std::vector<cv::Mat> rvecs;
	std::vector<cv::Mat> tvecs;
	cv::calibrateCamera(_objPoints3D, _imgPoints2D, _boardSize, _cameraMatrix, _distCoeffs, rvecs, tvecs);
	
}

cv::Mat Artem::Calibration::getCameraMatrix() const
{
	return _cameraMatrix;
}
