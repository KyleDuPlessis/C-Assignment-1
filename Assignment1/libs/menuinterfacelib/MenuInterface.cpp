//===============================================================================
// Name        : MenuInterface.cpp
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 18/02/2019
// Description : Program to build a simple database of student records, which can
//				 be queried for student information - written in C++, Ansi-style
//===============================================================================

#include "MenuInterface.h"

#include <cstdlib>

// this source file is the implementation of the simple menu-based interface

void DPLKYL002::displayMenu() {

	// display the simple menu-based interface
	cout << "\n\t---------- MENU ----------\n" << endl;
	cout << "[0] : add a student (or overwrite existing student)" << endl;
	cout << "[1] : read (view) database" << endl;
	cout << "[2] : save (write to) database" << endl;
	cout << "[3] : display student's data" << endl;
	cout << "[4] : grade student" << endl;
	cout << "[q] : quit" << endl;
	cout << "\nSelect a number [0->4]: \n[or 'q' to quit program]" << endl;

}

void DPLKYL002::clearConsoleWindow(void) {
	system("clear"); // clear terminal window
}
