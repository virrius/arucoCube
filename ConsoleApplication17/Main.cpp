#include"ICalib.h"
int main()
{
	ICalib C;
	C.GetCalibrationData_Chess();
	C.Calibrate();
	C.ShowUndistorted();
	return 0;
}