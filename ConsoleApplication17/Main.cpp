#include"ICalib.h"
int main()
{
	int CameraNum = 1;
	ICalib C;
	if (!C.GetCalibrationData_Chess(CameraNum))
		return 1;
	C.Calibrate();
	C.ShowUndistorted(CameraNum);
	return 0;
}