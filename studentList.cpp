//  with the command "g++ -c studentList.cpp"

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "student.h"
#include "studentList.h"
#include <vector>
using namespace std;

/*------------------------------------------------------------------------
Functions for handling and processing the list of  students
-------------------------------------------------------------------------*/

bool studentList::addStudent(student stu)
{
	if ((stuList.size()) >= maxSize)
		return false;
	stuList.push_back(stu);
		return true;
}

void studentList::writeData(ostream& outfile)
{		//writes the raw data for the student to an outfile
	for(unsigned int index = 0; index < stuList.size(); index++)
    {
		(stuList.at(index)).writeStudent(outfile);
		outfile << endl;
    }
}

void studentList::processGrade()
{  // processes the grade for the list of students.

  for(unsigned int index = 0; index < stuList.size(); index++)
    (stuList.at(index)).processStudent();
}

void studentList::printReport(ostream& outfile)
{	//prints the processed data in report form
  for(unsigned int index = 0; index < stuList.size(); index++)
  {
   (stuList.at(index)).printReport(outfile);
  }
}

void studentList::printTable(ostream& outfile)
{	//prints the processed data in tabular form	
	for(unsigned int index = 0; index < stuList.size(); index++)
   {
      (stuList.at(index)).printRecord(outfile);
   }
}

void studentList::printStudent(int index, ostream& outfile)
{	//prints the raw data for the students
	(stuList.at(index)).writeStudent(outfile);
}

float* studentList::getHomework(int i)
{	//gets the homework for the ith student
	return (stuList.at(i)).getHomework();
}

float* studentList::getTest(int i)
{	//gets test scores for the ith student
	return (stuList.at(i)).getTest();
}

student& studentList::getStudent(int i)
{		//returns the ith student
  return stuList.at(i);
}

int studentList::searchById(string Id)
{  //returns the index if there is a match;  -1 otherwise.
  for (unsigned int index = 0; index < stuList.size(); index++)
   {
     if ((stuList.at(index)).getId() == Id)
         return index;
   }
  return -1;
}

int studentList::searchByName(char name[])
{  //returns the index if there is a match;  -1 otherwise.
  for (unsigned int index = 0; index < stuList.size(); index++)
  {
    if (strcmp(name, (stuList.at(index)).getName()) == 0)
        return index;
  }
  return -1;
}
