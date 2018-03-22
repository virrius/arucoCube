#pragma once
#include<opencv2\core.hpp>	
#include<opencv2\highgui.hpp>
#include<iostream>
#include<opencv2\imgproc.hpp>
#include<opencv2\calib3d.hpp>

namespace Artem
{

	class Calibration {

	protected:
		//характеристики объекта
		cv::Size boardSize;
		std::vector<cv::Point3f> points3D;// вершины
		std::vector<cv::Point2f>corners;
		std::vector<std::vector<cv::Point3f>> objPoints3D;//физическое расположение
		std::vector<std::vector<cv::Point2f>> imgPoints2D;//расположение на изображении

	  //характеристики камеры
		cv::Mat cameraMatrix;
		cv::Mat distCoeffs;
public:
		Calibration();
		void Calibrate();
	};

}