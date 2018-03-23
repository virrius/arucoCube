/**
* \file
* \brief Header file describes calibration interface
*/

#pragma once
#include<opencv2\core.hpp>	
#include<opencv2\highgui.hpp>
#include<iostream>
#include<opencv2\imgproc.hpp>
#include<opencv2\calib3d.hpp>
#include"Calibration.h"
namespace Artem 
{
	/**
	* 
	* \brief Calibration class extension for interacting with external data
	*/
	class ICalib :public Calibration {
	protected:

	public:
		/**
		* \brief getting calibration image data
		* \param[in] CameraNum camera for work
		* \return successful receipt of data
		*/
		bool GetCalibrationData_Chess(int CameraNum);
		/**
		* \brief Showing undistorted image
		* \param[in] CameraNum camera for work
		*/
		void ShowUndistorted(int CameraNum);

	};
}