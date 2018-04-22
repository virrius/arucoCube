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

		/**
		* \brief fillup vector of coordinates
		*/
		void setupObjPoints3D(std::vector<std::vector<cv::Point3f>> &objPoints3D);
	public:
		
		Calibration() = default;
		virtual ~Calibration() = default;

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
		/**
		* \brief  return camera distortion coefficients
		*
		*/
		cv::Mat getDistCoeffs() const;
		/**
		* \brief  save camera and distcoeffs matrixes to file
		*
		*/
		void saveCalibrationParameters(const std::string fileToSave= "Calibration.yml");
		/**
		* \brief  load camera and distcoeffs matrixes from  file
		*
		*/
		void loadCalibrationParameters(const std::string fileToLoad = "Calibration.yml");
	};

}

#endif // ! CALIBRATION_H
