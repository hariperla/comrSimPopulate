# comrSimPopulate
Populate COMR calibrations based on the CAN frame automatically in an excel

This program will read a csv and read a .h file which contains list of CAN frame enums that are being received by the TCM. It will then
find the appropriate CAN frame from the csv and get the index of that in the .h file and append to a csv. 
