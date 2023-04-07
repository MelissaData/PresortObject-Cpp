#include<iostream>
#include<cstring>
#include<cstdlib>
#include<list>
#include<vector> 

#include "mdPresort.h"
#include "PresortObject.h"
#include "DataContainer.h"

using namespace std;

// function declarations
void ParseArguments(string& license, string& testPresortFile, string& dataPath, int argc, char** argv);
void RunAsConsole(string license, string testPresortFile, string dataPath);
list<string> SplitResultCodes(string s, string delimiter);

int main(int argc, char* argv[])
{
	// Variables
	string license = "";
	string testPresortFile = "";
	string dataPath = "";

	ParseArguments(license, testPresortFile, dataPath, argc, argv);
	RunAsConsole(license, testPresortFile, dataPath);

	return 0;
}

void ParseArguments(string& license, string& testPresortFile, string& dataPath, int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (string(argv[i]) == "--license" || string(argv[i]) == "-l")
		{
			if (argv[i + 1] != NULL)
			{
				license = argv[i + 1];
			}
		}
		if (string(argv[i]) == "--file" || string(argv[i]) == "-f")
		{
			if (argv[i + 1] != NULL)
			{
				testPresortFile = argv[i + 1];
			}
		}
		if (string(argv[i]) == "--dataPath" || string(argv[i]) == "-d")
		{
			if (argv[i + 1] != NULL)
			{
				dataPath = argv[i + 1];
			}
		}
	}
}

void RunAsConsole(string license, string testPresortFile, string dataPath)
{
	cout << "\n============ WELCOME TO MELISSA PRESORT OBJECT WINDOWS C++ ===========\n" << endl;

	PresortObject* presortObject = new PresortObject(license, dataPath);

	bool shouldContinueRunning = true;

	while (shouldContinueRunning)
	{
		DataContainer dataContainer = DataContainer();

		if (testPresortFile.empty())
		{
			cout << "\nFill in each value to see the Presort Object results" << endl;
			cout << "Presort file path: ";

			string input;
			getline(cin, input);

			dataContainer.PresortFile = input;
			dataContainer.formatPresortOutputFile();
		}
		else
		{
			dataContainer.PresortFile = testPresortFile;
			dataContainer.formatPresortOutputFile();
		}

		// Print user input
		cout << "\n============================== INPUTS ==============================\n" << endl;
		cout << "\t         Presort File: " + string(dataContainer.PresortFile)     << endl;
		
		// Execute Presort Object
		presortObject->ExecuteObjectAndResultCodes(dataContainer);

		// Print output
		cout << "\n============================== OUTPUT ==============================\n" << endl;
		cout << "\n\Presort Object Information:"                                           << endl;
		
		list<string> sections = dataContainer.getWrapped();
		string fileName = dataContainer.getFileName();

		cout << "\t          Output File: " + sections.front() << endl;
		for (string section : sections)
		{
			if (section != sections.front())
			{
				cout << "\t                       " << section << endl;
			}
		}

		bool isValid = false;

		if (!testPresortFile.empty()) 
		{
			isValid = true;
			shouldContinueRunning = false;
		}
		while (!isValid)
		{
			string testAnotherResponse;

			cout << "\nTest another phone? (Y/N)" << endl;
			getline(cin, testAnotherResponse);

			if (!testAnotherResponse.empty())
			{
				if (testAnotherResponse == "y" || testAnotherResponse == "Y")
				{
					isValid = true;
				}
				else if (testAnotherResponse == "n" || testAnotherResponse == "N")
				{
					isValid = true;
					shouldContinueRunning = false;
				}
				else
				{
					cout << "Invalid Response, please respond 'Y' or 'N'" << endl;
				}
			}
		}
	}
	cout << "\n=============== THANK YOU FOR USING MELISSA C++ OBJECT =============\n" << endl;
}

