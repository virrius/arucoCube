/**
* \file
* \brief Header file describes aruco markers class interface
*/
#ifndef  IARUCOMARKERS_H
#define IARUCOMARKERS_H
#include"ArucoMarkersCube.h"

namespace artem
{
	/**
	* \brief Aruco markers interface class with functions for show and input processing
	*
	*/
	class IArucoMarkers :public artem::ArucoMarkersCube
	{
	public:

		IArucoMarkers() = default;
		/**
		* \brief Show markers from dictionary 
		*
		*/
		void showDictMarkers(const int MarkerSize, const int sidePixels = 200, const int border = 1);
		/**
		* \brief finding markers and receiving their coordinates
		* \param[in] cameraMatrix Intristic camera parameters
		* \param[in] distCoeffs Camera distortion coefficients
		* \param[in] cameraNum Camera for work
		* \param[out] rvecs rotation vectors of markers
		* \param[out] tvecs translation vectors of markers
		* \param[in] drawMarkers draw borders and axis
		* \param[in] markerlength the length of the markers side, in meters(as normally)
		*/
		void getMarkersCoordinates(const cv::Mat cameraMatrix, const  cv::Mat distCoeffs, const int cameraNum, std::vector<cv::Vec3d> &rvecs, std::vector<cv::Vec3d> &tvecs, const double markerLength, const bool drawMarkers=0);
		
		virtual ~IArucoMarkers() = default;

	};

}

#endif
