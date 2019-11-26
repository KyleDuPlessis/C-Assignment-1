//===============================================================================
// Name        : Database.cpp
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 18/02/2019
// Description : Program to build a simple database of student records, which can
//				 be queried for student information - written in C++, Ansi-style
//===============================================================================

#include "Database.h"

#include <iomanip>
#include <fstream> // file I/O - can use ifstream and ofstream objects
#include <sstream> // read input from a string (instead of a file) - can use istringstream (stringstream) objects

// this source file is the implementation of the database engine - implementing all the database functionality

void DPLKYL002::processMenuChoice(int menuChoice,
		vector<StudentRecord>& database) {

	// process user input menu choice
	switch (menuChoice) {

	case 0: // add a student
		DPLKYL002::getStudentInformationLine(database);
		break;

	case 1: // read database from simple text file (database.txt)
		DPLKYL002::displayDatabase();
		break;

	case 2: // save database to simple text file (database.txt)
		DPLKYL002::saveDatabase(database);
		break;

	case 3: // display student's information
		DPLKYL002::displayStudentRecord(database);
		break;

	case 4: // grade student
		DPLKYL002::gradeStudent(database);
		break;

	}
}

void DPLKYL002::setupDatabase(vector<StudentRecord>& database) {

	// setup database from information in database.txt (this info is stored in vector)
	string fileName = "database.txt";
	ifstream file(fileName.c_str());

	if (!file)
		cout << "Unable to open database.txt." << endl;

	database.clear();
	string studentInformationLine;

	while (getline(file, studentInformationLine)) { // get the full line including space characters
		addStudentToDatabase(studentInformationLine, database, true); // true flag - means don't display output msg for adding a new student / updating student information
	}

	file.close();
}

void DPLKYL002::getStudentInformationLine(vector<StudentRecord>& database) {

	cin.ignore(); // ignore newline left in input stream left by >> operator

	// process line containing student information
	cout
			<< "Enter student's information ['name' 'surname' 'student number' 'class record']:"
			<< endl;

	string studentInformationLine;
	getline(cin, studentInformationLine); // get the full line including space characters

	// add student to database
	addStudentToDatabase(studentInformationLine, database, false); // false flag - means display output msg for adding a new student / updating student information
}

void DPLKYL002::displayDatabase() {

	// display all student records saved in database
	vector<StudentRecord> database; // database is a vector of student records (like an array - container that holds student records)
	setupDatabase(database); // setup database from information in database.txt (this info is stored in vector)

	cout << "\t\t\t---------- STUDENT RECORDS DATABASE ----------\n" << endl; // print out heading
	writeStudentRecord("Name:", "Surname:", "Student Number:", "Class Record:"); // print out heading

	// display all database content (student records)
	for (int i = 0; i < database.size(); i++) { // loop through all student records in database (vector of student records)

		StudentRecord studentRecord = database.at(i);
		writeStudentRecord(studentRecord.Name, studentRecord.Surname,
				studentRecord.StudentNumber, studentRecord.ClassRecord); // print out student information line

	}

}

void DPLKYL002::writeStudentRecord(string name, string surname,
		string studentNumber, string classRecord) {

	// display all database content (student records) in a specific format
	cout.setf(ios::left, ios::adjustfield); // set format of student records

	cout << setw(25) << name;

	cout << setw(25) << surname;

	cout << setw(25) << studentNumber;

	cout << classRecord << endl;

	cout.unsetf(ios::adjustfield);

}

void DPLKYL002::addStudentToDatabase(string studentInformationLine,
		vector<StudentRecord>& database, bool flag) {

	stringstream ss; // stringstream allows you to read from the string as if it were a stream (like cin)
	ss.str(studentInformationLine); // write to stringstream object (set the contents of the buffer to the string argument)
	string name, surname, studentNumber, classRecord;

	// process line containing student information
	ss >> name; // read from stringstream object; like cin it stops when encounters a space or newline character
	studentInformationLine = studentInformationLine.erase(0,
			studentInformationLine.find_first_not_of(name) + 1); // remove 'name' from student information line
	ss.str(studentInformationLine); // write to stringstream object (set the contents of the buffer to the string argument)

	ss >> surname;
	studentInformationLine = studentInformationLine.erase(0,
			studentInformationLine.find_first_not_of(surname) + 1);
	ss.str(studentInformationLine);

	ss >> studentNumber;
	studentInformationLine = studentInformationLine.erase(0,
			studentInformationLine.find_first_not_of(studentNumber) + 1);
	ss.str(studentInformationLine); // the remaining line is the grades (class record)

	classRecord = ss.str(); // get the entire contents of stringstream object (returns the contents of its buffer in string type)

	// if student not found in database, add new student to database (store student in vector)
	if (getStudentRecord(studentNumber, database).StudentNumber
			== "NOT_FOUND") {

		// create a new StudentRecord struct with the four student information fields
		StudentRecord studentRecord;
		studentRecord.Name = name;
		studentRecord.Surname = surname;
		studentRecord.StudentNumber = studentNumber;
		studentRecord.ClassRecord = classRecord;
		// add new student to database (store student in vector)
		database.push_back(studentRecord);

		if (!flag) // false flag - means display output msg for adding a new student
			cout << studentNumber
					<< ": has successfully been added to the database!" << endl;

	}

	// else if student found in database, update student's information
	/*You may not have duplicate records (i.e. two or more records for the same student
	 number). When you enter new data, you must first check to see whether that student
	 exists. If so, overwrite the old data with the new, otherwise create a new record as
	 expected.
	 */

	else {

		for (int i = 0; i < database.size(); i++) { // loop through all student records in database (vector of student records)

			StudentRecord studentRecord = database.at(i);
			if (studentRecord.StudentNumber == studentNumber) { // find specific student in database

				database.at(i).Name = name; // update student's information
				database.at(i).Surname = surname;
				database.at(i).ClassRecord = classRecord;
				break;

			}
		}

		if (!flag) // false flag - means  display output msg for updating student information
			cout << studentNumber
					<< ": student information has successfully been updated!"
					<< endl;
	}
}

DPLKYL002::StudentRecord DPLKYL002::getStudentRecord(string studentNumber,
		vector<StudentRecord>& database) {

	// if student number found, return student in database
	for (int i = 0; i < database.size(); i++) { // loop through all student records in database (vector of student records)

		StudentRecord studentRecord = database.at(i);

		if (studentRecord.StudentNumber == studentNumber) // find specific student in database
			return studentRecord;

	}

	// if student number not found, return no record
	StudentRecord noRecord;
	noRecord.StudentNumber = "NOT_FOUND";
	return noRecord;

}

void DPLKYL002::gradeStudent(vector<StudentRecord>& database) {

	// calculate student's grade average from class record based on a given student number
	cout << "Enter student number: \n[using capital letters]" << endl;
	string studentNumber;
	cin >> studentNumber;

	StudentRecord studentRecord = getStudentRecord(studentNumber, database); // get specific student record from database (vector of student records)
	if (studentRecord.StudentNumber == "NOT_FOUND"){
		cout << "Student number not found in database." << endl;}
else{


	stringstream ss;
	ss.str(studentRecord.ClassRecord); // write to stringstream object (set the contents of the buffer to the string argument)

	// average calculated by extracting all the numbers in ClassRecord string and averaging them
	string grade;
	double sumGrades = 0;
	int numGrades = 0;

	while (ss >> grade) {

		sumGrades += stoi(grade);
		numGrades++;

	}

	double gradeAverage = sumGrades / numGrades;
	cout << studentRecord.StudentNumber << "\nGrade average: " << gradeAverage
			<< "%" << endl;
}

}

void DPLKYL002::displayStudentRecord(vector<StudentRecord>& database) {

	// display student information based on a given student number
	cout << "Enter student number: \n[using capital letters]" << endl;
	string studentNumber;
	cin >> studentNumber;

	// search for specific student number in database
	StudentRecord studentRecord = getStudentRecord(studentNumber, database);

	// if student number does not exist in database, return to menu screen
	if (studentRecord.StudentNumber == "NOT_FOUND"){
		cout << "Student number not found in database." << endl;}
else{


	// else if student number does exist in database, display student's information
	cout << "Student found in database!" << endl;
	writeStudentRecord("Name:", "Surname:", "Student Number:", "Class Record:");
	writeStudentRecord(studentRecord.Name, studentRecord.Surname,
			studentRecord.StudentNumber, studentRecord.ClassRecord);}
}

void DPLKYL002::saveDatabase(vector<StudentRecord>& database) {

	// save / write student(s) to database (database.txt)
	ofstream file("database.txt");

	if (file.is_open()) {

		for (int i = 0; i < database.size(); i++) { // loop through all student records in database (vector of student records)

			StudentRecord studentRecord = database.at(i);
			file << studentRecord.Name + " ";
			file << studentRecord.Surname + " ";
			file << studentRecord.StudentNumber + " ";
			file << studentRecord.ClassRecord + "\n";

		}

		file.close();
		cout << "Database successfully saved!" << endl;

	} // if file not found
	else {

		cout << "database.txt not found" << endl;

	}
}
