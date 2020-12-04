#include "ArucoMarkersCube.h"
#include <experimental/filesystem>

void artem::ArucoMarkersCube::getMarkersPoseEstimation(cv::Mat &frame, 
	//std::vector<std::vector<cv::Point2f>> markerCorners,
	//std::vector<int> &markerIds,
	const double markerLength,
	const cv::Mat cameraMatrix, 
	const cv::Mat distCoeffs,
	std::vector<int> &markerIds,
	std::vector<cv::Vec3d> &rvecs,
	std::vector<cv::Vec3d> &tvecs,
	const bool drawMarkers)
{     
	;
	std::vector<std::vector<cv::Point2f>> markerCorners;

	cv::aruco::detectMarkers(frame, _MarkersDict, markerCorners, markerIds);
	if (markerIds.size() > 0)
	{
	
		cv::aruco::estimatePoseSingleMarkers(markerCorners, markerLength, cameraMatrix, distCoeffs, rvecs, tvecs);

		if (drawMarkers)
		{
			cv::aruco::drawDetectedMarkers(frame, markerCorners, markerIds);
			for (int i = 0; i < markerIds.size(); ++i)
				cv::aruco::drawAxis(frame, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], markerLength);
		}
		
	}
}

void artem::ArucoMarkersCube::generateDict(const int numMarkers, const int markersSize, const cv::Ptr<cv::aruco::Dictionary> &baseDict, const int sidePixels, const int border)
{
	_MarkersDict= cv::aruco::generateCustomDictionary(numMarkers,markersSize,baseDict);
	saveMarkersFromDict(sidePixels,border,_MarkersDict);
	
}

void artem::ArucoMarkersCube::generateDict(const int numMarkers, const int markersSize, const int sidePixels, const int border)
{
	_MarkersDict = cv::aruco::generateCustomDictionary(numMarkers, markersSize);
	saveMarkersFromDict(sidePixels,border,_MarkersDict);
}

void artem::ArucoMarkersCube::saveMarkersFromDict(const int sidePixels, const int border, const cv::Ptr<cv::aruco::Dictionary>& Dict)
{
	cv::Mat marker;
	if (std::experimental::filesystem::create_directory("Markers"))
	for (int i = 0; i <Dict.get()->bytesList.rows; ++i)
	{
		cv::aruco::drawMarker(_MarkersDict, i, sidePixels, marker, border);
		cv::imwrite("Markers/" + std::to_string(i) + ".png", marker);
	}
}

double artem::ArucoMarkersCube::getMarkerLength() const
{
	return _cubeMarkersLength;
}
void artem::ArucoMarkersCube::setMarkerLength(const double L)
{
	this->_cubeMarkersLength = L;
}




