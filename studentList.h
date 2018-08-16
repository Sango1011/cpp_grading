// This is the header file.
// Do not attempt to compile it.

#include <fstream>
using namespace std;
#include <iostream>
#include <vector>
#include <iomanip>
#include "student.h"
#ifndef STUDENTLIST
#define STUDENTLIST

// studentList.h

/*------------------------------------------------------------------------
data structures (arrays, variables and constants) to store the information
-------------------------------------------------------------------------*/
class studentList
{
	private:
		unsigned int maxSize;
		int  nameLength, idLength;
		vector<student> stuList;


	public:
		studentList(unsigned int size=0) //default
		{
			nameLength = student::nameLength;
			maxSize = size;
			idLength = student::idLength;
		}
		bool addStudent(student);
		void writeData(ostream& outfile);
		void processGrade();
		void printReport(ostream& outfile);
		void printTable(ostream& outfile);
		void printStudent(int index, ostream& outfile);
		float* getHomework(int i);
		float* getTest(int i);
				
		student& getStudent(int i);// IMPORTANT: returns a REFERENCE
                             // to the ith-student
		// Both search functions return the index of the student
		// if there is a match; -1 otherwise.
		int searchById(string Id);
		int searchByName(char name[]);					 
};

#endif
