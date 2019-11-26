//===============================================================================
// Name        : Database.h
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 18/02/2019
// Description : Program to build a simple database of student records, which can
//				 be queried for student information - written in C++, Ansi-style
//===============================================================================

#include <iostream>
#include <vector>
#include <string>

#ifndef LIBS_DATABASE_H
#define LIBS_DATABASE_H

using namespace std; // this is correct - they use std:: in .h in the tutorial pdf

namespace DPLKYL002 {

struct StudentRecord {

	string Name;
	string Surname;
	string StudentNumber;
	string ClassRecord;

};

void processMenuChoice(int menuChoice, vector<StudentRecord>& database);
void setupDatabase(vector<StudentRecord>& database);
void getStudentInformationLine(vector<StudentRecord>& database);
void displayDatabase();
void writeStudentRecord(string name, string surname, string studentNumber,
		string classRecord);
void addStudentToDatabase(string studentInformationLine, vector<StudentRecord>& database,
		bool setup);
StudentRecord getStudentRecord(string studentNumber,
		vector<StudentRecord>& database);
void gradeStudent(vector<StudentRecord>& database);
void displayStudentRecord(vector<StudentRecord>& database);
void saveDatabase(vector<StudentRecord>& database);

}

#endif
