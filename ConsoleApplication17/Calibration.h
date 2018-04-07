/**
* \file 
* \brief Header file describes opencv calibration logic
*/
#ifndef  CALIBRATION_H
#define CALIBRATION_H

#include<opencv2\calib3d.hpp>
#include<opencv2\core.hpp>	
#include<opencv2\highgui.hpp>
#include<opencv2\imgproc.hpp>
#include<iostream>



namespace artem
{
	/**
	* \brief Calibration class, include data and function for calibration
	* 
	*
	*/
	class Calibration {

	protected:
		/// Size of calibration pattern;
		cv::Size _boardSize;		
		/// Vector of corners calibration patterns 
		std::vector<std::vector<cv::Point2f>> _imgPoints2D;
		/// Intristic camera parameters
		cv::Mat _cameraMatrix;
		/// Camera distortion coefficients
		cv::Mat _distCoeffs;
	public:
		
		Calibration() = default;
		virtual ~Calibration() = default;
		/**
		* \brief fillup vector of coordinates
		*/
		void setupObjPoints3D(std::vector<std::vector<cv::Point3f>> &objPoints3D, const int size);
			/**
			* \brief Calibrating camera with dataset
			* \return error
			*/
			double calibrate();
		/**
		* \brief return Intristic parameters.
		*
		*/
		cv::Mat getCameraMatrix() const;
	};

}

#endif // ! CALIBRATION_H
