/*
Name - Erik W. Failing
Username - efailing
Assignment 3
*/

#pragma once
#include "User.h"
#include "UnsortedType.h"
#include "SortedType.h"
#include "TreeType.h"

class TestDriver
{
public:
	//Constructor
	TestDriver();

	//Read in from file
	int Populate(const char* input, User users[]);
	int Populate(const char* input, UnsortedType& allUnsortedUsers) const;
	int Populate(const char* input, SortedType& allSortedUsers) const;
	int Populate(const char* input, TreeType& treeUsers) const;

	//Testers
	void Test(User users[], int count) const;
	void Test(std::ofstream& outFile, User  users[], int count) const;
	void Test(std::ofstream& outFile, TreeType& treeUsers) const;
	void TestList(UnsortedType& allUnsortedUsers) const;
	void TestList(std::ofstream& outFile, UnsortedType& allUnsortedUsers) const;
	void TestList(SortedType& allSortedUsers) const;
	void TestList(std::ofstream& outFile, SortedType& allSortedUsers) const;

	//Destructor
	~TestDriver();
};
