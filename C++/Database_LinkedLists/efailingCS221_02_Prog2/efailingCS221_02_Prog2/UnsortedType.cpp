/*
Name - Erik W. Failing
Username - efailing
Assignment 2
*/

#include "pch.h"
#include "UnsortedType.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>

using namespace std;


UnsortedType::UnsortedType()
{
	length = 0;
	listData = NULL;
}

//Empties the list, deallocating all items and setting length to 0
void UnsortedType::MakeEmpty() 
{
	NodeType* tempPtr;
	while (listData != NULL) 
	{
		tempPtr = listData;
		listData = listData->next;
		delete tempPtr;
	}
	length = 0;
}

//Returns true if there is no room on the free store for another User, returns false if otherwise
bool UnsortedType::IsFull() const 
{
	NodeType* location;
	try
	{
		location = new NodeType;
		delete location;
		return false;
	}
	catch (std::bad_alloc exception)
	{
		return true;
	}
}


//Returns the current length of the linked list
int UnsortedType::GetLength() const 
{
	return length;
}

//Resets the current position to NULL
void UnsortedType::ResetList()
{
	currentPos = NULL;
}

//Returns the user searched for based on name
User* UnsortedType::GetUser(char fname[], char lname[], bool& found) const 
{
	bool moreToSearch;
	NodeType* location;

	location = listData;
	found = false;
	moreToSearch = (location != NULL);

	while (moreToSearch && !found) 
	{
		char locationFirstName[30];
		char locationLastName[30];
		location->user->GetFirstName(locationFirstName);
		location->user->GetLastName(locationLastName);
		
		if (locationFirstName == fname && locationLastName == lname) 
		{
			location = location->next;
			moreToSearch = (location != NULL);
		}
		else 
		{
			found = true;
		}
	}
	return location->user;
}

//Adds the user to the unsorted linked list
void UnsortedType::PutUser(User* user) 
{
	NodeType* location;

	location = new NodeType;
	location->user = user;
	location->next = listData;
	listData = location;
	length += 1;
}

//Deletes the given user from the list
void UnsortedType::DeleteUser(User* user) 
{
	NodeType* location = listData;
	NodeType* tempLocation = listData;
	//Locate Node to be deleted
	if (user == listData->user)
	{
		tempLocation = location;
		listData = listData->next;
	}
	else 
	{
		while ((user->comparedTo((location->next)->user)) != EQUAL) 
		{
			location = location->next;
			//Delete node at location->next
			tempLocation = location->next;
			location->next = (location->next)->next;
		}
		delete tempLocation;
		length -= 1;
	}
}

//Gets the next user in the linked list
User* UnsortedType::GetNextUser() 
{
	if (currentPos == NULL) currentPos = listData;
	else if (currentPos->next == NULL) currentPos = listData; //Loop back once end is reached
	else currentPos = currentPos->next;
	return currentPos->user;
}

//Prints the User to the console
void UnsortedType::Print() const 
{
	currentPos->user->Display();
}

//Prints the user to the output file
void UnsortedType::Print(std::ofstream& out) const 
{
	currentPos->user->Display(out);
}

//Prints the user's name to the console
void UnsortedType::PrintPartial() const 
{
	char fname[30];
	char lname[30];
	currentPos->user->GetFirstName(fname);
	currentPos->user->GetLastName(lname);
	cout << "FirstName: " << fname << endl;
	cout << "LastName: " << lname << endl;
	cout << "-----" << endl;
}

//Prints the user's name to the output file
void UnsortedType::PrintPartial(std::ofstream& out) const 
{
	char fname[30];
	char lname[30];
	currentPos->user->GetFirstName(fname);
	currentPos->user->GetLastName(lname);
	out << "FirstName: " << fname << endl;
	out << "LastName: " << lname << endl;
	out << "-----" << endl;
}


UnsortedType::~UnsortedType()
{
	NodeType* tempPtr;
	while (listData != NULL) 
	{
		tempPtr = listData;
		listData = listData->next;
		delete tempPtr;
	}
}
