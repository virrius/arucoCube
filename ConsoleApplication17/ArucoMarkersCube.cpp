#include "ArucoMarkersCube.h"
void artem::ArucoMarkersCube::getMarkersPoseEstimation(cv::Mat &frame, 
	std::vector<std::vector<cv::Point2f>> markerCorners,
	std::vector<int> &markerIds,
	const cv::Mat cameraMatrix, 
	const cv::Mat distCoeffs,
	std::vector<cv::Vec3d> &rvecs,
	std::vector<cv::Vec3d> &tvecs)
{                             
	cv::aruco::drawDetectedMarkers(frame, markerCorners, markerIds);
	cv::aruco::estimatePoseSingleMarkers(markerCorners, 0.05,cameraMatrix,distCoeffs,rvecs,tvecs);
	for (int i = 0; i<markerIds.size(); ++i)
		cv::aruco::drawAxis(frame, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 0.05);
}

void artem::ArucoMarkersCube::generateAndSaveDict(const std::string fileToSave )
{
	_MarkersDict= cv::aruco::generateCustomDictionary(6, 8);
	cv::FileStorage dictFile(fileToSave, cv::FileStorage::WRITE);
	dictFile << "MarkerSize" << (*_MarkersDict).markerSize;
	dictFile << "MaxCorrectionBits" << (*_MarkersDict).maxCorrectionBits;
	dictFile << "BytesList" << (*_MarkersDict).bytesList;
	cv::Mat marker;
	system("mkdir Markers");
	for (int i = 0; i < 6; ++i)
	{
		cv::aruco::drawMarker(_MarkersDict, i, 200, marker, 1);
		cv::imwrite("Markers/"+std::to_string(i)+".jpg", marker);
	}
	dictFile.release();
}
void artem::ArucoMarkersCube::loadDictfromFile(const std::string filename)
{
	cv::aruco::Dictionary ownDict;
	cv::FileStorage dictFile(filename, cv::FileStorage::READ);
	cv::Mat	bytesList;
	dictFile["BytesList"] >> bytesList;
	int markerSize;
	dictFile["MarkerSize"] >> markerSize;
	int maxCorrectionBits;
	dictFile["MaxCorrectionBits"] >> maxCorrectionBits;
	dictFile.release();
	_MarkersDict= cv::makePtr<cv::aruco::Dictionary>(cv::aruco::Dictionary(bytesList, markerSize, maxCorrectionBits));
	

}



