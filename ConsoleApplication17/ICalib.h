#pragma once
#include<opencv2\core.hpp>	
#include<opencv2\highgui.hpp>
#include<iostream>
#include<opencv2\imgproc.hpp>
#include<opencv2\calib3d.hpp>
class ICalib {
protected:
	//необходимое число кадров для калибровки
	const  int CalibNum = 15;
	//число удачных кадров
	int goodCalib = 0;

	const  cv::Size boardSize = cv::Size(4, 4);
	std::vector<cv::Point3f> points3D;// вершины
	std::vector<cv::Point2f>corners;
	std::vector<std::vector<cv::Point3f>> objPoints3D;//физическое расположение
	std::vector<std::vector<cv::Point2f>> imgPoints2D;//расположение на изображении

	//характеристики камеры
	cv::Mat cameraMatrix = cv::Mat(3, 3, CV_32FC1);
	cv::Mat distCoeffs;
	std::vector<cv::Mat> rvecs;
	std::vector<cv::Mat> tvecs;
public:
	void GetCalibrationData_Chess();
	void ShowUndistorted();
	
};