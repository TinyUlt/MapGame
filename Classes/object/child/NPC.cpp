#include "NPC.h"


std::vector<NPC*> NPC::g_array;

NPC::NPC(void)
{
}


NPC::~NPC(void)
{
}

void NPC::enter()
{
	g_array.push_back(this);
	m_type = NPC_TYPE;

}


