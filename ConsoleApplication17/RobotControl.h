#ifndef ROBOTCONTROl_H
#define ROBOTCONTROL_H

#include<opencv2\core.hpp>	
#include<opencv2\highgui.hpp>
#include<opencv2\imgproc.hpp>
#include<vector>
#include"IArucoMarkers.h"
#include"ICalib.h"

namespace artem {
	class RobotControl
	{
	private:
		ICalib _C;
		IArucoMarkers _Cube;
		cv::Vec3d _RobotTranslationCoordinates, _RobotRotationCoordinates;
		std::vector<cv::Vec3d>  _CubeTranslationCoordinates, _CubeRotationCoordinates;		
		int _mainCubeFace;
		std::vector<int> markerIds;
	public:
		RobotControl();

		void prepareAndStartTracking(const int cameraNum,  const int cubeMarkersSize);

		void CubeTracking(cv::Mat &frame);

		void getRobotCoordinates();
		
		void updateRobotCoordinates(const std::vector<int> &markerids, const std::vector<cv::Vec3d> &tvecs);
		
		virtual ~RobotControl() = default;
	};
}
#endif // !ROBOTCONTROl_H
