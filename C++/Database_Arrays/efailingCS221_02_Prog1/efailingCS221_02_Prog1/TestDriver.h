/*
Name - Erik W. Failing
Username - efailing
Assignment 1
*/

#pragma once
#include "User.h"

class TestDriver
{
public:
	//Constructor
	TestDriver();

	//Read in from file
	int Populate(const char* input, User users[]);

	//Testers
	void Test(User users[], int count) const;
	void Test(std::ofstream& outFile, User  users[], int count) const;

	//Destructor
	~TestDriver();
};

