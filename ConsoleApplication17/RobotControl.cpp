#include "RobotControl.h"


cv::Vec3d rotationMatrixToEulerAngles(cv::Mat &R)
{


	float sy = sqrt(R.at<double>(0, 0) * R.at<double>(0, 0) + R.at<double>(1, 0) * R.at<double>(1, 0));

	bool singular = sy < 1e-6; // If

	float x, y, z;
	if (!singular)
	{
		x = atan2(R.at<double>(2, 1), R.at<double>(2, 2));
		y = atan2(-R.at<double>(2, 0), sy);
		z = atan2(R.at<double>(1, 0), R.at<double>(0, 0));
	}
	else
	{
		x = atan2(-R.at<double>(1, 2), R.at<double>(1, 1));
		y = atan2(-R.at<double>(2, 0), sy);
		z = 0;
	}
	
	return cv::Vec3d(x, y, z);
};
cv::Mat eulerAnglesToRotationMatrix(cv::Vec3f &theta)
{
	// Calculate rotation about x axis
	cv::Mat R_x = (cv::Mat_<double>(3, 3) <<
		1, 0, 0,
		0, cos(theta[0]), -sin(theta[0]),
		0, sin(theta[0]), cos(theta[0])
		);

	// Calculate rotation about y axis
	cv::Mat R_y = (cv::Mat_<double>(3, 3) <<
		cos(theta[1]), 0, sin(theta[1]),
		0, 1, 0,
		-sin(theta[1]), 0, cos(theta[1])
		);

	// Calculate rotation about z axis
	cv::Mat R_z = (cv::Mat_<double>(3, 3) <<
		cos(theta[2]), -sin(theta[2]), 0,
		sin(theta[2]), cos(theta[2]), 0,
		0, 0, 1);


	// Combined rotation matrix
	cv::Mat R = R_z * R_y * R_x;

	return R;

}




artem::RobotControl::RobotControl() :_CubeTranslationCoordinates(6), _CubeRotationCoordinates(6) {};

void artem::RobotControl::prepareAndStartTracking(const int cameraNum,  const int cubeMarkersSize)
{
	
	cv::Mat frame;
	cv::VideoCapture cam(cameraNum);
	cv::namedWindow("Camera", CV_WINDOW_AUTOSIZE);

	getRobotCoordinates();
	_Calib.loadCalibrationParameters();
	_Cube.generateDict(6, cubeMarkersSize);

	std::vector<cv::Vec3d> rvecs, tvecs;
	do {
		cam >> frame;
		_Cube.getMarkersPoseEstimation(frame, _Cube.getMarkerLength(), _Calib.getCameraMatrix(), _Calib.getDistCoeffs(), _MarkerIds, rvecs, tvecs, true);
		cv::imshow("Camera", frame);
		cv::waitKey(1);		
	} while (_MarkerIds.size()==0);

	mainSurfacelost();	

	for (int i = 0; i < _MarkerIds.size(); ++i)
	{
		_CubeRotationCoordinates[_MarkerIds[i]] = rvecs[i];
		_CubeTranslationCoordinates[_MarkerIds[i]] = tvecs[i];
	}

	
	while (true)
	{
		cv::imshow("Camera", frame);
		cv::waitKey(1);
		cam >> frame;
		CubeTracking(frame,rvecs,tvecs);

	}
}

void artem::RobotControl::mainSurfacelost()
{
	if (_MarkerIds.size() ==0)
		return;
	_mainSurface = _MarkerIds[0];
	

		switch (_mainSurface)
		{
		case top:
		{
			_RotCoeff = (cv::Mat_<double>(3, 3) <<
				1, 0, 0,
				0, 1, 0,
				0, 0, 1);
			std::cout << "Top" << std::endl;
			break;
		}
		case up:
		{
			cv::Mat coeff1 = (cv::Mat_<double>(3, 3) <<
				1, 0, 0,
				0, cos(CV_PI/2), -sin(CV_PI / 2),
				0, sin(CV_PI / 2), cos(CV_PI / 2));

			_RotCoeff = coeff1;//coeff1.t();
			std::cout << "up" << std::endl;
			break;

		}
		case left:
		{
			cv::Mat coeff1 = (cv::Mat_<double>(3, 3) <<
				cos(CV_PI / 2), 0, sin(CV_PI / 2),
				0, 1, 0,
				-sin(CV_PI / 2), 0, cos(CV_PI / 2)
				);
	
			_RotCoeff = coeff1;// coeff1.t();
			std::cout << "Left"<<std::endl;
			break;
			
		}
		case right:
		{	
			cv::Mat coeff1 = (cv::Mat_<double>(3, 3) <<
			cos(CV_PI / 2), 0, -sin(CV_PI / 2),

			0, 1, 0,
			sin(CV_PI / 2), 0, cos(CV_PI / 2)

			);
			_RotCoeff = coeff1;// coeff1.t();
			std::cout << "Right" << std::endl;
			break;
		}
		case down:
		{
			cv::Mat coeff1 = (cv::Mat_<double>(3, 3) <<
				1, 0, 0,
				0, cos(CV_PI / 2), sin(CV_PI / 2),
				0, -sin(CV_PI / 2), cos(CV_PI / 2));

			_RotCoeff = coeff1;//coeff1.t();
			std::cout << "down" << std::endl;
			break;
		}
		case back:
		{
			cv::Mat coeff1 = (cv::Mat_<double>(3, 3) <<
				cos(CV_PI), 0, -sin(CV_PI),
				0, 1, 0,				
				sin(CV_PI), 0, cos(CV_PI));
			_RotCoeff = coeff1;// coeff1.t();
			std::cout << "Back" << std::endl;
			break;
			
		}

		};
	
};


void artem::RobotControl::CubeTracking(cv::Mat & frame,  std::vector<cv::Vec3d> rvecs,  std::vector<cv::Vec3d>& tvecs)
{
	
	_Cube.getMarkersPoseEstimation(frame, _Cube.getMarkerLength(), _Calib.getCameraMatrix(), _Calib.getDistCoeffs(), _MarkerIds, rvecs, tvecs, true);
	updateRobotCoordinates(frame, _MarkerIds, rvecs, tvecs);
	//cv::waitKey(200); //Debug!
	for (int i = 0; i < _MarkerIds.size(); ++i)
	{
		_CubeRotationCoordinates[_MarkerIds[i]] = rvecs[i];
		_CubeTranslationCoordinates[_MarkerIds[i]] = tvecs[i];		
	}
	

}

void artem::RobotControl::getRobotCoordinates()//todo
{
	{
		_RobotTranslationCoordinates = cv::Vec3d(0, 0, 0); 
		_RobotRotationCoordinates = cv::Vec3d(0, 0, 0);

	};
}


void artem::RobotControl::updateRobotCoordinates(cv::Mat &frame, const std::vector<int>& markerids,const std::vector<cv::Vec3d> &rvecs, const std::vector<cv::Vec3d>& tvecs)
{
	bool surfaceFinded=false;
	for (int i = 0; i<markerids.size(); ++i)
	{		
		if (markerids[i] == _mainSurface)
		{
			
			cv::Mat rvecMat;
			cv::Vec3d rvecUpd;		

			cv::Rodrigues(rvecs[i], rvecMat);
			rvecMat =  rvecMat*_RotCoeff;
			cv::Rodrigues(rvecMat,rvecUpd);					
			
			_RobotTranslationCoordinates += (tvecs[i] - _CubeTranslationCoordinates[markerids[i]]); 
			_RobotRotationCoordinates += (rvecUpd-_RobotRotationCoordinates);
			surfaceFinded = true;		
			
			//-------------------debug main Coordinate system-----------------------------------------------
			cv::namedWindow("CS", CV_WINDOW_AUTOSIZE);
			cv::Mat CoordinateFrame=cv::Mat::zeros(500,500,CV_32F);
			std::vector< cv::Point3f > axisPoints;
			axisPoints.push_back(cv::Point3f(0, 0, 0));
			axisPoints.push_back(cv::Point3f(0.02, 0, 0));
			axisPoints.push_back(cv::Point3f(0, 0.06, 0));
			axisPoints.push_back(cv::Point3f(0, 0, 0.1));
			std::vector< cv::Point2f > imagePoints;
			projectPoints(axisPoints, _RobotRotationCoordinates,cv::Vec3d(0.0,0.006,0.2), _Calib.getCameraMatrix(), _Calib.getDistCoeffs(), imagePoints);

			// draw axis lines
			line(CoordinateFrame, imagePoints[0], imagePoints[1], cv::Scalar(255, 0, 0), 3);
			line(CoordinateFrame, imagePoints[0], imagePoints[2], cv::Scalar(255, 0, 0), 3);
			line(CoordinateFrame, imagePoints[0], imagePoints[3], cv::Scalar(255, 0, 0), 3);
			cv::imshow("CS", CoordinateFrame);
			cv::waitKey(1);
			break;
		}
		
	};
	if (!surfaceFinded)
	{
		mainSurfacelost();
	}


	//Debug
	cv::Mat tmp;
	cv::Rodrigues(_RobotRotationCoordinates, tmp);
	cv::Vec3f euler = rotationMatrixToEulerAngles(tmp);
	cv::putText(frame, "Rot: " + std::to_string(euler[0] * 180.0 / CV_PI+180) + " " + std::to_string(euler[1] * 180.0 / CV_PI) + " " + std::to_string(euler[2] * 180.0 / CV_PI), cv::Point2i(10, 20),cv::FONT_HERSHEY_TRIPLEX, 0.4, (0, 0, 0));
	cv::putText(frame, "Tr: " + std::to_string(_RobotTranslationCoordinates[0]) + " " + std::to_string(_RobotTranslationCoordinates[1]) + " " + std::to_string(_RobotTranslationCoordinates[2]), cv::Point2i(10, 50), cv::FONT_HERSHEY_TRIPLEX, 0.4, (0, 0, 0));
	cv::putText(frame, "Norm: " + std::to_string(sqrt(_RobotTranslationCoordinates[0] * _RobotTranslationCoordinates[0] + _RobotTranslationCoordinates[1] * _RobotTranslationCoordinates[1] + _RobotTranslationCoordinates[2] * _RobotTranslationCoordinates[2])), cv::Point2i(10, 80), cv::FONT_HERSHEY_TRIPLEX, 0.4, (0, 0, 0));

	
}

