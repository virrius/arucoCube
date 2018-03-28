#pragma once
#include<iostream>
#include<opencv2\core.hpp>
#include<opencv2\highgui.hpp>
#include"aruco.h"

namespace Artem {
	class AR
	{
	public:
		AR();
		void GetMarkers(int CameraNum);
		~AR();
	};

}
