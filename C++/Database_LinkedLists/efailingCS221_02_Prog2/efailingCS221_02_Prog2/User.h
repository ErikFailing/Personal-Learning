/*
Name - Erik W. Failing
Username - efailing
Assignment 2
*/

#pragma once
#include <string>
#include "DateType.h"

struct AddressType
{
	char streetName[30] = "Nowhere Street";
	int streetNo = 404;
	char city[30] = "Nonexistant city";
	int zip = 33333;
	char state[3] = {'N', 'A', 'H'};
};

class User
{
private:
	char fName[30];
	char lName[30];
	char gender;
	char major[30];
	char email[30];
	AddressType address;
	float GPA;
	DateType dateOfBirth;
public:
	//Constructors
	User();
	User(const char* afName, const char* alName, char aGender, const char* aMajor, 
		const char* aEmail, AddressType aAddress, float aGPA, DateType aDateOfBirth);

	//Initializer
	void Initialize(const char* afName, const char* alName, char aGender, const char* aMajor, 
		const char* aEmail, AddressType aAddress, float aGPA, DateType aDateOfBirth);

	//Getters
	void GetFirstName(char afname[]) const;
	void GetLastName(char alname[]) const;
	void GetMajor(char amajor[]) const;
	void GetEmail(char aemail[]) const;
	void GetGender(char& agender) const;
	DateType GetDateOfBirth() const;
	void GetDateOfBirth(DateType& aDateOfBirth) const;
	float GetGPA() const;
	void GetGPA(float& aGPA) const;
	AddressType GetAddress() const;
	void GetAddress(AddressType& aAddress) const;
	void GetAddress(char aStreetName[], int& aStreetNo, char aCity[], int& aZip, char aState[]) const;

	//Setters
	void SetFirstName(const char* afName);
	void SetLastName(const char* alName);
	void SetMajor(const char* amajor);
	void SetEmail(const char* anemail);
	void SetGender(char aGender);
	void SetDateOfBirth(DateType aDateOfBirth);
	void SetGPA(float aGPA);
	void SetAddress(AddressType aAddress);
	void SetAddress(char aStreetName[], int aStreetNo, char aCity[], int aZip, char aState[]);

	//Displayers
	void Display() const;
	void Display(std::ofstream& outFile) const;

	//CompareTo
	RelationType comparedTo(User* aUser) const;

	//Deconstructor
	~User();
};

