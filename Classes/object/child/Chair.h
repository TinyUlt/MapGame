#pragma once
#include "paddle.h"
class ChairPart;
class Chair:public Paddle
{
public:
	static std::vector<Chair*> g_array;
	Chair(void);
	~Chair(void);
	CREATE_WITHCONTENSIZE(Chair);

	void enter();

	ChairPart* m_chairPart;
	int m_chairLocation;
};

