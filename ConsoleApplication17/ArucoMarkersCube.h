/**
* \file
* \brief Header file describes aruco markers for cube  and finding its coordinates
*/
#ifndef  ARUCOMARKERSCUBE_H
#define ARUCOMARKERSCUBE_H


#include"aruco.h"
#include<opencv2\core.hpp>
#include<opencv2\highgui.hpp>


namespace artem 
{
	/**
	* \brief class include aruco dictionary with method for its generate and pose estimation
	*/
	class ArucoMarkersCube
	{
	protected:
		/// dictionary with markers desribing the cube
		cv::Ptr<cv::aruco::Dictionary> _MarkersDict;
		double _cubeMarkersLength=0.05;
		public:
		/**
		* \brief  search markers and estimate their position
		* \param[in] frame frame to finding markers
		* \param[in] markerCorners corners vector of detected markers
		* \param[in] markerIds vector if IDs detected markers
		* \param[in] markerlength the length of the markers side, in meters(as normally)
		* \param[in] cameraMatrix Intristic camera parameters
		* \param[in] distCoeffs Camera distortion coefficients
		* \param[out] rvecs rotation vectors of markers
		* \param[out] tvecs translation vectors of markers
		* \param[in] drawMarkers draw borders and axis
		*/
		void getMarkersPoseEstimation(cv::Mat &frame, 
			//std::vector<std::vector<cv::Point2f>> markerCorners, 
			 
			const double markerLength, 
			const cv::Mat cameraMatrix, const cv::Mat distcoeffs, std::vector<int> &markerIds, std::vector<cv::Vec3d> &rvecs,
			std::vector<cv::Vec3d> &tvecs,const bool drawMarkers=false);
	
		ArucoMarkersCube() = default;
		/**
		* \brief  generate custom dictionary based on predefined
		* \param[in] numMarkers number of elements in dictionary
		* \param[in] markersSize size of element
		* \param[in] baseDict predefined dictionary
		* \param[in] sidePixels marker resolution in pixels
		* \param[in] border  width of marker border
		*/
		void generateDict(const int numMarkers, const int markersSize,  const cv::Ptr<cv::aruco::Dictionary> &baseDict, const int sidePixels=200, const int border=1 );
		/**
		* \brief  generate custom dictionary 
		* \param[in] numMarkers number of elements in dictionary
		* \param[in] markersSize size of element
		* \param[in] sidePixels marker resolution in pixels
		* \param[in] border  width of marker border
		*/
		void generateDict(const int numMarkers, const int markersSize, const int sidePixels=200, const int border=1);
		/**
		* \brief  save markers from dictionary in folder Markers
		* \param[in] sidePixels marker resolution in pixels
		* \param[in] border  width of marker border
		* \param[in] baseDict sourcedictionary
		*/
		void saveMarkersFromDict(const int sidePixels, const int border, const cv::Ptr<cv::aruco::Dictionary> &baseDict);

		virtual ~ArucoMarkersCube() = default;
		double getMarkerLength()const;
		void setMarkerLength(const double L);
	};

}
#endif

