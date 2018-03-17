#pragma once
#include<opencv2\core.hpp>	
#include<opencv2\highgui.hpp>
#include<iostream>
#include<opencv2\imgproc.hpp>
#include<opencv2\calib3d.hpp>
#include"Calibration.h"
class ICalib:public  Calibration{
protected:
	//����������� ����� ������ ��� ����������
	const  int CalibNum = 15;
	//����� ������� ������
	int goodCalib = 0;

public:
	void GetCalibrationData_Chess();
	void ShowUndistorted();
	
};