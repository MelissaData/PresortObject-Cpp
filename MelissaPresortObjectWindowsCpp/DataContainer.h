#include<iostream>
#include<string>
#include<list>
#include<vector>
#include<Windows.h>

#ifndef DATACONTAINER_H
#define DATACONTAINER_H

using namespace std;

class DataContainer
{
public:
	string PresortFile;
	string OutputFile;

	DataContainer() {};
	
	void formatPresortOutputFile()
	{
		// change the name of the output file
		int location = PresortFile.find(".csv");
		OutputFile = PresortFile.substr(0, location) + "_output.csv";
	};

	// Return a wrapped path
	list<string> getWrapped()
	{	
		TCHAR cwd[MAX_PATH];

		if (GetCurrentDirectory(MAX_PATH, cwd) != 0)
		{
			// convert to wide string and char in order to be able to use DWORD
			wstring widestr = wstring(OutputFile.begin(), OutputFile.end());
			vector<wchar_t> fullPath(MAX_PATH);
			//const wchar_t* szFileName = widestr.c_str();
			//wchar_t szFullPath[MAX_PATH];

			DWORD dwResult = GetFullPathNameW(widestr.c_str(), MAX_PATH, fullPath.data(), nullptr);

			// convert wchar to string
			wstring ws(fullPath.data());
			string strfullPath(ws.begin(), ws.end());

			// Get the split string
			list<string> substrings = split(strfullPath, '\\');

			return substrings;
		}
	}
	
	// Return the filename from the OutputFile (if relative path)
	string getFileName()
	{
		size_t pos = OutputFile.find_last_of("\\");

		if (pos != string::npos)
		{
			return OutputFile.substr(pos + 1);
		}
		else
		{
			return OutputFile;
		}
	}

	// Return a vector with split substrings using the delimiter
	list<string> split(const string str, const char delimiter)
	{
		list<string> substrings;

		int maxLineLength = 50;
		size_t start = 0;
		size_t end = str.find(delimiter);

		string currentLine = "";

		while (end != string::npos)
		{
			string temp = currentLine + str.substr(start, end - start);

			if (temp.size() > maxLineLength)
			{
				substrings.push_back(currentLine);
				currentLine = "";
			}

			currentLine += str.substr(start, end - start) + "\\";

			start = end + 1;
			end = str.find(delimiter, start);
		}

		if (currentLine.length() > 0)
		{
			substrings.push_back(currentLine);
			substrings.push_back(str.substr(start));
		}

		return substrings;
	}
};

#endif