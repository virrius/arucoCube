/**
* \file
* \brief Header file describes calibration interface
*/
#ifndef ICALIB_H
#define ICALIB_H


#include<opencv2\core.hpp>	
#include<opencv2\highgui.hpp>
#include<iostream>
#include<opencv2\imgproc.hpp>
#include<opencv2\calib3d.hpp>
#include"Calibration.h"
namespace artem 
{
	/**
	* 
	* \brief Calibration class extension for interacting with external data
	*/
	class ICalib :public Calibration {
	public:
		/**
		* \brief getting calibration image data
		* \param[in] cameraNum camera for work
		* \param[in]  calibNum number of frames, required for start calibration
		* \return successful receipt of data
		*/
		bool getCalibrationDataChess(const int cameraNum, const int calibNum);
		/**
		* \brief Showing undistorted image
		* \param[in] CameraNum camera for work
		*/
		void showUndistorted(const int cameraNum);
		/**
		* \brief set size
		* \param[in] size Size of calibration pattern
		*/
		void setBoardSize( const cv::Size2i size);
	};
}

#endif // !ICALIB_H
