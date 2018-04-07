#include"ICalib.h"




bool artem::ICalib::getCalibrationDataChess(const int cameraNum, const int calibNum)
{
	
	int goodCalib = 0;
	cv::VideoCapture cam(cameraNum);
	cv::Mat image, grayImg;
	std::vector<cv::Point2f> corners;
	while (goodCalib<calibNum)
	{
		cam >> image;
		cv::cvtColor(image, grayImg, CV_BGR2GRAY);
		bool success = cv::findChessboardCorners(image, _boardSize, corners, cv::CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
		if (success)
		{
			//check
			_imgPoints2D.emplace_back(corners);
			 //_objPoints3D.emplace_back(_points3D);
			
			goodCalib++;
		}
		if (cv::waitKey(1) == 27)
		{
			return false;
		}
	}
	cv::destroyAllWindows();
	cam.release();
	return true;
}
void artem::ICalib::showUndistorted(const int cameraNum)
{
	cv::VideoCapture cam(cameraNum);
	cv::Mat frame, UndistFrame;
	cv::namedWindow("frame", CV_WINDOW_AUTOSIZE);
	cv::namedWindow("UndsistFrame", CV_WINDOW_AUTOSIZE);
	while (true)
	{
		cam >> frame;
		cv::undistort(frame, UndistFrame, _cameraMatrix, _distCoeffs);
		cv::imshow("frame", frame);
		cv::imshow("UndsistFrame", UndistFrame);

		if (cv::waitKey(1) == 27)
		{
			return;
		}

	}
	cv::destroyWindow("frame");
	cv::destroyWindow("UndistFrame");
}

void artem::ICalib::setBoardSize(const cv::Size2i size)
{
	_boardSize = size;
}
