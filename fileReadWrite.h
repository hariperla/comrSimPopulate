#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

class FileReadWrite {
public:
	vector <string> readFile(string fileName);
	string removeSpaces(string str);
	vector <string> removeComments(vector <string> A, string B[], string C[]);
	string appendEnumToCal(string str1, string str2, string str3);
	void writeFile(string fileNameIn, string fileNameOut, vector <string> comrApp);
};

string FileReadWrite::appendEnumToCal(string str1,string str2,string str3) {
	str1.append(str2);
	str1.append(str3);
	return str1;
}


// Function to remove all spaces from a given string 
string FileReadWrite::removeSpaces(string str)
{
	str.erase(remove(str.begin(), str.end(), '\t'), str.end());
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	return str;
}

// Function to remove comments in a given vector strings
vector <string> FileReadWrite::removeComments(vector <string> A, string B[], string C[]) {
	vector <string> rxMsgs;
	bool m_cmt = false;
	
	// Loop through the line data from comr h file
	for (unsigned int j = 0; j < A.size(); j++) {
		B[j] = A.at(j);
		// Loop through the words each line to remove comments and spaces
		for (unsigned int i = 0; i < B[j].length(); i++) {
			if (m_cmt == true && B[j][i] == '*' && B[j][i + 1] == '/') {
				m_cmt = false;
				i++;
			}
			else if (B[j][i] == '/' && B[j][i + 1] == '*') {
				m_cmt = true;
				i++;
			}
			else if (m_cmt) {
				continue;
			}
			else {
				C[j] += B[j][i];
			}
		}
		C[j] = removeSpaces(C[j]);
		rxMsgs.push_back(C[j]);
	}
	return rxMsgs;
}


vector <string> FileReadWrite::readFile(string fileName) {
	// Assign a file pointer
	fstream fin;

	// Open an existing file
	fin.open(fileName, ios::in);

	// Read data from the above file
	vector <string> row;
	string line, word;

	while (fin.good()) {

		// Read an entire row and store it in a string 
		getline(fin, line);

		// To break the words in the string
		stringstream s(line);

		while (getline(s, word, ',')) {
			// Add all the column data of a row to vector
			row.push_back(word);
		}
	}
	return row;
}

void FileReadWrite::writeFile(string fileNameIn, string fileNameOut, vector <string> comrApp) {
	// Assign a file pointer
	fstream fin;
	ofstream fout;

	// Open an existing file
	fin.open(fileNameIn, ios::in);
	fout.open(fileNameOut, ios::out);

	// Read data from the above file
	vector <string> row;
	string line, word;
	int lineCount = 0;
	comrApp.insert(comrApp.begin(), "CAN_Cal");

	while (fin.good()) {

		// Read an entire row and store it in a string 
		getline(fin, line);
		row.push_back(line);
		lineCount++;
		}

	for (unsigned int i = 0; i < comrApp.size(); i++) {
		fout << row[i] << "," << comrApp[i] << endl;
	}
}