
#include"aruco.h"
#include<iostream>
#include<opencv2\core.hpp>
#include<opencv2\highgui.hpp>


namespace artem {
	class AR
	{
	public:
		AR();
		void getMarkers(int cameraNum);
		~AR();
	};

}
