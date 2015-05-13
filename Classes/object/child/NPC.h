#pragma once
#include "paddle.h"

class NPC:public Paddle
{
	static std::vector<NPC*> g_array;
public:
	NPC(void);
	~NPC(void);

	CREATE_WITHCONTENSIZE(NPC);

	void enter();
};

