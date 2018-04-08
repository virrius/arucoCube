#include "AR.h"



artem::AR::AR()
{
}

void artem::AR::getMarkers(int CameraNum)
{
	cv::Mat Frame;
	cv::VideoCapture cam(CameraNum);
	cv::Ptr<cv::aruco::Dictionary> dict = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
	for (int i = 0; i < 6; ++i)
	{
		cv::aruco::drawMarker(dict, i, 200, Frame, 1);
		cv::imshow(std::to_string(i), Frame);
	}
	cv::waitKey();
	std::vector<int> markerIds;
	std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;
	cv::Ptr<cv::aruco::DetectorParameters> parameters;
	cv::namedWindow("1",CV_WINDOW_AUTOSIZE);
	while (true)
	{
		cam >> Frame;
		cv::aruco::detectMarkers(Frame, dict, markerCorners, markerIds);

		if (markerIds.size() > 0)
		{
			std::cout << "G";
			cv::aruco::drawDetectedMarkers(Frame, markerCorners, markerIds);			
			
		}
		cv::imshow("1", Frame);
		cv::waitKey(1);
	}
	cv::Mat markerImage;
	cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
	cv::aruco::drawMarker(dictionary, 23, 200, markerImage, 1);
	cv::namedWindow("!", CV_WINDOW_AUTOSIZE);
	cv::imshow("!",markerImage);
	cv::waitKey();
}


artem::AR::~AR() = default;
