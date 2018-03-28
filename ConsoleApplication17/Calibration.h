/**
* \file 
* \brief Header file describes opencv calibration logic
*/

#pragma once
#include<opencv2\core.hpp>	
#include<opencv2\highgui.hpp>
#include<iostream>
#include<opencv2\imgproc.hpp>
#include<opencv2\calib3d.hpp>

namespace Artem
{
	/**
	* \brief Calibration class, include data and function for calibration
	* 
	*
	*/
	class Calibration {

	protected:
		/// Size of calibration pattern;
		const cv::Size _boardSize; 
		/// Coordinates of calibration pattern
		std::vector<cv::Point3f> _points3D;
		/// Corners of calibration pattern
		std::vector<cv::Point2f> _corners;
		/// Vector of coordinates calibration patterns
		std::vector<std::vector<cv::Point3f>> _objPoints3D;
		/// Vector of corners calibration patterns 
		std::vector<std::vector<cv::Point2f>> _imgPoints2D;

		/// Intristic camera parameters
		cv::Mat _cameraMatrix;
		/// Camera distortion coefficients
		cv::Mat _distCoeffs;
public:
	/**
	* \brief Constructor. Initialize pattern size, coordinates and camera matrix 
	*/
		Calibration();
	/**
	* \brief Calibrating camera with dataset
	*/	
		void calibrate();
		/**
		* \brief return Intristic parameters.
		* 		
		*/
		cv::Mat getCameraMatrix() const;
	};

}