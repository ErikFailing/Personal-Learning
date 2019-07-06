/*
Name - Erik W. Failing
Username - efailing
Assignment 2
*/

#include "pch.h"
#include "DateType.h"


void DateType::Initialize (int newMonth, int newDay, int newYear)
{
	year = newYear;
	month = newMonth;
	day = newDay;
}

RelationType DateType::comparedTo(DateType aDate) const
{
	if (year < aDate.year) return LESS;
	else if (year > aDate.year) return GREATER;
	else if (month < aDate.month) return LESS;
	else if (month > aDate.month) return GREATER;
	else if (day < aDate.day) return LESS;
	else if (day > aDate.day) return GREATER;
	else return EQUAL;
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
