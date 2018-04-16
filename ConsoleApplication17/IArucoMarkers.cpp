#include "IArucoMarkers.h"



void artem::IArucoMarkers::showDictMarkers()
{
	cv::Mat marker;
	for (int i = 0; i < _MarkersDict.get()->bytesList.rows; ++i)
	{
		cv::aruco::drawMarker(_MarkersDict, i, 200, marker, 1);
		cv::imshow(std::to_string(i), marker);
	}
	cv::waitKey();
	cv::destroyAllWindows();
}

void artem::IArucoMarkers::getMarkersCoordinates(const cv::Mat cameraMatrix, const  cv::Mat distCoeffs, const int cameraNum, std::vector<cv::Vec3d> &rvecs, std::vector<cv::Vec3d> &tvecs, const bool drawMarkers)
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

		getMarkersPoseEstimation(frame, markerCorners, markerIds, cameraMatrix, distCoeffs, rvecs, tvecs, drawMarkers);

		cv::imshow("video", frame);
		if (cv::waitKey(1) == 27)
		{
			cv::destroyWindow("video");
			return;
		}
	}
}



