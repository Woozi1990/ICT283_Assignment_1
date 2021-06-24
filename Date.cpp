#include "Date.h"

Date::Date()
{
    //ctor
    m_day=0;
    m_month=0;
    m_year=0;

}

Date::~Date()
{
    //dtor
}

void Date::SetDay(unsigned day)
{
    m_day = day;
}

void Date::SetMonth(unsigned month)
{
    m_month = month;
}

void Date::SetYear(int year)
{
    m_year = year;
}

unsigned Date::GetDay() const
{
    return m_day;
}

unsigned Date::GetMonth() const
{
    return m_month;
}

int Date::GetYear() const
{
    return m_year;
}

bool Date::isValid() const
{
    COleDateTime dt;
    
    return !dt.SetDate(m_year, m_month, m_day);

}



istream & operator >>( istream & input, Date & D )
{
    string line;
    getline(input,line,',');
    getline(input,line,',');
    D.SetDay(atoi(line.c_str()));
    getline(input,line,',');
    D.SetMonth(atoi(line.c_str()));
    getline(input,line,',');
    D.SetYear(atoi(line.c_str()));

    return input;

}
ostream & operator <<( ostream & os, const Date & D )
{
    unsigned day = D.GetDay();
    unsigned month = D.GetMonth();
    unsigned year = D.GetYear();

    

    os << "\tDate: " << day << " "<< month << " "<< year<<'\n';

    return os;
}
