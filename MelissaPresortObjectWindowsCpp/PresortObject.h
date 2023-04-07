#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<map>

#include "mdPresort.h"
#include "DataContainer.h"

using namespace std;

#ifndef PRESORTOBJECT_H
#define PRESORTOBJECT_H

class PresortObject
{
public:
	// Path to Presort Object data files (.dat, etc)
	string dataFilePath;

	// Create instance of Melissa Presort Object
	mdPresort* mdPresortObj = new mdPresort;

	PresortObject(string license, string dataPath);

	// This will call the lookup function to process the input presort file as well as generate the result codes
	void ExecuteObjectAndResultCodes(DataContainer& data);
};

#endif
