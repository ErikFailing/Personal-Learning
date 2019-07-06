/*
Name - Erik W. Failing
Username - efailing
Assignment 1
*/

#pragma once
class DateType
{
public:
	void Initialize(int newMonth, int newDay, int newYear);
	int GetYear() const;    // Returns year
	int GetMonth() const;   // Returns month
	int GetDay() const;     // Returns day
private:
	int year;
	int month;
	int day;
};