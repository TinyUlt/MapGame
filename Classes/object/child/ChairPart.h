#pragma once
#include "paddle.h"
class ChairPart:public Paddle
{
public:
	static std::vector<ChairPart*> g_array;

	ChairPart(void);
	~ChairPart(void);

	CREATE_WITHCONTENSIZE(ChairPart);
	void enter();
};

