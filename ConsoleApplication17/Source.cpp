#include<opencv2\core.hpp>	
#include<opencv2\highgui.hpp>
#include<iostream>
#include<opencv2\imgproc.hpp>
#include<opencv2\calib3d.hpp>
#include<fstream>

 class calibratemecompletely {
 protected:
	 //����������� ����� ������ ��� ����������
	 const  int CalibNum = 15; 
	 //����� ������� ������
	 int goodCalib = 0;

	 const  cv::Size boardSize = cv::Size(4, 4);
	 std::vector<cv::Point3f> points3D;// �������
	 std::vector<cv::Point2f>corners; 
	 std::vector<std::vector<cv::Point3f>> objPoints3D;//���������� ������������
	 std::vector<std::vector<cv::Point2f>> imgPoints2D;//������������ �� �����������
	


	 cv::Mat cameraMatrix = cv::Mat(3, 3, CV_32FC1);
	 cv::Mat distCoeffs;
	 std::vector<cv::Mat> rvecs;
	 std::vector<cv::Mat> tvecs;

 public:
	 calibratemecompletely()
	 {
		 
		 for (int i = 0; i < boardSize.height*boardSize.width; i++)
		 {
			 
			 points3D.push_back(cv::Point3f(i/boardSize.width, i%boardSize.height, 0));
		 }
	 }
	 void ChessCalibration()
	 {
		 std::cout << "start calibration \n";
		 cv::VideoCapture cam(0);
		 cv::Mat image, grayImg;
		 //������� ������� ���������
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
			 cv::imshow("2",grayImg);
			 char key = cv::waitKey(100);
			 if (key == 27)
			 {
				 std::cout << "terminated  \n" ;
				 return;
			 }
		 }
		 
		//����������
		
		 cameraMatrix.ptr<float>(0)[0] = 1;
		 cameraMatrix.ptr<float>(1)[1] = 1;
		 cv::calibrateCamera(objPoints3D, imgPoints2D, boardSize, cameraMatrix, distCoeffs, rvecs, tvecs);
		
		 std::cout << "Calibrated succesfully  \n";
		 cv::destroyAllWindows();
		 cam.release();
	}
	 void ShowUndistorted()
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


};



int main()
{
	calibratemecompletely calib1;
	calib1.ChessCalibration();
	calib1.ShowUndistorted();











	return 0;
}