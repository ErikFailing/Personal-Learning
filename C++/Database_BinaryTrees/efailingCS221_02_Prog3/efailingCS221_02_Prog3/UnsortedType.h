/*
Name - Erik W. Failing
Username - efailing
Assignment 3
*/

#include "User.h"

#pragma once

struct NodeType
{
	User* user;
	NodeType* next;
};

class UnsortedType
{
protected:
	int length;
	NodeType* listData;
	NodeType* currentPos;
public:


	UnsortedType();
	void MakeEmpty();
	bool IsFull() const;
	int GetLength() const;
	void ResetList();
	User* GetUser(char fname[], char lname[], bool& found) const;
	virtual void PutUser(User* user);
	void DeleteUser(User* user);
	User* GetNextUser();
	void Print() const;
	void Print(std::ofstream& out) const;
	void PrintPartial() const;
	void PrintPartial(std::ofstream& out) const;
	~UnsortedType();
};

