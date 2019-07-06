/*
Name - Erik W. Failing
Username - efailing
Assignment 4
*/

#pragma once
#include "User.h"
#include "GraphType.h"
#include <iostream>

enum OrderType { PRE_ORDER, IN_ORDER, POST_ORDER };

struct TreeNode {
	User* user;
	TreeNode* left;
	TreeNode* right;
};

class TreeType
{
private:
	TreeNode* root;
public:
	TreeType();
	~TreeType();
	void MakeEmpty();
	bool IsEmpty() const;
	bool IsFull();
	int GetLength() const;
	User* GetUser(User* user, bool& found) const;
	void DeleteUser(User* user);

	void PutUser(User* user); // This will insert user to the tree
	User* GetHighestGPA(float& gpa); // needs to call another recursive function
	void Print(OrderType otype, std::ofstream& outfile); // needs to call another recursive function PrintTree
	void Print(OrderType otype);
	void PrintDescendants(User* user, OrderType otype, std::ofstream& outfile); // find the user in the tree and then find the descendants of the user
	void print2D();

	void BuildVertexGraph(GraphType& net);

};

