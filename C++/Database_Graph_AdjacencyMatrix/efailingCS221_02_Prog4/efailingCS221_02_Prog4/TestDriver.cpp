/*
Name - Erik W. Failing
Username - efailing
Assignment 4
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
	while (count < (int)((tempStorage.size() + 1) / 13))
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
int TestDriver::Populate(const char* input, UnsortedType& allUnsortedUsers) const
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
	while (count < (int)((tempStorage.size() + 1) / 13))
	{
		if (allUnsortedUsers.IsFull()) return count;
		User* tempUser = new User;
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
				tempUser->SetFirstName(tempCharArr);
			}
			if (tempStorage[i + j].find("LastName: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 10);
				//Convert to proper type
				strcpy_s(tempCharArr, tempStorage[i + j].c_str());
				//Assign to new user
				tempUser->SetLastName(tempCharArr);
			}
			if (tempStorage[i + j].find("Major: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 7);
				//Convert to proper type
				strcpy_s(tempCharArr, tempStorage[i + j].c_str());
				//Assign to new user
				tempUser->SetMajor(tempCharArr);
			}
			if (tempStorage[i + j].find("Gender: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 8);
				//Assign to new user
				tempUser->SetGender(tempStorage[i + j][0]);
			}
			if (tempStorage[i + j].find("Email: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 7);
				//Convert to proper type
				strcpy_s(tempCharArr, tempStorage[i + j].c_str());
				//Assign to new user
				tempUser->SetEmail(tempCharArr);
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
				tempUser->SetDateOfBirth(dateOfBirth);
			}
			if (tempStorage[i + j].find("GPA: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 5);
				//Assign to new user
				tempUser->SetGPA(stof(tempStorage[i + j]));
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
			tempUser->SetAddress(streetName, streetNo, city, zip, state);
		}
		//Add tempUser to unsorted linkedList
		allUnsortedUsers.PutUser(tempUser);
		count += 1;
	}

	return count;
}
int TestDriver::Populate(const char* input, SortedType& allSortedUsers) const
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
	while (count < (int)((tempStorage.size() + 1) / 13))
	{
		if (allSortedUsers.IsFull()) return count;
		User* tempUser = new User;
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
				tempUser->SetFirstName(tempCharArr);
			}
			if (tempStorage[i + j].find("LastName: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 10);
				//Convert to proper type
				strcpy_s(tempCharArr, tempStorage[i + j].c_str());
				//Assign to new user
				tempUser->SetLastName(tempCharArr);
			}
			if (tempStorage[i + j].find("Major: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 7);
				//Convert to proper type
				strcpy_s(tempCharArr, tempStorage[i + j].c_str());
				//Assign to new user
				tempUser->SetMajor(tempCharArr);
			}
			if (tempStorage[i + j].find("Gender: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 8);
				//Assign to new user
				tempUser->SetGender(tempStorage[i + j][0]);
			}
			if (tempStorage[i + j].find("Email: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 7);
				//Convert to proper type
				strcpy_s(tempCharArr, tempStorage[i + j].c_str());
				//Assign to new user
				tempUser->SetEmail(tempCharArr);
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
				tempUser->SetDateOfBirth(dateOfBirth);
			}
			if (tempStorage[i + j].find("GPA: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 5);
				//Assign to new user
				tempUser->SetGPA(stof(tempStorage[i + j]));
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
			tempUser->SetAddress(streetName, streetNo, city, zip, state);
		}
		//Add tempUser to unsorted linkedList
		allSortedUsers.PutUser(tempUser);
		count += 1;
	}

	return count;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TestDriver::Populate(const char* input, TreeType& treeUsers) const
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
	while (count < (int)((tempStorage.size() + 1) / 13))
	{
		if (treeUsers.IsFull()) return count;
		User* tempUser = new User;
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
				tempUser->SetFirstName(tempCharArr);
			}
			if (tempStorage[i + j].find("LastName: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 10);
				//Convert to proper type
				strcpy_s(tempCharArr, tempStorage[i + j].c_str());
				//Assign to new user
				tempUser->SetLastName(tempCharArr);
			}
			if (tempStorage[i + j].find("Major: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 7);
				//Convert to proper type
				strcpy_s(tempCharArr, tempStorage[i + j].c_str());
				//Assign to new user
				tempUser->SetMajor(tempCharArr);
			}
			if (tempStorage[i + j].find("Gender: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 8);
				//Assign to new user
				tempUser->SetGender(tempStorage[i + j][0]);
			}
			if (tempStorage[i + j].find("Email: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 7);
				//Convert to proper type
				strcpy_s(tempCharArr, tempStorage[i + j].c_str());
				//Assign to new user
				tempUser->SetEmail(tempCharArr);
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
				tempUser->SetDateOfBirth(dateOfBirth);
			}
			if (tempStorage[i + j].find("GPA: ") != string::npos)
			{
				//Delete the label
				tempStorage[i + j].erase(0, 5);
				//Assign to new user
				tempUser->SetGPA(stof(tempStorage[i + j]));
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
			tempUser->SetAddress(streetName, streetNo, city, zip, state);
		}
		//Add tempUser to binary search tree
		treeUsers.PutUser(tempUser);
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

	cout << "BirthDate: " << users[count - 1].GetDateOfBirth().GetMonth() << " "
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
void TestDriver::Test(std::ofstream& outFile, TreeType& treeUsers) const
{
	//Print out users to a file
	outFile << "PRINTING USERS OUT FOR BINARY TREE: " << endl << endl;
	treeUsers.Print(PRE_ORDER, outFile);
	treeUsers.Print(IN_ORDER, outFile);
	treeUsers.Print(POST_ORDER, outFile);

	//Test unused methods
	outFile << endl << endl << "TESTING UNUSED METHODS: " << endl << endl;

	outFile << endl << endl << endl << endl;
}
void TestDriver::Test(TreeType& treeUsers) const
{
	//Print out users to a file
	cout << "PRINTING USERS OUT FOR BINARY TREE: " << endl << endl;
	treeUsers.Print(PRE_ORDER);

}
void TestDriver::TestList(UnsortedType& allUnsortedUsers) const
{
	//Print ID
	cout << "Name: Erik Failing" << endl;
	cout << "Username: efailing" << endl;
	cout << "Assignment 2" << endl << endl;

	//Print out users to console
	cout << "PRINTING USERS OUT FOR UNSORTED LINKED LIST: " << endl << endl;
	allUnsortedUsers.ResetList();
	for (int i = 0; i < allUnsortedUsers.GetLength(); i += 1)
	{
		allUnsortedUsers.GetNextUser();
		allUnsortedUsers.Print();
	}

	//Test unused methods
	cout << endl << endl << "TESTING UNUSED METHODS: " << endl << endl;
	allUnsortedUsers.PrintPartial();
	char fname[30];
	char lname[30];
	bool found;
	strcpy(fname, "John");
	strcpy(lname, "Rich");
	User* go = allUnsortedUsers.GetUser(fname, lname, found);
	if (found)
	{
		cout << "User: " << fname << " " << lname << " found." << endl;
		allUnsortedUsers.DeleteUser(go);
		cout << "Deleted User." << endl;
	}
	cout << endl << endl << endl << endl;
}
void TestDriver::TestList(std::ofstream& outFile, UnsortedType& allUnsortedUsers) const
{
	//Print ID
	outFile << "Name: Erik Failing" << endl;
	outFile << "Username: efailing" << endl;
	outFile << "Assignment 2" << endl << endl;

	//Print out users to console
	outFile << "PRINTING USERS OUT FOR UNSORTED LINKED LIST: " << endl << endl;
	allUnsortedUsers.ResetList();
	for (int i = 0; i < allUnsortedUsers.GetLength(); i += 1)
	{
		allUnsortedUsers.GetNextUser();
		allUnsortedUsers.Print(outFile);
	}

	//Test unused methods
	outFile << endl << endl << "TESTING UNUSED METHODS: " << endl << endl;
	allUnsortedUsers.PrintPartial(outFile);
	char fname[30];
	char lname[30];
	bool found;
	strcpy(fname, "John");
	strcpy(lname, "Rich");
	User* go = allUnsortedUsers.GetUser(fname, lname, found);
	if (found)
	{
		outFile << "User: " << fname << " " << lname << " found." << endl;
		allUnsortedUsers.DeleteUser(go);
		outFile << "Deleted User." << endl;
	}
	outFile << endl << endl << endl << endl;
}
void TestDriver::TestList(SortedType& allSortedUsers) const
{
	//Print out users to console
	cout << "PRINTING USERS OUT FOR SORTED LINKED LIST: " << endl << endl;
	allSortedUsers.ResetList();
	for (int i = 0; i < allSortedUsers.GetLength(); i += 1)
	{
		allSortedUsers.GetNextUser();
		allSortedUsers.Print();
	}

	//Test unused methods
	cout << endl << endl << "TESTING UNUSED METHODS: " << endl << endl;
	allSortedUsers.PrintPartial();
	char fname[30];
	char lname[30];
	bool found;
	strcpy(fname, "John");
	strcpy(lname, "Rich");
	User* go = allSortedUsers.GetUser(fname, lname, found);
	if (found)
	{
		cout << "User: " << fname << " " << lname << " found." << endl;
		allSortedUsers.DeleteUser(go);
		cout << "Deleted User." << endl;
	}
	cout << endl << endl << endl << endl;
}
void TestDriver::TestList(std::ofstream& outFile, SortedType& allSortedUsers) const
{
	//Print out users to console
	outFile << "PRINTING USERS OUT FOR SORTED LINKED LIST: " << endl << endl;
	allSortedUsers.ResetList();
	for (int i = 0; i < allSortedUsers.GetLength(); i += 1)
	{
		allSortedUsers.GetNextUser();
		allSortedUsers.Print(outFile);
	}

	//Test unused methods
	outFile << endl << endl << "TESTING UNUSED METHODS: " << endl << endl;
	allSortedUsers.PrintPartial(outFile);
	char fname[30];
	char lname[30];
	bool found;
	strcpy(fname, "John");
	strcpy(lname, "Rich");
	User* go = allSortedUsers.GetUser(fname, lname, found);
	if (found)
	{
		outFile << "User: " << fname << " " << lname << " found." << endl;
		allSortedUsers.DeleteUser(go);
		outFile << "Deleted User." << endl;
	}
	outFile << endl << endl << endl << endl;
}

void TestDriver::Test(char* outfilename, GraphType& userNet) 
{
	ofstream outFile;
	outFile.open(outfilename);
	if (!outFile)
	{
		cout << "Can't open file." << endl;
		return;
	}
	TestGraph(outFile, userNet);
}
void TestDriver::TestGraph(std::ofstream& outFile, GraphType& userNet) 
{
	//Test building the adjacency matrix
	userNet.PrintAdjacencyMatrix();
	userNet.PrintAdjacencyMatrix(outFile);
	
	//Test find sibling
	cout << endl << "Finding sibling of vertex 1 on the matrix:" << endl;
	userNet.findSibling(userNet.GetVertex(1))->Display();
	outFile << endl << "Finding sibling of vertex 1 on the matrix:" << endl;
	userNet.findSibling(userNet.GetVertex(1))->Display(outFile);

	//Test display ancestors
	cout << endl << "Finding the ancestors of vertex 6:" << endl;
	userNet.DisplayAncestors(userNet.GetVertex(6));
	outFile << endl << "Finding the ancestors of vertex 6:" << endl;
	userNet.DisplayAncestors(outFile, userNet.GetVertex(6));

	//Test find earliest common ancestor 
	cout << endl << "Finding earliest common ancestor of vertex 7 (Ri) and 10 (Al) on the matrix:" << endl;
	userNet.FindEarliestCommonAncestor(userNet.GetVertex(7), userNet.GetVertex(10))->Display();
	outFile << endl << "Finding earliest common ancestor of vertex 7 (Ri) and 10 (Al) on the matrix:" << endl;
	userNet.FindEarliestCommonAncestor(userNet.GetVertex(7), userNet.GetVertex(10))->Display(outFile);

}

//Deconstructor
TestDriver::~TestDriver()
{
}