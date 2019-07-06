/*
Name - Erik W. Failing
Username - efailing
Assignment 1
*/

#include "pch.h"
#include "DateType.h"


void DateType::Initialize (int newMonth, int newDay, int newYear)
{
	year = newYear;
	month = newMonth;
	day = newDay;
}

//GETTERS
int DateType::GetMonth() const
{
	return month;
}
int DateType::GetYear() const
{
	return year;
}
int DateType::GetDay() const
{
	return day;
}
