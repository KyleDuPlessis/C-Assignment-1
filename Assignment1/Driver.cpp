//===============================================================================
// Name        : Driver.cpp
// Author      : Kyle du Plessis [DPLKYL002]
// Date:       : 18/02/2019
// Description : Program to build a simple database of student records, which can
//				 be queried for student information - written in C++, Ansi-style
//===============================================================================

#include <iostream>
#include <typeinfo>
#include "Database.h"
#include "MenuInterface.h"

// main function
int main(void) {

	DPLKYL002::clearConsoleWindow(); // start with clearing terminal window
	vector<DPLKYL002::StudentRecord> database; // database is a vector of student records (like an array - container that holds student records)
	DPLKYL002::setupDatabase(database); // setup database from information in database.txt (this info is stored in vector)

	for (;;) { // loop forever since reading menu options continuously

			// display the simple menu-based interface
			DPLKYL002::displayMenu();

			// get user input menu choice
			char userInput;
			cin >> userInput;

			// if termination condition is 'q' is selected
			if (userInput == 'q')
				break; // exit from the application; any information not saved will be lost

			int menuChoice;
			menuChoice = userInput - '0'; // convert char number to int ('0' -> 0 etc.)

			if (menuChoice >= 0 && menuChoice <= 4) { // if user selected a valid input menu choice (0->4)

				processMenuChoice(menuChoice, database); // process user input menu choice
				cout << "Press Enter to clear screen and return to the menu: ";

				if (menuChoice != 0)
					cin.ignore(); // ignore newline left in input stream left by >> operator

				cin.get(); // wait for input (Enter to be pressed)
				DPLKYL002::clearConsoleWindow(); // clear terminal window

			} else { // else if user selected an invalid input menu choice

				cout << "Invalid menu option selected.";
				DPLKYL002::clearConsoleWindow(); // clear terminal window

			}
		}

		return 0;

		/* 'cin >> ...' stops when encounters a space or newline character.
		 When you're reading an integer with cin >> a;, you're typing <digit> <digit> <digit> <digit> <ENTER> on the keyboard.
		 operator >> for integers consumes the digits, but goes no further, the <ENTER> is still waiting to be processed.
		 Your first cin.get() reads and returns that <ENTER> as the character '\n', which you don't assign anywhere.
		 Your second cin.get() reads and returns the next character to be entered, and since there's nothing after that Enter, it waits (for input).
		 Note that if you enter <digit> <digit> <digit> <SPACE> <ENTER>, your double-cin-get will fail: the first will read the space, the second will read the enter, and the program will complete immediately.
		 You called the the input operator ( >> ) and that left a newline in the stream. The first cin.get() takes that character. The second one waits for input.
		 You can keep it as two cin.get() functions. Or after your last ( >> ) statement you can use a cin.ignore() statement.
		 */

}
