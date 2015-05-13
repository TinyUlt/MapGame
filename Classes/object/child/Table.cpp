#include "Table.h"


std::vector<Table*> Table::g_array;


Table::Table(void)
{
}


Table::~Table(void)
{
}

void Table::enter()
{
	g_array.push_back(this);
	m_type = TABLE_TYPE;
}



