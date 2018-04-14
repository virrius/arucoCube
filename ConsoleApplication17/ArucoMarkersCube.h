#ifndef  ARUCOMARKERSCUBE_H
#define ARUCOMARKERSCUBE_H


#include"aruco.h"
#include<iostream>
#include<opencv2\core.hpp>
#include<opencv2\highgui.hpp>


namespace artem 
{
	class ArucoMarkersCube
	{
	protected:
		cv::Ptr<cv::aruco::Dictionary> _MarkersDict;
		void getMarkersPoseEstimation(cv::Mat &frame, std::vector<std::vector<cv::Point2f>> markerCorners, std::vector<int> &markerIds, const cv::Mat cameraMatrix, const cv::Mat distcoeffs, std::vector<cv::Vec3d> &rvecs,
			std::vector<cv::Vec3d> &tvecs);
	public:
		ArucoMarkersCube() = default;
		virtual ~ArucoMarkersCube() = default;
		
		void generateAndSaveDict(const std::string fileToSave= "ownDict.yml");
		void loadDictfromFile(const std::string filename = "ownDict.yml");
		

	};

}
#endif

