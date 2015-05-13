#include "SendingDevice.h"

std::vector<SendingDevice*> SendingDevice::g_array;


SendingDevice::SendingDevice(void)
{
}


SendingDevice::~SendingDevice(void)
{
}

void SendingDevice::enter()
{
	g_array.push_back(this);
	m_type = SEND_TYPE;
}

