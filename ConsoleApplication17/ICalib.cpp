#include"ICalib.h"




/*bool artem::ICalib::getCalibrationDataChess(const int cameraNum, const int calibNum)
{
	
	int goodCalib = 0;
	cv::VideoCapture cam(cameraNum);
	cv::Mat image, grayImg;
	cv::namedWindow("cam", CV_WINDOW_AUTOSIZE);
	std::vector<cv::Point2f> corners;
	bool success=false;
	while (goodCalib<calibNum)
	{
		cam >> image;
		cv::cvtColor(image, grayImg, CV_BGR2GRAY);
		cv::imshow("cam", image);
		switch (cv::waitKey(1))
		{
			case 27: 
			{
				return false;
				break;
			}
			case 13: 
			{
				success = cv::findChessboardCorners(grayImg, _boardSize, corners, cv::CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
				break;
			}
		
		}
		
		if (success)
		{
			_imgPoints2D.emplace_back(corners);
			goodCalib++;
			cv::drawChessboardCorners(image, _boardSize, corners, true);
			success = false;
			cv::imshow("cam", image);
			cv::waitKey(1000);
		}
		
	}
	cv::destroyAllWindows();
	cam.release();
	return true;
}*/

bool artem::ICalib::findPattern(pattern patternMode,const cv::Mat &grayImg, std::vector<cv::Point2f> &corners)
{
	switch (patternMode)
	{
		case circleGrid:
		{
			return  cv::findCirclesGrid(grayImg, _boardSize, corners, cv::CALIB_CB_SYMMETRIC_GRID);
			break;
		}
		case assymetricCircleGrid:
		{
			return  cv::findCirclesGrid(grayImg, _boardSize, corners,cv::CALIB_CB_ASYMMETRIC_GRID);
			break;
		}
		case chessBoard:
		{
			return cv::findChessboardCorners(grayImg, _boardSize, corners, cv::CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
			break;
		}
	}
}

void artem::ICalib::drawPattern(pattern patternMode, const cv::Mat & Img, const std::vector<cv::Point2f>& corners)
{
	cv::drawChessboardCorners(Img, _boardSize, corners, true);

}



bool artem::ICalib::getCalibrationData(const int cameraNum, const int calibNum, pattern patternMode)
{
	int goodCalib = 0;
	std::cout << "start";
	cv::VideoCapture cam(cameraNum);
	cv::Mat image, grayImg;
	cv::namedWindow("cam", CV_WINDOW_AUTOSIZE);
	std::vector<cv::Point2f> corners;
	while (goodCalib < calibNum)
	{
		cam >> image;
		cv::cvtColor(image, grayImg, CV_BGR2GRAY);
		cv::imshow("cam", image);
		switch (cv::waitKey(1))
		{
		case 27:
		{
			return false;
			break;
		}
		case 13:
		{	
			
			if (findPattern(patternMode, grayImg, corners))
			{
				
				_imgPoints2D.emplace_back(corners);
				goodCalib++;
				cv::drawChessboardCorners(image, _boardSize, corners, true);
				cv::imshow("cam", image);
				cv::waitKey(1000);
				std::cout << goodCalib<<std::endl;
				//Kill!
			}
			break;
		}

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

void artem::ICalib::saveCalibrationParameters(const std::string &fileToSave)
{
	cv::FileStorage calibFile(fileToSave, cv::FileStorage::WRITE);
	calibFile << "Camera matrix" << _cameraMatrix;
	calibFile << "Distortion coefficients" << _distCoeffs;
	calibFile.release();

}

void artem::ICalib::loadCalibrationImages(const int count, const std::string & directory)
{
	std::vector<cv::Point2f> corners;
	cv::Mat grayImg;
	for (int i = 0; i < count; ++i)
	{		
		cv::cvtColor(cv::imread(directory+ std::to_string(i)+".png"), grayImg, CV_BGR2GRAY);
		cv::findChessboardCorners(grayImg, _boardSize, corners, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
		_imgPoints2D.emplace_back(corners);
	}
		
}

void artem::ICalib::loadCalibrationParameters(const std::string &fileToLoad)
{
	cv::FileStorage calibFile(fileToLoad, cv::FileStorage::READ);
	calibFile["Camera matrix"] >> _cameraMatrix;
	calibFile["Distortion coefficients"] >> _distCoeffs;
	calibFile.release();

}