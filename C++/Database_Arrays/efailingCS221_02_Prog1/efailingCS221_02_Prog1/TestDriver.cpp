/*
Name - Erik W. Failing
Username - efailing
Assignment 1
*/

#include "pch.h"
#include "TestDriver.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <fstream>
#include <math.h>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <vector>
#include "DateType.h""

using namespace std;

//Constructor
TestDriver::TestDriver()
{
}


//Read in from file
int TestDriver::Populate(const char* input, User users[]) 
{
	ifstream inFile;
	DateType dateOfBirth;
	vector<string> tempStorage;
	char tempCharArr[30];
	char tempChar = 0;
	int count = 0;

	string month;
	string day;
	string year;

	char streetName[30];
	int streetNo = 0;
	char city[30];
	int zip = 0;
	char state[3];

	inFile.open(input);
	if (!inFile)
	{
		cout << "Can't find file." << endl;
		return 0;
	}

	//Get all data from file into a vector of strings
	string line;
	while (getline(inFile, line))
	{
		tempStorage.push_back(line);
	}

	inFile.close();

	//Take all raw data and create a variable number of users from it
	while (count < (int) ((tempStorage.size() + 1) / 13))
	{
		int j = count * 13;
		//Take raw data and create a user from it
		for (int i = 0; i < 12; i += 1)
		{
			if (tempStorage[i + j].find("FirstName: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 11);
				//Convert to proper type
				strcpy_s(tempCharArr, tempStorage[i + j].c_str());
				//Assign to new user
				users[count].SetFirstName(tempCharArr);
			}
			if (tempStorage[i + j].find("LastName: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 10);
				//Convert to proper type
				strcpy_s(tempCharArr, tempStorage[i + j].c_str());
				//Assign to new user
				users[count].SetLastName(tempCharArr);
			}
			if (tempStorage[i + j].find("Major: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 7);
				//Convert to proper type
				strcpy_s(tempCharArr, tempStorage[i + j].c_str());
				//Assign to new user
				users[count].SetMajor(tempCharArr);
			}
			if (tempStorage[i + j].find("Gender: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 8);
				//Assign to new user
				users[count].SetGender(tempStorage[i + j][0]);
			}
			if (tempStorage[i + j].find("Email: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 7);
				//Convert to proper type
				strcpy_s(tempCharArr, tempStorage[i + j].c_str());
				//Assign to new user
				users[count].SetEmail(tempCharArr);
			}
			if (tempStorage[i + j].find("BirthDate: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 11);
				//Get month
				month = tempStorage[i + j].substr(0, tempStorage[i + j].find(' ') + 1);
				//Delete month
				tempStorage[i + j].erase(0, tempStorage[i + j].find(' ') + 1);
				//Get day
				day = tempStorage[i + j].substr(0, tempStorage[i + j].find(' ') + 1);
				//Delete day
				tempStorage[i + j].erase(0, tempStorage[i + j].find(' ') + 1);
				//Get year
				year = tempStorage[i + j].substr(0, 4);
				//Initialize DateType
				dateOfBirth.Initialize(stoi(month), stoi(day), stoi(year));
				//Assign to new user
				users[count].SetDateOfBirth(dateOfBirth);
			}
			if (tempStorage[i + j].find("GPA: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 5);
				//Assign to new user
				users[count].SetGPA(stof(tempStorage[i + j]));
			}
			if (tempStorage[i + j].find("StreetName: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 12);
				//Assign to var
				strcpy_s(streetName, tempStorage[i + j].c_str());
			}
			if (tempStorage[i + j].find("StreetNo: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 10);
				//Assign to var
				streetNo = stoi(tempStorage[i + j]);
			}
			if (tempStorage[i + j].find("City: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 6);
				//Assign to var
				strcpy_s(city, tempStorage[i + j].c_str());
			}
			if (tempStorage[i + j].find("Zip: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 5);
				//Assign to var
				zip = stoi(tempStorage[i + j]);
			}
			if (tempStorage[i + j].find("State: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 7);
				//Assign to var
				strcpy_s(state, tempStorage[i + j].c_str());
			}
			//Set address
			users[count].SetAddress(streetName, streetNo, city, zip, state);
		}
		count += 1;
	}

	return count;
}



//Testers
void TestDriver::Test(User users[], int count) const
{
	//Print ID
	cout << "Name: Erik Failing" << endl;
	cout << "Username: efailing" << endl;
	cout << "Assignment 1" << endl << endl;

	//Print out users to console
	cout << "PRINTING USERS OUT: " << endl << endl;
	for (int i = 0; i < count; i += 1)
	{
		users[i].Display();
	}

	//Test unused methods
	cout << endl << endl << "TESTING UNUSED METHODS: " << endl << endl;
	cout << users[count - 1].GetGPA() << endl << endl;

	cout << "BirthDate: " << users[count -1].GetDateOfBirth().GetMonth() << " " 
		<< users[count - 1].GetDateOfBirth().GetDay() << " " << users[count - 1].GetDateOfBirth().GetYear() << endl << endl;

	users[count - 1].SetAddress(users[count - 2].GetAddress());
	cout << "StreetName: " << users[count - 1].GetAddress().streetName << endl;
	cout << "StreetNo: " << users[count - 1].GetAddress().streetNo << endl;
	cout << "City: " << users[count - 1].GetAddress().city << endl;
	cout << "Zip: " << users[count - 1].GetAddress().zip << endl;
	cout << "State: " << users[count - 1].GetAddress().state << endl;



}
void TestDriver::Test(std::ofstream& outFile, User  users[], int count) const
{
	//Print ID
	outFile << "Name: Erik Failing" << endl;
	outFile << "Username: efailing" << endl;
	outFile << "Assignment 1" << endl << endl;

	//Print out users to console
	for (int i = 0; i < count; i += 1)
	{
		users[i].Display(outFile);
	}

	//Test untested methods
	outFile << endl << endl << "TESTING UNUSED METHODS: " << endl << endl;
	outFile << users[count - 1].GetGPA() << endl << endl;

	outFile << "BirthDate: " << users[count - 1].GetDateOfBirth().GetMonth() << " "
		<< users[count - 1].GetDateOfBirth().GetDay() << " " << users[count - 1].GetDateOfBirth().GetYear() << endl << endl;

	users[count - 1].SetAddress(users[count - 2].GetAddress());
	outFile << "StreetName: " << users[count - 1].GetAddress().streetName << endl;
	outFile << "StreetNo: " << users[count - 1].GetAddress().streetNo << endl;
	outFile << "City: " << users[count - 1].GetAddress().city << endl;
	outFile << "Zip: " << users[count - 1].GetAddress().zip << endl;
	outFile << "State: " << users[count - 1].GetAddress().state << endl;
}


//Deconstructor
TestDriver::~TestDriver()
{
}