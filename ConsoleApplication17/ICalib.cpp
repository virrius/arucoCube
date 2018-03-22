#include"ICalib.h"




bool ICalib::GetCalibrationData_Chess(int CameraNum)
{
	int CalibNum=15;
	int goodCalib = 0;
	
	cv::VideoCapture cam(CameraNum);
	cv::Mat image, grayImg;
	cv::namedWindow("ColoredCalibrationImage", CV_WINDOW_AUTOSIZE);
	cv::namedWindow("GrayCalibrationImage", CV_WINDOW_AUTOSIZE);
	//создаем систему уравнений
	while (goodCalib<CalibNum)
	{
		cam >> image;
		cv::cvtColor(image, grayImg, CV_BGR2GRAY);
		bool success = cv::findChessboardCorners(image, boardSize, corners, cv::CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
		if (success)
		{
			imgPoints2D.push_back(corners);
			objPoints3D.push_back(points3D);
			
			goodCalib++;
			

			cv::cornerSubPix(grayImg, corners, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.001));
			cv::drawChessboardCorners(grayImg, boardSize, corners, success);
		}
		
		cv::imshow("ColoredCalibrationImage", image);
		cv::imshow("GrayCalibrationImage", grayImg);
		
		if (cv::waitKey(5) == 27)
		{
		
			return false;
		}
	}
	cv::destroyAllWindows();
	cam.release();
	return true;
}
void ICalib::ShowUndistorted(int CameraNum)
{
	cv::VideoCapture cam(CameraNum);
	cv::Mat frame, UndistFrame;
	cv::namedWindow("frame", CV_WINDOW_AUTOSIZE);
	cv::namedWindow("UndsistFrame", CV_WINDOW_AUTOSIZE);
	while (true)
	{
		cam >> frame;
		cv::undistort(frame, UndistFrame, cameraMatrix, distCoeffs);
		cv::imshow("frame", frame);
		cv::imshow("UndsistFrame", UndistFrame);

		cv::waitKey(1);

	}
	cv::destroyAllWindows();
	cam.release();
}