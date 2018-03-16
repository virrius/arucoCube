#pragma once
#include<opencv2\core.hpp>	
#include<opencv2\highgui.hpp>
#include<iostream>
#include<opencv2\imgproc.hpp>
#include<opencv2\calib3d.hpp>
class ICalib {
protected:
	//����������� ����� ������ ��� ����������
	const  int CalibNum = 15;
	//����� ������� ������
	int goodCalib = 0;

	const  cv::Size boardSize = cv::Size(4, 4);
	std::vector<cv::Point3f> points3D;// �������
	std::vector<cv::Point2f>corners;
	std::vector<std::vector<cv::Point3f>> objPoints3D;//���������� ������������
	std::vector<std::vector<cv::Point2f>> imgPoints2D;//������������ �� �����������

	//�������������� ������
	cv::Mat cameraMatrix = cv::Mat(3, 3, CV_32FC1);
	cv::Mat distCoeffs;
	std::vector<cv::Mat> rvecs;
	std::vector<cv::Mat> tvecs;
public:
	void GetCalibrationData_Chess();
	void ShowUndistorted();
	
};