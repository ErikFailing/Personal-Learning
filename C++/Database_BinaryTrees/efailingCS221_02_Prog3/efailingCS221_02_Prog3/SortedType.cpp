/*
Name - Erik W. Failing
Username - efailing
Assignment 3
*/

#include "pch.h"
#include "SortedType.h"
#pragma once


SortedType::SortedType()
{
}

//Adds the user into the right place on the list
void SortedType::PutUser(User* user)
{
	//Creating new Node with inputted user
	NodeType* location;
	location = new NodeType;
	location->user = user;

	//If list is empty insert right away
	if (listData == NULL)
	{
		location->next = NULL;
		listData = location;
	}
	//Else if new node is less than or equal to first node, insert right away
	else if ((location->user->comparedTo(listData->user)) == LESS || (location->user->comparedTo(listData->user)) == EQUAL)
	{
		location->next = listData;
		listData = location;
	}
	else
	{
		currentPos = listData;
		while ((currentPos->next != NULL) && (location->user->comparedTo(currentPos->next->user) == GREATER))
		{
			currentPos = currentPos->next;
		}
		location->next = currentPos->next;
		currentPos->next = location;

	}

	length += 1;
}

SortedType::~SortedType()
{
}

