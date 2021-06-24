#include "Time.h"

Time::Time()
{
	m_minute = 0;
	m_hour = 0;
}

Time::~Time()
{

}

unsigned Time::GetMinute()
{
	return m_minute;
}

void Time::SetMinute(unsigned min)
{
	m_minute = min;
}

unsigned Time::GetHour()
{
	return m_hour;
}

void Time::SetHour(unsigned hour)
{
	m_hour = hour;
}

bool Time::isValid()
{
	bool isValid = false;

	if (0 <= m_hour && m_hour < 24)
		if (0 <= m_minute && m_minute < 60)
			isValid = true;

	return isValid;
}
