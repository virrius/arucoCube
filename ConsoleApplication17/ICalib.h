/**
* \file
* \brief Header file describes calibration interface
*/
#ifndef ICALIB_H
#define ICALIB_H

#include"Calibration.h"
#include<opencv2\core.hpp>	
#include<opencv2\highgui.hpp>
#include<iostream>
#include<opencv2\imgproc.hpp>
#include<opencv2\calib3d.hpp>

namespace artem 
{
	/**
	* 
	* \brief Calibration class extension for interacting with external data
	*/
	class ICalib :public Calibration {
	
		
	public:
		

		bool findPattern(pattern patternMode, const cv::Mat &grayImg, std::vector<cv::Point2f> &corners);
		
		void drawPattern(pattern patternMode, const cv::Mat& Img, const std::vector<cv::Point2f> &corners);

	//	bool getCalibrationDataChess(const int cameraNum, const int calibNum);

		
		/**
		* \brief getting calibration image data
		* \param[in] cameraNum camera for work
		* \param[in]  calibNum number of frames, required for start calibration
		* \param[in] patternMode name of calibration pattern
		* \return successful receipt of data
		*/
		bool getCalibrationData(const int cameraNum, const int calibNum, pattern patternMode);
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
		/**
		* \brief  save camera and distcoeffs matrixes to file
		*
		*/
		void saveCalibrationParameters(const std::string &fileToSave = "Calibration.yml");
		/**
		* \brief  load camera and distcoeffs matrixes from  file
		*
		*/
		void loadCalibrationParameters(const std::string &fileToLoad = "Calibration.yml");
		void loadCalibrationImages(const int count, const std::string &directory = "CalibImg/");
	};
}

#endif // !ICALIB_H
