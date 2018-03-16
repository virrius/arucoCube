#pragma once
#include<opencv2\core.hpp>	
#include<opencv2\highgui.hpp>
#include<iostream>
#include<opencv2\imgproc.hpp>
#include<opencv2\calib3d.hpp>
#include"ICalib.h"


class Calibration: public ICalib {	
public:
	Calibration();
	void Calibrate();
};