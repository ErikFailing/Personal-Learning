/*
Name - Erik W. Failing
Username - efailing
Assignment 2
*/

#include "pch.h"
#include "User.h"
#include "DateType.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>

using namespace std;

//Constructors
User::User()
{
	strcpy_s(fName, "John");
	strcpy_s(lName, "Doe");
	gender = 'M';
	strcpy_s(major, "CS");
	strcpy_s(email, "JohnDoe@email.com");
	GPA = 3.0f;
	dateOfBirth.Initialize(1, 1, 2000);
}
User::User(const char* afName, const char* alName, char aGender, const char* aMajor, 
	const char* aEmail, AddressType aAddress, float aGPA, DateType aDateOfBirth)
{
	strcpy_s(fName, afName);
	strcpy_s(lName, alName);
	gender = aGender;
	strcpy_s(major, aMajor);
	strcpy_s(email, aEmail);
	address = aAddress;
	GPA = aGPA;
	dateOfBirth = aDateOfBirth;
}

//Initializer
void User::Initialize(const char* afName, const char* alName, char aGender, const char* aMajor, 
	const char* aEmail, AddressType aAddress, float aGPA, DateType aDateOfBirth)
{
	strcpy_s(fName, afName);
	strcpy_s(lName, alName);
	gender = aGender;
	strcpy_s(major, aMajor);
	strcpy_s(email, aEmail);
	address = aAddress;
	GPA = aGPA;
	dateOfBirth = aDateOfBirth;
}


//GETTERS
void User::GetFirstName(char afname[]) const
{
	strcpy(afname, fName);
}
void User::GetLastName(char alname[]) const
{
	strcpy(alname, lName);
}
void User::GetMajor(char amajor[]) const
{
	strcpy(amajor, major);
}
void User::GetEmail(char aemail[]) const
{
	strcpy(aemail, email);
}
void User::GetGender(char& agender) const 
{
	agender = gender;
}
DateType User::GetDateOfBirth() const
{
	return dateOfBirth;
}
void User::GetDateOfBirth(DateType& aDateOfBirth) const
{
	aDateOfBirth = dateOfBirth;
}
float User::GetGPA() const
{
	return GPA;
}
void User::GetGPA(float& aGPA) const
{
	aGPA = GPA;
}
AddressType User::GetAddress() const
{
	return address;
}
void User::GetAddress(AddressType& aAddress) const
{
	aAddress = address;
}
void User::GetAddress(char aStreetName[], int& aStreetNo, char aCity[], int& aZip, char aState[]) const
{
	strcpy(aStreetName, address.streetName);
	aStreetNo = address.streetNo;
	strcpy(aCity, address.city);
	aZip = address.zip;
	strcpy(aState, address.state);
}


//SETTERS
void User::SetFirstName(const char* afName) 
{
	strcpy(fName, afName);
}
void User::SetLastName(const char* alName) 
{
	strcpy(lName, alName);
}
void User::SetMajor(const char* amajor)
{
	strcpy(major, amajor);
}
void User::SetEmail(const char* aemail)
{
	strcpy(email, aemail);
}
void User::SetGender(char aGender)
{
	gender = aGender;
}
void User::SetDateOfBirth(DateType aDateOfBirth)
{
	dateOfBirth = aDateOfBirth;
}
void User::SetGPA(float aGPA)
{
	GPA = aGPA;
}
void User::SetAddress(AddressType aAddress)
{
	address = aAddress;
}
void User::SetAddress(char aStreetName[], int aStreetNo, char aCity[], int aZip, char aState[])
{
	strcpy(address.streetName, aStreetName);
	address.streetNo = aStreetNo;
	strcpy(address.city, aCity);
	address.zip = aZip;
	strcpy(address.state, aState);
}

//Display to standard output stream
void User::Display() const
{
	char tempCharArray[30];
	char tempChar;
	float tempNum;

	GetFirstName(tempCharArray);
	cout << "FirstName: " << tempCharArray << endl;
	GetLastName(tempCharArray);
	cout << "LastName: " << tempCharArray << endl;
	GetMajor(tempCharArray);
	cout << "Major: " << tempCharArray << endl;
	GetGender(tempChar);
	cout << "Gender: " << tempChar << endl;
	GetEmail(tempCharArray);
	cout << "Email: " << tempCharArray << endl;
	GetGPA(tempNum);
	cout << "GPA: " << tempNum << endl;
	cout << "StreetName: " << address.streetName << endl;
	cout << "StreetNo: " << address.streetNo << endl;
	cout << "City: " << address.city << endl;
	cout << "Zip: " << address.zip << endl;
	cout << "State: " << address.state << endl;
	cout << "BirthDate: " << dateOfBirth.GetMonth() << " " << dateOfBirth.GetDay() << " " << dateOfBirth.GetYear() << endl;
	cout << "-----" << endl;
}

//Display to file
void User::Display(std::ofstream& outFile) const
{	
	char tempCharArray[30];
	char tempChar;
	float tempNum;

	GetFirstName(tempCharArray);
	outFile << "FirstName: " << tempCharArray << endl;
	GetLastName(tempCharArray);
	outFile << "LastName: " << tempCharArray << endl;
	GetMajor(tempCharArray);
	outFile << "Major: " << tempCharArray << endl;
	GetGender(tempChar);
	outFile << "Gender: " << tempChar << endl;
	GetEmail(tempCharArray);
	outFile << "Email: " << tempCharArray << endl;
	GetGPA(tempNum);
	outFile << "GPA: " << tempNum << endl;
	outFile << "StreetName: " << address.streetName << endl;
	outFile << "StreetNo: " << address.streetNo << endl;
	outFile << "City: " << address.city << endl;
	outFile << "Zip: " << address.zip << endl;
	outFile << "State: " << address.state << endl;
	outFile << "BirthDate: " << dateOfBirth.GetMonth() << " " << dateOfBirth.GetDay() << " " << dateOfBirth.GetYear() << endl;
	outFile << "-----" << endl;
}

//CompareTo based on date or birth of this user and another inputted user
RelationType User::comparedTo(User* aUser) const 
{
	return dateOfBirth.comparedTo(aUser->dateOfBirth);
}

//Deconstructor
User::~User()
{
}
