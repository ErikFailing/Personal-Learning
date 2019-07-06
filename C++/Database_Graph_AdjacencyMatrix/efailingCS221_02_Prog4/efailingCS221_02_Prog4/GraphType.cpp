/*
Name - Erik W. Failing
Username - efailing
Assignment 4
*/

#include "pch.h"
#include "GraphType.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

int IndexIs(User** vertices, User* vertex);

GraphType::GraphType()
{
	numVertices = 0;
	maxVertices = 50;
	vertices = new User*[maxVertices];
	edges = new bool*[maxVertices];
	for (int i = 0; i < maxVertices; i += 1) 
	{
		edges[i] = new bool[maxVertices];
	}
}

GraphType::GraphType(int noVertices) 
{
	numVertices = 0;
	maxVertices = noVertices;
	vertices = new User*[noVertices];
	edges = new bool*[noVertices];
	for (int i = 0; i < noVertices; i += 1)
	{
		edges[i] = new bool[noVertices];
	}
}

void GraphType::AddVertex(User* user) 
{
	vertices[numVertices] = user;
	edges[numVertices][numVertices] = false;
	for (int index = 0; index < numVertices; index += 1) 
	{
		edges[numVertices][index] = false;
		edges[index][numVertices] = false;
	}
	numVertices += 1;
}

void GraphType::AddEdge(User* fromVertex, User* toVertex) 
{
	int row = IndexIs(vertices, fromVertex);
	int col = IndexIs(vertices, toVertex);
	edges[row][col] = true;
}
int IndexIs(User** vertices, User* vertex) 
{
	int index = 0;
	while (!(vertex == vertices[index])) index += 1;
	return index;
}


void GraphType::PrintAdjacencyMatrix() 
{
	cout << "PRINTING DIRECTED ADJACENCY MATRIX FOR THE BINARY TREE:" << endl << endl;
	for (int row = 0; row < numVertices; row += 1) 
	{
		char name[30];
		vertices[row]->GetFirstName(name);
		cout << name[0] << name[1] << " ";
		for (int col = 0; col < numVertices; col += 1)
		{
			cout << edges[row][col] << " ";
		}
		cout << endl;
	}
}
void GraphType::PrintAdjacencyMatrix(std::ofstream& outFile) 
{
	outFile << "PRINTING DIRECTED ADJACENCY MATRIX FOR THE BINARY TREE:" << endl << endl;
	for (int row = 0; row < numVertices; row += 1)
	{
		char name[30];
		vertices[row]->GetFirstName(name);
		outFile << name[0] << name[1] << " ";
		for (int col = 0; col < numVertices; col += 1)
		{
			outFile << edges[row][col] << " ";
		}
		outFile << endl;
	}
}


User* GraphType::findSibling(User* user1) 
{
	//Find a 1 in the column of user1 vertex. Then search that row for another 1.
	//If another 1 is found, return the column vertex associated with it.
	//If no other 1 is found, return NULL
	int userIndex = IndexIs(vertices, user1);
	int index = 0;
	while (edges[index][userIndex] == false) 
	{
		index += 1;
	}
	int parentIndex = index;
	index = 0;
	bool foundSibling = false;
	while (!foundSibling && index < numVertices) 
	{
		if (edges[parentIndex][index] == true && index != userIndex) return vertices[index];
		else index += 1;
	}
	return NULL;
}

User* GraphType::GetVertex(int vertex) 
{
	return vertices[vertex];
}

void GraphType::DisplayAncestors(User* user1) 
{
	//Find the parent of the user and display them.
	//Loop this until no parent is found.
	int userIndex = IndexIs(vertices, user1);
	
	while (true) 
	{
		int index = 0;
		bool parentFound = false;
		while (parentFound == false && index < numVertices)
		{
			if (edges[index][userIndex] == true) parentFound = true;
			else index += 1;
		}
		if (parentFound == false) return;
		else
		{
			int parentIndex = index;
			userIndex = parentIndex;
			vertices[parentIndex]->Display();
		}
	}
	
}

void GraphType::DisplayAncestors(std::ofstream& outFile, User* user1) 
{
	//Find the parent of the user and display them.
	//Loop this until no parent is found.
	int userIndex = IndexIs(vertices, user1);

	while (true)
	{
		int index = 0;
		bool parentFound = false;
		while (parentFound == false && index < numVertices)
		{
			if (edges[index][userIndex] == true) parentFound = true;
			else index += 1;
		}
		if (parentFound == false) return;
		else
		{
			int parentIndex = index;
			userIndex = parentIndex;
			vertices[parentIndex]->Display(outFile);
		}
	}
}

User* GraphType::FindEarliestCommonAncestor(User* user1, User* user2) 
{
	//Find the parents of user 1 & 2.
	//If pU1 == pU2 return parent
	//else 

	

	int user1Index = IndexIs(vertices, user1);
	int user2Index = IndexIs(vertices, user2);

	while (true) 
	{
		int index1 = 0;
		bool parentFound = false;
		while (parentFound == false && index1 < numVertices)
		{
			if (edges[index1][user1Index] == true) parentFound = true;
			else index1 += 1;
		}


		while (parentFound == true) 
		{
			int index2 = 0;
			parentFound = false;
			while (parentFound == false && index2 < numVertices)
			{
				if (edges[index2][user2Index] == true) parentFound = true;
				else index2 += 1;
			}
			if (vertices[index1] == vertices[index2]) return vertices[index1];
			else if (parentFound == true) user2Index = index2;
		}
		
		user1Index = index1;
		user2Index = IndexIs(vertices, user2);

	}
}



GraphType::~GraphType()
{
}
