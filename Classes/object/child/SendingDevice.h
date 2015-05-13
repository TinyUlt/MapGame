#pragma once
#include "paddle.h"
class SendingDevice:public Paddle
{
public:
	static std::vector<SendingDevice*> g_array;

	SendingDevice(void);
	~SendingDevice(void);
	CREATE_WITHCONTENSIZE(SendingDevice);
	void enter();

	CCPoint m_target;
	std::string m_targetName;
};

