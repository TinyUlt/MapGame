#include "Chair.h"


std::vector<Chair*> Chair::g_array;

Chair::Chair(void):m_chairPart(NULL),m_chairLocation(-1)
{
}


Chair::~Chair(void)
{
}

void Chair::enter()
{
	g_array.push_back(this);
	m_type = CHAIR_TYPE;

}
