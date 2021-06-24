// Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include "Vector.h"
#include "Date.h"
#include "Time.h"

using namespace std;

struct Record {
	Date date;
	Time time;
	unsigned speed = 0;
	unsigned solarRatiation = 0;
	float temperature = 0;
};

Vector<Record>* g_record = new Vector<Record>();
string g_monthCharacter[12] = { "January","February","March","April","May","June","July","August","September","October","November","December" };

void PrintMenu();
int InputCheck(int fIndex, int lIndex, string msg);
void LoadFile();
void SaveFile();
void CalAveWindSpeed(unsigned year, unsigned mon, float& speed);
void CalAveTemperature(unsigned year, unsigned mon, float& temperature);
void CalTotalSolarRadiation(unsigned year, unsigned mon, unsigned& total);



void SpeedTempForASpecifiedMonth();
void SpeedTempForAYear();
void TotalSolarRadiationForAYear();
void DisplayAllData();


int main()
{
	LoadFile();


	while (true)
	{
		PrintMenu();
		cout << "Enter your choice: " << endl;

		string errMsg = "Invalid choice, please enter again.";
		int choice = InputCheck(1, 5, errMsg);
		switch (choice)
		{
		case 1:
			SpeedTempForASpecifiedMonth();
			break;
		case 2:
			SpeedTempForAYear();
			break;
		case 3:
			TotalSolarRadiationForAYear();
			break;
		case 4:
			DisplayAllData();
			break;
		case 5:
			cout << "The program is terminated..." << endl;
			return 0;
		}
	}
}

void PrintMenu()
{
	cout << endl;
	cout << "1. Display average wind speed and average ambient air temperature for a specified month and year." << endl;
	cout << "2. Display average wind speed and average ambient air temperature for each month of a specified year." << endl;
	cout << "3. Display total solar radiation in kWh/m2 for each month of a specified year." << endl;
	cout << "4. Display average wind speed, average ambient air temperature and total solar radiation for each month of a specified year." << endl;
	cout << "5. Exit program." << endl;
	cout << endl;

}

int InputCheck(int fIndex, int lIndex, string msg)
{
	int choice = 0;


	while (!(cin >> choice) || choice<fIndex || choice>lIndex)
	{
		cin.clear();
		while (cin.get() != '\n')
		{
			continue;
		}
		cout << msg << endl;
	}

	return choice;
}

void LoadFile()
{

	string file = "data\\MetData-31-3a.csv";
	string fileAll = "data\\MetData_Mar01-2015-Mar01-2016-ALL.csv";

	ifstream infile(fileAll, ios::in);
	if (!infile)
	{
		cout << "Can not open file " << file << endl;
		return;
	}

	string data;
	getline(infile, data, '\n');
	while (!infile.eof())
	{
		data = "";
		getline(infile, data, ',');

		if (!data.find("\n"))
			break;

		unsigned day, mon, year, hour, min;

		Date date;
		Time time;

		unsigned speed, radiation;
		float temperature;

		day = stoi(data.substr(0, data.find("/")));
		mon = stoi(data.substr(data.find("/") + 1, 2));
		year = stoi(data.substr(data.find("/") + 4, 4));

		hour = stoi(data.substr(data.find(" ") + 1, 2));
		min = stoi(data.substr(data.find(":") + 1));

		date.SetDay(day);
		date.SetMonth(mon);
		date.SetYear(year);
		if (!date.isValid())
		{
			getline(infile, data, '\n');
			continue;
		}

		time.SetHour(hour);
		time.SetMinute(min);
		if (!time.isValid())
		{
			getline(infile, data, '\n');
			continue;
		}

		for (int i = 0; i < 10; i++)
		{
			getline(infile, data, ',');
		}
		speed = stoi(data);
		getline(infile, data, ',');
		radiation = stoi(data);
		radiation < 100 ? 0 : radiation;

		for (int i = 0; i < 5; i++)
		{
			getline(infile, data, ',');
		}
		getline(infile, data, '\n');
		temperature = stof(data);

		Record record;
		record.date = date;
		record.time = time;
		record.speed = speed;
		record.solarRatiation = radiation;
		record.temperature = temperature;

		g_record->Add(record);

	}

	cout << g_record->Size() << " data have been loaded from " << file << "." << endl;

}

void SaveFile()
{

}

void CalAveWindSpeed(unsigned year, unsigned mon, float& speed)
{
	//convert unit m/s -> km/h
	float sum = 0;
	unsigned counter = 0;
	for (unsigned i = 0; i < g_record->Size(); i++)
	{
		if (g_record->At(i).date.GetYear() == year)
		{
			if (g_record->At(i).date.GetMonth() == mon)
			{
				counter++;
				sum += g_record->At(i).speed;
			}
		}
	}
	speed = sum == 0 ? -1 : sum / counter * 3.6f;	//use -1 as a flag to show "no data", because sum of wind speed will not be negetive.

	//cout << "S: " << sum << " " << counter << endl;

}

void CalAveTemperature(unsigned year, unsigned mon, float& temperature)
{
	//convert unit m/s -> km/h
	float sum = 0;
	unsigned counter = 0;
	for (unsigned i = 0; i < g_record->Size(); i++)
	{
		if (g_record->At(i).date.GetYear() == year)
		{
			if (g_record->At(i).date.GetMonth() == mon)
			{
				counter++;
				sum += g_record->At(i).temperature;
			}
		}
	}

	temperature = sum / counter;
	//cout << "T: " << sum << " " << counter << endl;

}

void CalTotalSolarRadiation(unsigned year, unsigned mon, unsigned &total)
{
	unsigned sum = 0;
	for (unsigned i = 0; i < g_record->Size(); i++)
	{
		if (g_record->At(i).date.GetYear() == year)
		{
			if (g_record->At(i).date.GetMonth() == mon)
			{
				sum += g_record->At(i).solarRatiation;
			}
		}
	}

	total = sum == 0 ? -1 : sum;
}

void SpeedTempForASpecifiedMonth()
{
	unsigned mon, year;
	string errMsg = "Please enter a valid data.";
	bool isFound = false;

	float aveSpeed = 0, aveTemp = 0;

	cout << "Enter a month" << endl;
	mon = InputCheck(1, 12, errMsg);
	cout << "Enter a year" << endl;
	year = InputCheck(0, 2022, errMsg);


	for (unsigned i = 0; i < g_record->Size(); i++)
	{
		if (year == g_record->At(i).date.GetYear())
		{
			if (mon == g_record->At(i).date.GetMonth())
			{
				isFound = true;
			}
		}
	}
	cout << endl;
	if (isFound)
	{
		CalAveWindSpeed(year, mon, aveSpeed);
		CalAveTemperature(year, mon, aveTemp);

		cout << g_monthCharacter[mon - 1] << " " << year << ": ";
		cout << aveSpeed << " km/h, " << aveTemp << " degrees C" << endl;
	}
	else
	{
		cout << g_monthCharacter[mon - 1] << " " << year << ": No Data" << endl;
	}

}

void SpeedTempForAYear()
{
	unsigned  year;
	string errMsg = "Please enter a valid year.";

	float aveSpeed = 0, aveTemp = 0;

	cout << "Enter a year" << endl;
	year = InputCheck(0, 2022, errMsg);

	cout <<endl<< year << endl;
	for (unsigned i = 0; i < 12; i++)
	{
		CalAveWindSpeed(year, i + 1, aveSpeed);
		CalAveTemperature(year, i + 1, aveTemp);
		if (aveSpeed==-1)
		{
			cout << g_monthCharacter[i] << ": No Data" << endl;
		}
		else
		{
			cout << g_monthCharacter[i] << ": " << aveSpeed << " km/h, " << aveTemp << " degrees C" << endl;
		}
	}
}

void TotalSolarRadiationForAYear()
{
	unsigned  year;
	string errMsg = "Please enter a valid year.";

	unsigned totalRadiation = 0;

	cout << "Enter a year" << endl;
	year = InputCheck(0, 2022, errMsg);

	cout << endl << year << endl;
	for (unsigned i = 0; i < 12; i++)
	{
		CalTotalSolarRadiation(year, i+1,totalRadiation);

		if (totalRadiation == -1)
		{
			cout << g_monthCharacter[i] << ": No Data" << endl;
		}
		else
		{
			cout << g_monthCharacter[i] << ": " << totalRadiation << " kWh/m2" << endl;
		}
	}
}

void DisplayAllData()
{
	unsigned  year;
	string errMsg = "Please enter a valid year.";

	float aveSpeed = 0, aveTemp = 0;
	unsigned totalRadiation=0 ;

	cout << "Enter a year" << endl;
	year = InputCheck(0, 2022, errMsg);

	cout << endl << year << endl;
	for (unsigned i = 0; i < 12; i++)
	{
		CalAveWindSpeed(year, i + 1, aveSpeed);
		CalAveTemperature(year, i + 1, aveTemp);
		CalTotalSolarRadiation(year, i + 1, totalRadiation);
		if (aveSpeed == -1)
		{
			cout << g_monthCharacter[i] << ": No Data" << endl;
		}
		else
		{
			cout << g_monthCharacter[i] << ": " << aveSpeed << " ," << aveTemp << " ,"<<totalRadiation << endl;
		}
	}
}