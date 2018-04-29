#include "RobotControl.h"


artem::RobotControl::RobotControl() :_CubeTranslationCoordinates(6), _CubeRotationCoordinates(6) {};

void artem::RobotControl::prepareAndStartTracking(const int cameraNum,  const int cubeMarkersSize)
{
	cv::Mat frame;
	cv::VideoCapture cam(cameraNum);
	cam >> frame;


	getRobotCoordinates();
	_C.loadCalibrationParameters();
	_Cube.generateDict(6, cubeMarkersSize);
	std::vector<cv::Vec3d> rvecs, tvecs;

	do {
		std::cout << markerIds.size();
		_Cube.getMarkersPoseEstimation(frame, _Cube.getMarkerLength(), _C.getCameraMatrix(), _C.getDistCoeffs(), markerIds, rvecs, tvecs, true);
		cv::imshow("Camera", frame);
		cv::waitKey(1);
	} while (markerIds.size() == 0);

	_mainCubeFace = markerIds[0];
	
	
	std::cout << "main cube face: "<<_mainCubeFace << std::endl << std::endl; //Debug1

	for (int i = 0; i < markerIds.size(); ++i)
	{
		_CubeRotationCoordinates[markerIds[i]] = rvecs[i];
		_CubeTranslationCoordinates[markerIds[i]] = tvecs[i];
	}

	cv::namedWindow("Camera", CV_WINDOW_AUTOSIZE);
	while (true)
	{
		cv::imshow("Camera", frame);
		cv::waitKey(1);
		cam >> frame;
		CubeTracking(frame);

	}
}

void artem::RobotControl::CubeTracking(cv::Mat & frame)
{
	std::vector<cv::Vec3d> rvecs, tvecs;
	_Cube.getMarkersPoseEstimation(frame, _Cube.getMarkerLength(), _C.getCameraMatrix(), _C.getDistCoeffs(), markerIds, rvecs, tvecs, true);
	updateRobotCoordinates(markerIds, tvecs);
	for (int i = 0; i < markerIds.size(); ++i)
	{

		_CubeRotationCoordinates[markerIds[i]] = rvecs[i];
		_CubeTranslationCoordinates[markerIds[i]] = tvecs[i];
	cv::waitKey(400);
	}
}

void artem::RobotControl::getRobotCoordinates()
{
	{
		_RobotTranslationCoordinates = cv::Vec3d(0, 0, 0); //todo

	};
}

void artem::RobotControl::updateRobotCoordinates(const std::vector<int>& markerids, const std::vector<cv::Vec3d>& tvecs)
{
	for (int i = 0; i<markerids.size(); ++i)
	{
		if (markerids[i] == _mainCubeFace)
		{

			_RobotTranslationCoordinates += (tvecs[i] - _CubeTranslationCoordinates[markerids[i]]); //mult?


		}

	};

	std::cout << _RobotTranslationCoordinates << std::endl;
}

