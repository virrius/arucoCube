#include "IArucoMarkers.h"



void artem::IArucoMarkers::showDictMarkers(const int sidePixels, const int border)
{
	cv::Mat marker;
	for (int i = 0; i < _MarkersDict.get()->bytesList.rows; ++i)
	{
		cv::aruco::drawMarker(_MarkersDict, i, sidePixels, marker, border);
		cv::imshow(std::to_string(i), marker);
	}
	cv::waitKey();
	cv::destroyAllWindows();
}

void artem::IArucoMarkers::getMarkersCoordinates(const cv::Mat cameraMatrix, const  cv::Mat distCoeffs, const int cameraNum, std::vector<cv::Vec3d> &rvecs, std::vector<cv::Vec3d> &tvecs, const double markerLength, const bool drawMarkers)
{
	cv::Mat frame;
	cv::VideoCapture cam(cameraNum);

	std::vector<int> markerIds;
	std::vector<std::vector<cv::Point2f>> markerCorners;
	cv::Ptr<cv::aruco::DetectorParameters> parameters;


	cv::namedWindow("video", CV_WINDOW_AUTOSIZE);
	while (true)
	{
		cam >> frame;

		getMarkersPoseEstimation(frame, markerCorners, markerIds,markerLength, cameraMatrix, distCoeffs, rvecs, tvecs, drawMarkers);

		cv::imshow("video", frame);
		if (cv::waitKey(1) == 27)
		{
			cv::destroyWindow("video");
			return;
		}
	}
}



