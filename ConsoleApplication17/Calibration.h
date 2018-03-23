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
		cv::Size boardSize; 
		/// Coordinates of calibration pattern
		std::vector<cv::Point3f> points3D;
		/// Corners of calibration pattern
		std::vector<cv::Point2f>corners;
		/// Vector of coordinates calibration patterns
		std::vector<std::vector<cv::Point3f>> objPoints3D;
		/// Vector of corners calibration patterns 
		std::vector<std::vector<cv::Point2f>> imgPoints2D;

		/// Intristic camera parameters
		cv::Mat cameraMatrix;
		/// Camera distortion coefficients
		cv::Mat distCoeffs;
public:
	/**
	* \brief Constructor. Initialize pattern size, coordinates and camera matrix 
	*/
		Calibration();
	/**
	* \brief Calibrating camera with dataset
	*/	
		void Calibrate();
	};

}