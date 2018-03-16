#include"ICalib.h"



void ICalib::GetCalibrationData_Chess()
{

	cv::VideoCapture cam(0);
	cv::Mat image, grayImg;
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
			std::cout << "captured! ";
			goodCalib++;
			std::cout << goodCalib << "/" << CalibNum << std::endl;

			cv::cornerSubPix(grayImg, corners, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.001));
			cv::drawChessboardCorners(grayImg, boardSize, corners, success);
		}

		cv::imshow("1", image);
		cv::imshow("2", grayImg);
		char key = cv::waitKey(100);
		if (key == 27)
		{
			std::cout << "terminated  \n";
			return;
		}
	}
	cv::destroyAllWindows();
	cam.release();
}
void ICalib::ShowUndistorted()
{
	cv::VideoCapture cam(0);
	cv::Mat frame, UndistFrame;
	while (true)
	{
		cam >> frame;
		cv::undistort(frame, UndistFrame, cameraMatrix, distCoeffs);
		cv::imshow("win1", frame);
		cv::imshow("win2", UndistFrame);

		cv::waitKey(1);

	}
	cv::destroyAllWindows();
	cam.release();
}