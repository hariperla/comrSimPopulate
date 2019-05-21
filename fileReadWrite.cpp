// csvRead.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include "fileReadWrite.h"

int main()
{
	// Creating class object and other necessary objects
	FileReadWrite readCSV, read_h_File;
	string file1, file2, file3;
	vector <string> rowData;
	vector <string> comrData;
	vector <string> comr_CAN_Rx_Msg;
	vector <string> canFrame;
	vector <string> comrCalInfo;
	vector <string> comrCalInfoAppended;
	string* sigGrpName;
	string* sigGrpNameNoComments;
	string appendedString;
	unsigned int count, index = 0;

	cout << "Reading csv!\n";
	file1 = "W:/UdacityLearning/Cpp_Projects/csvRead/csvRead/ReceiveCOMRTestParameters1.csv";
	rowData = readCSV.readFile(file1);

	cout << "Reading comr file which has the messages!" << endl;
	file2 = "W:/UdacityLearning/Cpp_Projects/csvRead/csvRead/comrb_can_rx_msg.txt";
	comrData = read_h_File.readFile("W:/UdacityLearning/Cpp_Projects/csvRead/csvRead/comrb_can_rx_msg.txt");

	// Output file name
	file3 = "W:/UdacityLearning/Cpp_Projects/csvRead/csvRead/ReceiveCOMRTestParameters2.csv";

	// Store just the comr frames into a string vector
	vector <string> comrDataRx(comrData.begin() + 20, comrData.end() - 1);

	// Dynamically allocate memory for the comr signals because new CAN msgs can be added
	int comrDataSize = comrDataRx.size();
	sigGrpName = new string[comrDataSize];
	sigGrpNameNoComments = new string[comrDataSize];

	// Loop through the csv and get all the CAN frames listed
	for (unsigned int i = 9; i < rowData.size(); i += 9) {
		canFrame.push_back(rowData.at(i));
	}

	// Remove unwanted comments, spaces and tabs from the comr file and just grab the msgs
	comr_CAN_Rx_Msg = read_h_File.removeComments(comrDataRx, sigGrpName, sigGrpNameNoComments);

	// Delete previously allocated memory because, we finished using the pointer
	delete[] sigGrpName;
	delete[] sigGrpNameNoComments;

	for (unsigned int i = 0; i < canFrame.size(); i++) {
		// Reset count for each msg
		count = 0;
		for (unsigned int j = 0; j < comr_CAN_Rx_Msg.size(); j++) {
			if (comr_CAN_Rx_Msg[j].find(canFrame[i]) < 20) {
				index = j;
				count++;
			}
		}
		if (count > 1) {
			index -= 1;
		}
		comrCalInfo.push_back(comr_CAN_Rx_Msg[index]);
	}

	// After getting the comr rx messages, append the cal to the rx messages to write to csv
	for (unsigned int i = 0; i < comrCalInfo.size(); i++) {
		appendedString = readCSV.appendEnumToCal("KaCOMR_NormReceiveMsgObj[", comrCalInfo[i], "]");
		comrCalInfoAppended.push_back(appendedString);
	}

	readCSV.writeFile(file1, file3, comrCalInfoAppended);

	return 0;
}
