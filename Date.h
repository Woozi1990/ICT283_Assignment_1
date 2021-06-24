#ifndef DATE_H
#define DATE_H
#include <string>
#include <iostream>
#include <ATLComTime.h>

using namespace std;

class Date
{
private:
    unsigned m_month;           //Month
    unsigned int m_day;         //Day
    int m_year;                 //Year
    
public:
    //Constructor
    Date();

    //Destructor
    virtual ~Date();

    
    //Set month
    void SetMonth(unsigned month);

    //Set day
    void SetDay(unsigned int day);

    //Set year
    void SetYear(int year);

    //Get day
    unsigned GetDay() const;

    //Get year
    int GetYear() const;

    //Get month
    unsigned GetMonth() const;

    bool isValid() const;

protected:


};
istream& operator >>(istream& input, Date& D);
ostream& operator <<(ostream& os, const Date& D);
#endif // DATE_H
