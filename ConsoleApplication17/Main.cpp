#include"ICalib.h"
int main()
{
	int CameraNum = 0;
	Artem::ICalib C;
	if (!C.GetCalibrationData_Chess(CameraNum))
		return 1;
	C.Calibrate();
	C.ShowUndistorted(CameraNum);
	return 0;
}