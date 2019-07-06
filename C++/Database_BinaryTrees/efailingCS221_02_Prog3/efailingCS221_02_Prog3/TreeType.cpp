/*
Name - Erik W. Failing
Username - efailing
Assignment 3
*/

#include "pch.h"
#include "TreeType.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>

using namespace std;

#pragma once

int CountNodes(TreeNode* tree);
void Retrieve(TreeNode* tree, User* user, bool& found);
void Delete(TreeNode* tree, User* user);
void DeleteNode(TreeNode* tree);
void GetPredecessor(TreeNode* tree, User* data);
void Insert(TreeNode*& tree, User* user);
void PrintTreePreOrder(TreeNode* tree, std::ofstream& outfile);
void PrintTreeInOrder(TreeNode* tree, std::ofstream& outfile);
void PrintTreePostOrder(TreeNode* tree, std::ofstream& outfile);
void Destroy(TreeNode*& tree);


//Constructor
TreeType::TreeType()
{
	root = NULL;
}

//Empties the tree
void TreeType::MakeEmpty()
{
	Destroy(root);
	root = NULL;
}

//Returns true if the tree is empty and flase otherwise
bool TreeType::IsEmpty() const
{
	return root == NULL;
}

//Returns true if the free store has no room for another node and false otherwise
bool TreeType::IsFull()
{
	TreeNode* location;
	try
	{
		location = new TreeNode;
		delete location;
		return false;
	}
	catch (std::bad_alloc exception)
	{
		return true;
	}
}

//Returns the number of nodes in the tree
int TreeType::GetLength() const
{
	return CountNodes(root);
}
int CountNodes(TreeNode* tree)
{
	if (tree == NULL) return 0;
	else return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

//Returns the searched for user if it is in the tree
User* TreeType::GetUser(User* user, bool& found) const
{
	Retrieve(root, user, found);
	return user;
}
void Retrieve(TreeNode* tree, User* user, bool& found)
{
	if (tree == NULL) found = false;
	else if (user < tree->user) Retrieve(tree->left, user, found);
	else if (user > tree->user) Retrieve(tree->right, user, found);
	else {

		user = tree->user;
		found = true;
	}
}

//Deletes the user from the tree
void TreeType::DeleteUser(User* user)
{
	Delete(root, user);
}
void Delete(TreeNode* tree, User* user)
{
	if (user < tree->user) Delete(tree->left, user);
	else if (user > tree->user) Delete(tree->right, user);
	else
	{
		DeleteNode(tree);
	}
}
void DeleteNode(TreeNode* tree)
{
	User* data = NULL;
	TreeNode* tempPtr = tree;
	if (tree->left == NULL)
	{
		tree = tree->right;
		delete tempPtr;
	}
	else if (tree->right == NULL)
	{
		tree = tree->left;
		delete tempPtr;
	}
	else
	{
		GetPredecessor(tree->left, data);
		tree->user = data;
		Delete(tree->left, data);
	}
}
void GetPredecessor(TreeNode* tree, User* data)
{
	while (tree->right != NULL)
	{
		tree = tree->right;
		data = tree->user;
	}
}




//Inserts user into the tree
void TreeType::PutUser(User* user)
{
	Insert(root, user);
}
void Insert(TreeNode*& tree, User* user)
{
	if (tree == NULL)
	{
		tree = new TreeNode;
		tree->right = NULL;
		tree->left = NULL;
		tree->user = user;
	}
	else if (user < tree->user) Insert(tree->left, user);
	else Insert(tree->right, user);
}

//Returns the user with the highest GPA
User* TreeType::GetHighestGPA(float& gpa)
{
	TreeNode* currentHighest = root;
	while (currentHighest->right != NULL)
	{
		currentHighest = currentHighest->right;
	}
	gpa = currentHighest->user->GetGPA();
	return currentHighest->user;
}

//Prints the tree to an outfile
void TreeType::Print(OrderType otype, std::ofstream& outfile)
{
	if (otype == PRE_ORDER) 
	{
		outfile << "PRINTING PRE_ORDER: " << endl;
		PrintTreePreOrder(root, outfile);
		outfile << endl << endl;
	}
	else if (otype == IN_ORDER) 
	{
		outfile << "PRINTING IN_ORDER: " << endl;
		PrintTreeInOrder(root, outfile);
		outfile << endl << endl;
	}
	else if (otype == POST_ORDER) 
	{
		outfile << "PRINTING IN POST_ORDER: " << endl;
		PrintTreePostOrder(root, outfile);
		outfile << endl << endl;
	}
}

void PrintTreePreOrder(TreeNode* tree, std::ofstream& outfile)
{
	cout << "CALLED" << endl;
	if (tree != NULL)
	{
		tree->user->Display(outfile);
		cout << "PRINTING" << endl;
		PrintTreePreOrder(tree->left, outfile); //left
		PrintTreePreOrder(tree->right, outfile); //right
	}
}
void PrintTreeInOrder(TreeNode* tree, std::ofstream& outfile)
{
	if (tree != NULL)
	{
		PrintTreeInOrder(tree->left, outfile); //left
		tree->user->Display(outfile);
		PrintTreeInOrder(tree->right, outfile); //right
	}
}
void PrintTreePostOrder(TreeNode* tree, std::ofstream& outfile)
{
	if (tree != NULL)
	{
		PrintTreePostOrder(tree->left, outfile); //left
		PrintTreePostOrder(tree->right, outfile); //right
		tree->user->Display(outfile);
	}
}

//Finds the user in the tree and prints it and the descendants of the user
void TreeType::PrintDescendants(User* user, OrderType otype, std::ofstream& outfile)
{
	bool found = false;
	User* gotuser = GetUser(user, found);
	if (found == false) return;
	else Print(otype, outfile);
}

//Deconstructor
TreeType::~TreeType()
{
	Destroy(root);
}
void Destroy(TreeNode*& tree)
{
	if (tree != NULL)
	{
		Destroy(tree->left);
		Destroy(tree->right);
		delete tree;
	}
}
