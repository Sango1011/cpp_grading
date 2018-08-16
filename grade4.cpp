//Sarah Ngo
//CSCI 201:  Final Project

/* This is an interactive grading program
it will execute the user's choice from a menu */

#include <iostream>
#include <fstream>
#include <cstring>

#include <string>
#include <iomanip>
#include "studentList.h"

using namespace std;

const int maxSize = 20; //at most 20 students
const int nameLength = student::nameLength;
const int idLength = student::idLength; // 8-character Id
studentList stuList(maxSize);


ofstream outfile;
ifstream infile;
char input_file_name[21], output_file_name[21], name[nameLength+1];
string id;

/*------------------------------------------------------------------------
  Functions used by main program and the user interface
  ------------------------------------------------------------------------*/

void showmenu()
{
  cout<< "Please type in  one of the following options: \n";
  cout<< "L or l  to load the student data \n";
  cout<< "D or d  to display  the student data \n";
  cout<< "P or p to process grades \n";
  cout<< "C or c to change a student's scores \n";
  cout<< "A or a to add a new student to the classlist \n";
  cout<< "S or s to search for a particular student's information \n";
  cout<< "R or r to print the grade results to a file \n";
  cout<< "M or m to display this menu \n";
  cout<< "E or e to save and exit \n";
}

void loadStudents()
{
    student s_temp;  float HomeworkScores[10];
	int participation; float TestScores[4];
	int size = 0; int x;
	
	cout << "Please enter name of the data file:  ";
	cin >> input_file_name;
	infile.open(input_file_name);
	
	if (!infile)
    {
		// abandons operation with error mesg
		cout << "Could not open input file \n";
		infile.close();
		infile.clear();
		return;
	}
	
	infile >> name; s_temp.setName(name); //read and store name in s_temp
	while(!infile.eof())
    {
		infile >> id; s_temp.setId(id);  //read and store id in s_temp

		// for loop stores the homework scores into an array. 
		for (int i = 0; i < 10; i++)
		{
			infile >> HomeworkScores[i];
		}

		s_temp.setHomework(HomeworkScores);
		infile >> participation; s_temp.setParticipation(participation);
		
		for (int i = 0; i < 4; i++)
		{
			infile >> TestScores[i];
		}
		s_temp.setTest(TestScores);
		
		if (!stuList.addStudent(s_temp))
		{	
			cout << "The file exceeded 20 students, only 20 students were read \n";
			break;
		}
		else
			cout << "Students were loaded successfully. \n";
		infile >> name;
		s_temp.setName(name);
		size++;
    }
	if (size == 0)
		cout << "The file was empty \n";

  infile.close();
  infile.clear();
}

void displayData()
{
	stuList.writeData(cout);
}

void processTheGrades()
{
	stuList.processGrade();
	cout << "Grades successfully processed. \n";
}

void changeScores()
{
	int i, x, index;
	float score;
	float* hw;
	float* t;
	cout << "Please enter id of the person:  ";
	cin >> id;
	i = stuList.searchById(id);
	if ( i!= -1)    
	{      
		cout << "Please input the score you would like to change:\n";
		cout << "   1 - homework   2 - Participation    3 - Test :  ";
		cin >> x;
		if (x == 1)
		{
			hw = stuList.getHomework(i);
			cout << "Please enter the index of the homework score to be changed: ";
			cin >> index;
			cout << "Please input the new score: ";
			cin >> score;
			hw[index] = score;
			(stuList.getStudent(i)).setHomework(hw); 
			cout << "Score successfullychanged. \n";
		}
		else if (x == 2)
		{
			cout << "Please input the new score: ";
			cin >> score;
			(stuList.getStudent(i)).setParticipation(score);
			cout << "Score successfullychanged. \n";
		}
		else if (x == 3)
		{
			t = stuList.getTest(i);
			cout << "Please input the index of the test score to be changed: ";
			cin >> index;
			cout << "Please input the new score: ";
			cin >> score;
			t[index] = score; 
			(stuList.getStudent(i)).setTest(t); 
			cout << "Score successfullychanged. \n";
		}
		else
			cout << "I'm sorry that was an invalid selection. \n";
	}
	else
		cout << "Sorry, there is no such student. \n";
}

void addNewStudent()
{
	student s_temp; float HomeworkScores[10], TestScores[4];
	int participation;
	
	cout << "Please enter the name of the student:  ";
	cin >> name; 
	s_temp.setName(name);		
	cout << "Please enter the id of the student:  ";
	cin >> id;
	s_temp.setId(id);
	cout << "Please enter the 10 homework scores:  \n";
	cin >> HomeworkScores[0] >> HomeworkScores[1]
		>> HomeworkScores[2] >> HomeworkScores[3]
		>> HomeworkScores[4] >> HomeworkScores[5]
		>> HomeworkScores[6] >> HomeworkScores[7]
		>> HomeworkScores[8] >> HomeworkScores[9];
	s_temp.setHomework(HomeworkScores);
	cout << "Please enter the participation score:  ";
	cin >> participation;
	s_temp.setParticipation(participation);
	cout << "Please enter the 4 test scores:  \n";
	cin >> TestScores[0] >> TestScores[1] >> TestScores[2] >> TestScores[3];
	s_temp.setTest(TestScores);
	
	if (stuList.addStudent(s_temp))
		cout << "Successfully added student. \n";
	else
		cout << "Sorry, the student could not be added. \n";
}

void searchStudent()
{
	int i, x, index;
	float score;
	char w;
	
	cout << "Would you like to search by name (y or n) ";
	cin >> w;
	
	if (w == 'n' || w =='N')
	{
		cout << "Please enter id of the person:  ";
		cin >> id;
		i = stuList.searchById(id);
	}
	else
	{
		cout << "Please enter the name of the person:  ";
		cin >> name;
		i = stuList.searchByName(name);
	}
	
	if ( i!= -1)    
	{   
		cout << "That student is in the list \n";
		cout << "Would you like to display the informaion (y or n)? ";
		cin >> w;
		if (w == 'y' || w == 'Y')
		{
			stuList.printStudent(i, cout);
			cout << endl << endl;
		}
		cout << "Would you like to print the information to a file (y or n)? ";
		cin >> w;
		if (w == 'y' || w == 'Y')
		{
			cout << "Please enter the name of the output file:  ";
			cin >> output_file_name;
			outfile.open(output_file_name);
			cout << endl;
	
			if (!outfile)
			{
			// abandons operation with error mesg
			cout << "Could not open input file \n";
			outfile.close();
			outfile.clear();
			return;
			}
			stuList.printStudent(i, outfile);
			outfile.close();
			outfile.clear();
			cout << "Information saved to " << output_file_name << endl;
		}
	}
	else
		cout << "Sorry, there is no such student. \n";
}

void printGrades()
{
	int x;
	cout << "Please enter name of the output file:  ";
	cin >> output_file_name;
	outfile.open(output_file_name);
	
	if (!outfile)
    {
		// abandons operation with error mesg
		cout << "Could not open input file \n";
		outfile.close();
		outfile.clear();
		return;
	}
	cout << "How would you like your report:" << endl;
	cout << "    1 for tabular or 2 for report" << endl;
	cin >> x;
	if (x == 1)
	{
		stuList.printTable(outfile);
		cout << "Grades have been saved to " << output_file_name << endl;
	}
	else if (x == 2)
	{
		stuList.printReport(outfile);
		cout << "Grades have been saved to " << output_file_name << endl;
	}
	else
		cout << "I am sorry that wasn't a valid selection \n"; 
	outfile.close();
	outfile.clear();
}

void saveData()
{
	cout << "Please enter name of the new data file:  ";
	cin >> output_file_name;
	outfile.open(output_file_name);
	if ( !outfile)
    {
		// abandons operation with error mesg
		cout << "Could not open  file \n";
		outfile.close();
		outfile.clear();
		return;
    }
	stuList.writeData(outfile);
	outfile.clear();
	outfile.close();
	cout << "Information saved to " << output_file_name << endl;
}


/* ---------------------- start of Main Program -----------------------------*/ 


int main()
{
	char choice;

	showmenu();
	cout << "Please indicate your choice of operation (m for menu): ";
	cin >> choice;

	while ((choice != 'e')&& (choice != 'E'))
    {
		switch(choice)
        {
			case 'l':
			case 'L': loadStudents(); break;
			case 'd':
			case 'D': displayData(); break;
			case 'p':
			case 'P': processTheGrades();break;
			case 'c':
			case 'C': changeScores();break;
			case 'a':
			case 'A': addNewStudent();break;
			case 's':
			case 'S': searchStudent();break;
			case 'r':
			case 'R': printGrades();break;
			case 'm':
			case 'M': showmenu();break;
			default : cout << "Not a valid choice" << endl;
        }
		cin.ignore(200, '\n'); cin.clear(); //clear out all input
		cout << "Please indicate your choice of operation (m for menu): ";
		cin >> choice;
    }
	saveData();
	cout << "Thank-you, good bye! \n";
}
