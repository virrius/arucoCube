#include "ArucoMarkersCube.h"

void artem::ArucoMarkersCube::getMarkersPoseEstimation(cv::Mat &frame, 
	std::vector<std::vector<cv::Point2f>> markerCorners,
	std::vector<int> &markerIds,
	const cv::Mat cameraMatrix, 
	const cv::Mat distCoeffs,
	std::vector<cv::Vec3d> &rvecs,
	std::vector<cv::Vec3d> &tvecs,
	const bool drawMarkers)
{                    
	cv::aruco::detectMarkers(frame, _MarkersDict, markerCorners, markerIds);
	if (markerIds.size() > 0)
	{
		
		cv::aruco::estimatePoseSingleMarkers(markerCorners, 0.05, cameraMatrix, distCoeffs, rvecs, tvecs);

		if (drawMarkers)
		{
			cv::aruco::drawDetectedMarkers(frame, markerCorners, markerIds);
			for (int i = 0; i < markerIds.size(); ++i)
				cv::aruco::drawAxis(frame, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.05);
		}
		
	}
}

void artem::ArucoMarkersCube::generateDict(int numMarkers, int markersSize, const cv::Ptr<cv::aruco::Dictionary> &baseDict)
{
	_MarkersDict= cv::aruco::generateCustomDictionary(numMarkers,markersSize,baseDict);
	saveMarkersFromDict(_MarkersDict);
	
}

void artem::ArucoMarkersCube::generateDict(int numMarkers, int markersSize)
{
	_MarkersDict = cv::aruco::generateCustomDictionary(numMarkers, markersSize);
	saveMarkersFromDict(_MarkersDict);
}

void artem::ArucoMarkersCube::saveMarkersFromDict(const cv::Ptr<cv::aruco::Dictionary>& Dict)
{
	cv::Mat marker;
	
	system("mkdir Markers");
	for (int i = 0; i <Dict.get()->bytesList.rows; ++i)
	{
		cv::aruco::drawMarker(_MarkersDict, i, 200, marker, 1);
		cv::imwrite("Markers/" + std::to_string(i) + ".jpg", marker);
	}
}



