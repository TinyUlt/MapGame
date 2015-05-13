#include "ChairPart.h"

std::vector<ChairPart*> ChairPart::g_array;

ChairPart::ChairPart(void)
{
}

ChairPart::~ChairPart(void)
{
}

void ChairPart::enter()
{
	g_array.push_back(this);
	m_type = CHAIRPART_TYPE;
}