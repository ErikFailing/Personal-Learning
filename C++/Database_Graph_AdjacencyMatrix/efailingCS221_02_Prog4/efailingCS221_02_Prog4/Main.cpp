/*
Name - Erik W. Failing
Username - efailing
Assignment 4
*/

#include "pch.h"
#include "DateType.h"
#include "TestDriver.h"
#include "User.h"
#include "UnsortedType.h"
#include "SortedType.h"
#include "TreeType.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <fstream>
#include <math.h>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <limits>
#include <vector>
#include <tuple>
#include <map>
#include <iterator>
#include <algorithm>
#include <filesystem>
#include <windows.h>
#include <stdio.h> 
#include <direct.h>
#define GetCurrentDir getcwd

using namespace std;

#pragma once

int main()
{

	//Create a variable path to output files to and get files from
	char cCurrentPath[FILENAME_MAX];
	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		return errno;
	}
	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
	printf("The current working directory is %s", cCurrentPath);
	cout << endl << endl;
	char path[300];
	string temp(cCurrentPath);
	string sampleFilePath = temp + "\\hw1samplefile.txt";
	string outputFilePath = temp + "\\efailingHw4Outfile.txt";

	TestDriver test;
	ofstream outFile;
	//User users[100];
	//int count = 0;
	//UnsortedType allUnsortedUsers;
	//SortedType allSortedUsers;
	TreeType treeUsers;
	int noUsers;

	//Assign path to sampleFilePath
	strcpy(path, sampleFilePath.c_str());

	//Populate Unsorted, Sorted and Array
	//count = test.Populate(path, users);
	//test.Populate(path, allUnsortedUsers);
	//test.Populate(path, allSortedUsers);
	noUsers = test.Populate(path, treeUsers);
	GraphType userNet(noUsers);
	treeUsers.BuildVertexGraph(userNet);

	//Run Tests on consoles
	//test.Test(users, count);
	//test.TestList(allUnsortedUsers);
	//test.TestList(allSortedUsers);
	test.Test(treeUsers);

	//Open outfile and test to it
	strcpy(path, outputFilePath.c_str());
	//outFile.open(path);
	//if (!outFile)
	//{
	//	cout << "Can't open file." << endl;
	//	return 1;
	//}
	//test.Test(outFile, users, count);
	//test.TestList(outFile, allUnsortedUsers);
	//test.TestList(outFile, allSortedUsers);
	//test.Test(outFile, treeUsers);
	//outFile.close();
	treeUsers.print2D();
	test.Test(path, userNet);

	//Make everything empty
	//allUnsortedUsers.MakeEmpty();
	//allSortedUsers.MakeEmpty();
	//treeUsers.MakeEmpty();

	return 0;
}
