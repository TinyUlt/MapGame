#pragma once
#include "paddle.h"
class Table:public Paddle
{
public:
	static std::vector<Table*> g_array;
	Table(void);
	~Table(void);
	CREATE_WITHCONTENSIZE(Table);
	void enter();
};

