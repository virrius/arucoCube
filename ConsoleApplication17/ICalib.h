#pragma once
#include<opencv2\core.hpp>	
#include<opencv2\highgui.hpp>
#include<iostream>
#include<opencv2\imgproc.hpp>
#include<opencv2\calib3d.hpp>
#include"Calibration.h"
class ICalib:public  Calibration{
protected:
	//необходимое число кадров для калибровки
	const  int CalibNum = 15;
	//число удачных кадров
	int goodCalib = 0;

public:
	void GetCalibrationData_Chess();
	void ShowUndistorted();
	
};