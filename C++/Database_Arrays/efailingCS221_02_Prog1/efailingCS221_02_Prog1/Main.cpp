/*
Name - Erik W. Failing
Username - efailing
Assignment 1
*/

#include "pch.h"
#include "DateType.h"
#include "TestDriver.h"
#include "User.h"
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

int main()
{
	char cCurrentPath[FILENAME_MAX];
	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		return errno;
	}
	cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';

	printf("The current working directory is %s", cCurrentPath);
	cout << endl << endl;
	
	
	TestDriver test;
	ofstream outFile;
	User users[100];
	int count = 0;
	char path[300];
	string temp(cCurrentPath);
	string sampleFilePath = temp + "\\hw1samplefile.txt";
	string outputFilePath = temp + "\\efailingHw1Outfile.txt";
	
	//Assign path to sampleFilePath
	strcpy(path, sampleFilePath.c_str());

	//Test to console
	count = test.Populate(path, users);
	test.Test(users, count);

	//Open outfile
	strcpy(path, outputFilePath.c_str());
	outFile.open(path);
	if (!outFile)
	{
		cout << "Can't open file." << endl;
		return 1;
	}

	//Test to file
	test.Test(outFile, users, count);

	outFile.close();

	return 0;
}
