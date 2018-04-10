#include"Calibration.h"
#
void artem::Calibration::setupObjPoints3D(std::vector<std::vector<cv::Point3f>> &objPoints3D)
{
	std::vector<cv::Point3f> points3D;
	for (int i = 0; i < _boardSize.width; ++i)
		for (int j = 0; j < _boardSize.height; ++j)
		{
			points3D.emplace_back(cv::Point3f(i, j, 0));
		}
	for (int i = 0; i < _imgPoints2D.size; ++i)
	{
		objPoints3D.emplace_back(points3D);
	}

}
double artem::Calibration::calibrate()
{
	std::vector<std::vector<cv::Point3f>> _objPoints3D;
	
	setupObjPoints3D(_objPoints3D);
	std::vector<cv::Mat> rvecs;
	std::vector<cv::Mat> tvecs;
	return cv::calibrateCamera(_objPoints3D, _imgPoints2D, _boardSize, _cameraMatrix, _distCoeffs, rvecs, tvecs);
	
}

cv::Mat artem::Calibration::getCameraMatrix() const
{
	return _cameraMatrix.clone();
}

cv::Mat artem::Calibration::getDistCoeffs() const
{
	return _distCoeffs.clone();
}
