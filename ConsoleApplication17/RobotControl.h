#ifndef ROBOTCONTROl_H
#define ROBOTCONTROL_H

#include<opencv2\core.hpp>	
#include<opencv2\highgui.hpp>
#include<opencv2\imgproc.hpp>
#include"IArucoMarkers.h"
#include"ICalib.h"
#include<vector>

namespace artem {
	class RobotControl
	{
	private:
		enum dice
		{
			top,
			up,
			left,
			right,
			down,
			back
		};
		ICalib _C;
		IArucoMarkers _Cube;
		cv::Vec3d _RobotTranslationCoordinates, _RobotRotationCoordinates;
		std::vector<cv::Vec3d>  _CubeTranslationCoordinates, _CubeRotationCoordinates;
		int _mainSurface;
		std::vector<int> markerIds; //?
		cv::Mat coeff;

	public:
		RobotControl();
		void prepareAndStartTracking(const int cameraNum, const int cubeMarkersSize);

		void mainSurfacelost();//const std::vector<cv::Vec3d>& rvecs, const std::vector<cv::Vec3d>& tvecs);
		

		void CubeTracking(cv::Mat &frame,  std::vector<cv::Vec3d> rvecs,  std::vector<cv::Vec3d>& tvecs);

		void getRobotCoordinates();

		void updateRobotCoordinates(cv::Mat &frame, const std::vector<int> &markerids,  std::vector<cv::Vec3d> rvecs, const std::vector<cv::Vec3d> &tvecs);

		virtual ~RobotControl() = default;

	};
};
#endif // !ROBOTCONTROl_H
