#ifndef TIME_H
#define TIME_H



class Time
{
private:
	unsigned m_minute;  //Minute
	unsigned m_hour;    //Hour


public:
	//Constructor
	Time();
	//Destructor
	~Time();
	//Get minute
	unsigned GetMinute();
	//Set minute
	void SetMinute(unsigned min);
	//Get hour
	unsigned GetHour();
	//Set hour
	void SetHour(unsigned hour);

	bool isValid();

};



#endif // TIME_H
