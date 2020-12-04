#include "Fanuc.h"
#include <iostream>
#include <sstream>
#include <Ws2tcpip.h>

FanucM20iA::FanucM20iA(const double xMin, const double yMin, const double zMin,
	const double xMax, const double yMax, const double zMax)
	: _portS(59002),
	_portR(59003),
	_tmpAddrString("172.27.221.60"),
	_wsaData(),
	_workInJoint(false),
	_maxValueOf(xMax, yMax, zMax),
	_minValueOf(xMin, yMin, zMin)
{
	initSockets();
}

const int FanucM20iA::buffLength = 64;

const std::map<int, std::string> FanucM20iA::tableOfErrors = 
{
	{ 6, "Specified event object handle is invalid." },
	{ 8, "Insufficient memory available." },
	{ 87, "One or more parameters are invalid." },
	{ 995, "Overlapped operation aborted." },
	{ 996, "Overlapped I/O event object not in signaled state." },
	{ 997, "Overlapped operations will complete later." },
	{ 10004, "Interrupted function call." },
	{ 10009, "File handle is not valid." },
	{ 10013, "Permission denied." },
	{ 10014, "Bad address" },
	{ 10022, "Invalid argument." },
	{ 10024, "Too many open files." },
	{ 10035, "Resource temporarily unavailable." },
	{ 10036, "Operation now in progress." },
	{ 10037, "Operation already in progress." },
	{ 10038, "Socket operation on nonsocket." },
	{ 10039, "Destination address required." },
	{ 10040, "Message too long." },
	{ 10041, "Protocol wrong type for socket." },
	{ 10042, "Bad protocol option." },
	{ 10043, "Protocol not supported." },
	{ 10044, "Socket type not supported." },
	{ 10045, "Operation not supported." },
	{ 10046, "Protocol family not supported." },
	{ 10047, "Address family not supported by protocol family." },
	{ 10048, "Address already in use." },
	{ 10049, "Cannot assign requested address." },
	{ 10050, "Network is down." },
	{ 10051, "Network is unreachable." },
	{ 10052, "Network dropped connection on reset." },
	{ 10053, "Software caused connection abort." },
	{ 10054, "Connection reset by peer." },
	{ 10055, "No buffer space available." },
	{ 10056, "Socket is already connected." },
	{ 10057, "Socket is not connected." },
	{ 10058, "Cannot send after socket shutdown." },
	{ 10059, "Too many references." },
	{ 10060, "Connection timed out." },
	{ 10061, "Connection refused." },
	{ 10062, "Cannot translate name." },
	{ 10063, "Name too long." },
	{ 10064, "Host is down." },
	{ 10065, "No route to host." },
	{ 10066, "Directory not empty." },
	{ 10067, "Too many processes." },
	{ 10068, "User quota exceeded." },
	{ 10069, "Disk quota exceeded." },
	{ 10070, "Stale file handle reference." },
	{ 10071, "Item is remote." },
	{ 10091, "Network subsystem is unavailable." },
	{ 10092, "Winsock.dll version out of range." },
	{ 10093, "Successful WSAStartup not yet performed." },
	{ 10101, "Graceful shutdown in progress." },
	{ 10102, "No more results." },
	{ 100000, "Some another error occured..." }
};

void FanucM20iA::initSockets()
{
	try
	{
		if (WSAStartup(MAKEWORD(2, 2), &_wsaData) != 0)
		{
			throw WSAGetLastError();
		}

		if ((_sockSend = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
		{
			throw WSAGetLastError();
		}
		if ((_sockReceive = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
		{
			throw WSAGetLastError();
		}
	}
	catch (int e)
	{
		socketErrorOnScreen(e);
		system("pause");
		exit(-1);
	}
}

void FanucM20iA::startWorking() const
{
	try
	{
		const char* serveraddr = _tmpAddrString.c_str();

		sockaddr_in destAddr;
		destAddr.sin_family = AF_INET;
		destAddr.sin_port = htons(_portS);
		//destAddr.sin_addr.s_addr = inet_addr(serveraddr);
		inet_pton(AF_INET, serveraddr, &destAddr.sin_addr);
		if (connect(_sockSend, reinterpret_cast<sockaddr*>(&destAddr), sizeof(destAddr)) == SOCKET_ERROR)
		{
			throw WSAGetLastError();
		}

		sockaddr_in recvAddr;
		recvAddr.sin_family = AF_INET;
		recvAddr.sin_port = htons(_portR);
		//recvAddr.sin_addr.s_addr = inet_addr(serveraddr);
		inet_pton(AF_INET, serveraddr, &recvAddr.sin_addr);
		if (connect(_sockReceive, reinterpret_cast<sockaddr*>(&recvAddr), sizeof(recvAddr)) == SOCKET_ERROR)
		{
			throw WSAGetLastError();
		}
	}
	catch (int e)
	{
		socketErrorOnScreen(e);
		system("pause");
		exit(-2);
	}
}

std::array<double, 6> FanucM20iA::parseString(char* str)
{
	std::array<double, 6> tmp;
	int k = 1;
	for (auto& coord : tmp)
	{
		char sum[7] = "";
		int j = 0;
		while (str[k] != ' ' && str[k] != '\n')
		{
			sum[j] = str[k];
			++j;
			++k;
		}

		coord = atof(sum) / 1000;

		++k;
	}
	return tmp;
}

const char* FanucM20iA::createStringToSend(const double& xToRobot, const double& yToRobot, const double& zToRobot,
										   const double& wToRobot, const double& pToRobot, const double& rToRobot)
{
	std::ostringstream tmpBuf;
	tmpBuf << static_cast<int>(xToRobot * 1000.) << ' ' << static_cast<int>(yToRobot * 1000.) << ' '
		<< static_cast<int>(zToRobot * 1000.) << ' ' << static_cast<int>(wToRobot * 1000.) << ' '
		<< static_cast<int>(pToRobot * 1000.) << ' ' << static_cast<int>(rToRobot * 1000.) << " 10 2 0";
	return _strdup(tmpBuf.str().c_str());
}

const char* FanucM20iA::createStringToSend(const double& xToRobot, const double& yToRobot, const double& zToRobot,
										   const double& wToRobot, const double& pToRobot, const double& rToRobot,
										   const int& seg)
{
	std::ostringstream tmpBuf;
	tmpBuf << static_cast<int>(xToRobot * 1000.) << ' ' << static_cast<int>(yToRobot * 1000.) << ' '
		<< static_cast<int>(zToRobot * 1000.) << ' ' << static_cast<int>(wToRobot * 1000.) << ' '
		<< static_cast<int>(pToRobot * 1000.) << ' ' << static_cast<int>(rToRobot * 1000.) << ' ' << seg << " 2 0";
	return _strdup(tmpBuf.str().c_str());
}

const char* FanucM20iA::createStringToSend(const double& xToRobot, const double& yToRobot, const double& zToRobot,
										   const double& wToRobot, const double& pToRobot, const double& rToRobot,
										   const int& seg, const int& type)
{
	std::ostringstream tmpBuf;
	tmpBuf << static_cast<int>(xToRobot * 1000.) << ' ' << static_cast<int>(yToRobot * 1000.) << ' '
		<< static_cast<int>(zToRobot * 1000.) << ' ' << static_cast<int>(wToRobot * 1000.) << ' '
		<< static_cast<int>(pToRobot * 1000.) << ' ' << static_cast<int>(rToRobot * 1000.) << ' ' << seg << ' ' << type <<
		" 0";
	return _strdup(tmpBuf.str().c_str());
}

void FanucM20iA::socketErrorOnScreen(int& e)
{
	auto tmpIter = tableOfErrors.find(e);
	if (tmpIter == tableOfErrors.end())
	{
		tmpIter = std::prev(tableOfErrors.end());
	}
	std::cout << "Error " << tmpIter->first << ":\t" << tmpIter->second << std::endl;
}

void FanucM20iA::checkCoordsLimits(const double& x, const double& y, const double& z) const
{
	if (!_workInJoint)
	{
		try
		{
			if (x > _maxValueOf._x) throw "Exceeding the maximum limits along the X axis";
			if (x < _minValueOf._x) throw "Exceeding the minimum limits along the X axis";

			if (y > _maxValueOf._y) throw "Exceeding the maximum limits along the Y axis";
			if (y < _minValueOf._y) throw "Exceeding the minimum limits along the Y axis";

			if (z > _maxValueOf._z) throw "Exceeding the maximum limits along the Z axis";
			if (z < _minValueOf._z) throw "Exceeding the minimum limits along the Z axis";
		}
		catch (char* msg)
		{
			std::cout << msg << std::endl;
			system("pause");
			exit(-9);
		}
	}
}

void FanucM20iA::setWorldFrame()
{
	try
	{
		_workInJoint = false;
		const char* c = "2";
		if (send(_sockSend, c, static_cast<int>(strlen(c)), 0) == SOCKET_ERROR)
		{
			throw WSAGetLastError();
		}
	}
	catch (int e)
	{
		socketErrorOnScreen(e);
		system("pause");
		exit(-3);
	}
}

void FanucM20iA::setJointFrame()
{
	try
	{
		_workInJoint = true;
		const char* c = "0";
		if (send(_sockSend, c, static_cast<int>(strlen(c)), 0) == SOCKET_ERROR)
		{
			throw WSAGetLastError();
		}
	}
	catch (int e)
	{
		socketErrorOnScreen(e);
		system("pause");
		exit(-4);
	}
}

void FanucM20iA::goToCoordinates(const double& x, const double& y, const double& z, const double& w, const double& p,
								 const double& r) const
{
	try
	{
		checkCoordsLimits(x, y, z);
		const char* str = createStringToSend(x, y, z, w, p, r);
		if (send(_sockSend, str, static_cast<int>(strlen(str)), 0) == SOCKET_ERROR)
		{
			throw WSAGetLastError();
		}
	}
	catch (int e)
	{
		socketErrorOnScreen(e);
		system("pause");
		exit(-5);
	}
}

void FanucM20iA::goToCoordinates(const double& x, const double& y, const double& z, const double& w, const double& p,
								 const double& r, const int& seg) const
{
	try
	{
		checkCoordsLimits(x, y, z);
		const char* str = createStringToSend(x, y, z, w, p, r, seg);
		if (send(_sockSend, str, static_cast<int>(strlen(str)), 0) == SOCKET_ERROR)
		{
			throw WSAGetLastError();
		}
	}
	catch (int e)
	{
		socketErrorOnScreen(e);
		system("pause");
		exit(-6);
	}
}

void FanucM20iA::goToCoordinates(const double& x, const double& y, const double& z, const double& w, const double& p,
								 const double& r, const int& seg, const int& type) const
{
	try
	{
		checkCoordsLimits(x, y, z);
		const char* str = createStringToSend(x, y, z, w, p, r, seg, type);
		if (send(_sockSend, str, static_cast<int>(strlen(str)), 0) == SOCKET_ERROR)
		{
			throw WSAGetLastError();
		}
	}
	catch (int e)
	{
		socketErrorOnScreen(e);
		system("pause");
		exit(-7);
	}
}


std::array<double, 6> FanucM20iA::getJointAngles() const
{
	char buff[buffLength];
	try
	{
		const int valRead = recv(_sockReceive, buff, buffLength, 0);
		if (valRead == SOCKET_ERROR && valRead == 0)
		{
			throw WSAGetLastError();
		}

		buff[valRead] = '\0';
	}
	catch (int e)
	{
		socketErrorOnScreen(e);
		system("pause");
		exit(-8);
	}
	std::cout << buff << std::endl;
	return parseString(buff);
}

FanucM20iA::~FanucM20iA()
{
	if (_workInJoint)
	{
		goToCoordinates(0., 0., 0., 90., 0., 0.);
		getJointAngles();
	}
	else
	{
		goToCoordinates(985., 0., 940., 180., 0., 0.);
		getJointAngles();
	}
	closesocket(_sockSend);
	closesocket(_sockReceive);
	WSACleanup();
}

FanucM20iA::ExtremeValuesMax::ExtremeValuesMax(const double& x, const double& y, const double& z)
	: _x(x),
	_y(y),
	_z(z)
{
}

FanucM20iA::ExtremeValuesMin::ExtremeValuesMin(const double& x, const double& y, const double& z)
	: _x(x),
	_y(y),
	_z(z)
{
}