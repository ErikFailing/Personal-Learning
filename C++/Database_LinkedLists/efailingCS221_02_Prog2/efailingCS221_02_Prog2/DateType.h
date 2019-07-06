/*
Name - Erik W. Failing
Username - efailing
Assignment 2
*/

enum RelationType {LESS, EQUAL, GREATER};

#pragma once
class DateType
{
public:
	void Initialize(int newMonth, int newDay, int newYear);
	RelationType comparedTo(DateType aDate) const;
	int GetYear() const;    // Returns year
	int GetMonth() const;   // Returns month
	int GetDay() const;     // Returns day
private:
	int year;
	int month;
	int day;
};