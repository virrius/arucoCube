#ifndef  AR_H
#define AR_H


#include"aruco.h"
#include<iostream>
#include<opencv2\core.hpp>
#include<opencv2\highgui.hpp>


namespace artem 
{
	class AR
	{

	public:
		AR() = default;
		void getMarkers(int cameraNum);
		void generateAndSaveDict(const std::string fileToSave= "ownDict.yml");
		cv::aruco::Dictionary loadDictfromFile(const std::string filename = "ownDict.yml");
		
	};

}

#endif // ! AR_H
