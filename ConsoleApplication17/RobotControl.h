/**
* \file
* \brief Header file describes robot control with Aruco cube
*/
#ifndef ROBOTCONTROl_H
#define ROBOTCONTROL_H

#include<opencv2\core.hpp>	
#include<opencv2\highgui.hpp>
#include<opencv2\imgproc.hpp>
#include"IArucoMarkers.h"
#include"ICalib.h"
#include<vector>

namespace artem {
	/**
	*
	* \brief class include tracking and processing  a cube as well as interacting with a robot
	*/
	class RobotControl
	{
	private:
		/// Enum of cube faces
		enum dice
		{
			top,
			up,
			left,
			right,
			down,				
			back
		};
		/// Calibration parameters
		ICalib _Calib;
		/// faces aruco dictionary
		IArucoMarkers _Cube;
		/// vectors of tralslaion and rotation robot coordinates
		cv::Vec3d _RobotTranslationCoordinates, _RobotRotationCoordinates;
		/// coordinates of each cube face
		std::vector<cv::Vec3d>  _CubeTranslationCoordinates, _CubeRotationCoordinates;
		///ID of the tracking cube face
		int _mainSurface;
		/// IDs of all visible cube faces
		std::vector<int> _MarkerIds;
		///rotation coeffitient to bring the current cube face coordinate system to the main
		cv::Mat _RotCoeff;
		
	public:
		
		RobotControl();
		/**
		* \brief load parameters and finding cube
		* \param[in] CameraNum camera for work
		* \param[in] cubeMarkersSize  size of cube face
		*/
		void prepareAndStartTracking(const int cameraNum, const int cubeMarkersSize);
		/**
		* \brief find new mainSurface
		*
		*/
		void mainSurfacelost();
		
		/**
		* \brief Tracking and updating coordinates
		*
		*/
		void CubeTracking(cv::Mat &frame,  std::vector<cv::Vec3d> rvecs,  std::vector<cv::Vec3d>& tvecs);
		/**
		* \brief receive robot rotation and translation coordinates
		*
		*/
		void getRobotCoordinates();
		/**
		* \brief Processing and updating robot coordinates
		*
		*/
		void updateRobotCoordinates(cv::Mat &frame, const std::vector<int> &markerids,const  std::vector<cv::Vec3d> &rvecs, const std::vector<cv::Vec3d> &tvecs);

		virtual ~RobotControl() = default;

	};
};
#endif // !ROBOTCONTROl_H
