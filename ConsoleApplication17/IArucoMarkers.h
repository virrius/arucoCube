#ifndef  IARUCOMARKERS_H
#define IARUCOMARKERS_H
#include"ArucoMarkersCube.h"

namespace artem
{
	class IArucoMarkers :public artem::ArucoMarkersCube
	{
	public:

		IArucoMarkers() = default;
		void showDictMarkers();
		void getMarkers(const cv::Mat cameraMatrix, const  cv::Mat distCoeffs, const int cameraNum, std::vector<cv::Vec3d> &rvecs, std::vector<cv::Vec3d> &tvecs);

		virtual ~IArucoMarkers() = default;

	};

}

#endif
