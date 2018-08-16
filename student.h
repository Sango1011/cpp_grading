#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>
#ifndef STUDENT
#define STUDENT
using namespace std;


class student{

 public:
  const static int nameLength = 20;
  const static int idLength = 8;
  const static int maxScores = 10;

 private:
  char name[nameLength];  // name is stored as an array of char
  string id;  // id stored as string
  float participation, HwTotal, TestTotal, finalscore;
  char grade;
  float HomeworkScores[maxScores], TestScores[4];
  
  	void FinalHWScore (float sum)		//computes the aggregated HW and Participation score
	{
		if (sum == -1)
			HwTotal = -1;
		else
			HwTotal = sum/20;			//divide by 20 to scale to 50
	}
	
	void FinalTestScore(float tests)
	{
		if (tests == -1)
			TestTotal = -1;
		else
			TestTotal = tests/8;	//divide by 400 then take half (same as division by 8)									
	}
	
	void TotalScore ()
	{
		if (HwTotal == -1 || TestTotal == -1)
			finalscore = -1;
		else 
			finalscore = HwTotal + TestTotal;
	}
	
	void letterGrade()
	{
	/*Calculates the letter grade */
	
		if (finalscore >= 90)
			grade = 'A';
		else if (finalscore >=80)
			grade = 'B';
		else if (finalscore >=70)
			grade = 'C';
		else if (finalscore >=60)
			grade = 'D';
		else if (finalscore >= 0)
			grade = 'F';
		else
			grade = 'Z';
	}

  
 public:

	void setName(char n[]) // parameter is array of char, to match name
    {
		strcpy(name, n); // need this function; cannot assign arrays
    }

	void setId(string n) // parameter is a string object
    {
		id =  n; 
    }

	void setHomework(float homework[])  //array of floats
    {
		for (int i = 0; i < 10; i++)
			HomeworkScores[i] = homework[i];
    }

	void setTest(float test[])		//array of floats
    {
		for (int i = 0; i < 4; i++)
			TestScores[i] = test[i];
    }

	void setParticipation (int p)
	{
		participation = p;
	}

	string getId() // returns a string
    {
		return id;
    }

	float* getHomework()	//returns a array
    {
		return HomeworkScores;
    }
  
	float* getTest()	//returns an array
	{
		return TestScores;
	}

	char* getName() // returns an array of char
    {
		return name;
    }
	
	void processStudent()
	{
		bool error = false, Terror = false;
		float sum = 0, lowscore = 100, tests = 0, total;
		
		for (int i = 0; i < maxScores; i++)
		{
			sum += HomeworkScores[i];		//sum all the honmework scores together
			if (HomeworkScores[i] < 0 || HomeworkScores[i] > 100)
				error = true;					//checking for socres that aren't allowed
			if (lowscore > HomeworkScores[i])
				lowscore = HomeworkScores[i];	//keep track of low score to drop
		}
		
		if (participation < 0 || participation > 100)
			error = true;
		
		sum -= lowscore;		//drop low homework score
		sum += participation;  	//add in participation score
		
		for(int i=0; i < 4; i++)
		{
			tests += TestScores[i];			//sum the test scores
			if ((TestScores[i] < 0) || (TestScores[i] > 100))
				Terror = true;				//checking for scores that aren't allowed
		}
				
		if (error)			//if any socre is outside the limits
			sum = -1;		//return a -1
		if (Terror)
			tests = -1;
		
		FinalHWScore (sum);
		FinalTestScore (tests);
		TotalScore();
		letterGrade ();
	}
	
	void printRecord ( ostream& outfile)
	{
		//prints on one line with uniform field widths
		//describing the student's progress
		
		outfile << setw(nameLength + 2) << name
				<< setw(idLength + 2) << id
				<< setw(10) << HwTotal
				<< setw(10) << TestTotal
				<< setw(10) << finalscore
				<< setw(5) << grade << endl;
	}
	
	void writeStudent( ostream& outfile)
    {
		// saves the raw data to the specified stream
		char space = ' ';
		outfile << name << space << id << space;
		for (int i = 0; i < maxScores; i++)
			outfile << HomeworkScores[i] << space;
		
		outfile << participation << space;
		
		for (int j = 0; j < 4; j++)
			outfile << TestScores[j] << space;
    }
	
	void printReport ( ostream& outfile)
	{		//prints a multi-line report for a student
			//describing the grade
		outfile << "Name:   "<<  name << endl
			<< "Id:   "<<  id << endl
			<< "Homework/Participation:  " << HwTotal << endl
			<< "Tests:  " << TestTotal << endl
			<< "Total Score:  " << finalscore << endl
			<< "Grade:   " << grade << endl
			<<"--------------------------------"<< endl << endl;
	}
};
#endif
