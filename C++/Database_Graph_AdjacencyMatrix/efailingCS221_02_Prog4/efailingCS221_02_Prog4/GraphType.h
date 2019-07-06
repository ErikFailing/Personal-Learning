/*
Name - Erik W. Failing
Username - efailing
Assignment 4
*/

#pragma once
#include "User.h"

class GraphType
{
private:
	int numVertices;
	int maxVertices;
	User** vertices;
	bool** edges;
public:
	GraphType();
	GraphType(int noVertices);
	void AddVertex(User* user);
	void AddEdge(User* fromVertex, User* toVertex);
	User* findSibling(User* user1);
	void DisplayAncestors(User* user1);
	void DisplayAncestors(std::ofstream& outFile, User* user1);
	User* FindEarliestCommonAncestor(User* user1, User* user2);
	void PrintAdjacencyMatrix();
	void PrintAdjacencyMatrix(std::ofstream& outFile);
	User* GetVertex(int vertex);


	~GraphType();
};

