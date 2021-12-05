#include <iostream>
#include <string>
#include "contactClass.h"


//TODO find a way to fix memory leak

using namespace std;

/**
 * For project 4 you are asked to create and maintain contact information (name and phone number). Your program must include the following functionality:
 * 1) add a new contact
 * 2) remove a contact
 * 3) update contact info
 * 4) display contacts in ascending order by last name
 * 5) find the contact info for a particular person
 */

//input a character will mostly crash the program
//TODO find a way to fix this
void promptMenu() {
	char confirm;
	contactList newList;
	string firstName, lastName, phoneNumber, error;
	int menuChoice, choice;
	bool loop;
	cout
			<< "1) Add a new contact\n2) Delete a contact\n3) Update contact info\n4) Display contacts in ascending order by last name\n5) Find the contact info for a particular person\n6) Exit\n=================================================="
			<< endl;
	cout << "> ";
	cin >> menuChoice;
	// a while condition here will cause a crash loop if you entered a string
	if (menuChoice < 1 || menuChoice > 6) {
		cout << "Fatal crash - Invalid input" << endl;
	} else {
		while (menuChoice != 6) {
			if (menuChoice == 1) {
				cout << "You have chosen to add a new contact\nPlease enter the first name of the contact" << endl;
				cout << "> ";
				cin >> firstName;
				cout << "Please enter the last name of the contact" << endl;
				cout << "> ";
				cin >> lastName;
				cout << "Please enter the phone number of the contact" << endl;
				cout << "> ";
				cin >> phoneNumber;
				contactNode newContact(firstName, lastName, phoneNumber);
				try {
					newList.addContact(newContact);
					cout << "Contact added successfully" << endl;
				} catch (string error) {
					cout << error << endl;
				}
			} else if (menuChoice == 2) {
				cout << "You have chosen to remove a contact\nPlease enter the first name of the contact" << endl;
				cout << "Please enter the phone number of the contact that you want to remove" << endl;
				cout << "> ";
				cin >> phoneNumber;
				try {
					newList.removeContact(phoneNumber);
					cout << "Contact removed successfully" << endl;
				} catch (string error) {
					cout << "Internal error removing contact" << error << endl;
				}
			} else if (menuChoice == 3) {
				cout
						<< "You have chosen to update a contact\nPlease enter the phone number of the contact you would like to update."
						<< endl;
				cin >> phoneNumber;
				if (!newList.isContactInList(phoneNumber)) {
					cout << "Contact not found" << endl;
				} else {
					cout << "Which of the following would you like to update contact for?";
					cout << "1) First name\n2) Last name\n3) Phone number";
					cout << "> ";
				};
				cin >> choice;
				while (choice < 1 || choice > 3) {
					cout << "Invalid choice, try again" << endl;
					cout << "> ";
					cin >> choice;
				}
				try {
					if (choice == 1) {
						string oldValue = newList.getFirstName(phoneNumber);
						cout << "What would you like to change the first name to?" << endl;
						cin >> firstName;
						newList.updateContact(phoneNumber, choice, firstName);
					} else if (choice == 2) {
						string oldValue = newList.getLastName(phoneNumber);
						cout << "What would you like to change the last name to?" << endl;
						cin >> lastName;
						newList.updateContact(phoneNumber, choice, lastName);
					} else if (choice == 3) {
						string oldValue = newList.getPhoneNumber(phoneNumber);
						cout << "What would you like to change the phone number to?" << endl;
						cin >> phoneNumber;
						newList.updateContact(phoneNumber, choice, phoneNumber);
					}
				} catch (string error) {
					cout << "Internal error updating contact" << error << endl;
				}
			} else if (menuChoice == 4) {
				try {
					newList.printSortedList();
				} catch (string error) {
					cout << "Internal error displaying contacts" << error << endl;
				}
			} else if (menuChoice == 5) {
				cout << "Please enter the phone number of the contact" << endl;
				cin >> phoneNumber;
				try {
					newList.searchForContact(phoneNumber);
				} catch (string error) {
					cout << "Internal error finding contact" << error << endl;
				}
			} else if (menuChoice == 6) {
				exit(0);
			}
			cout << "Would you like to continue? (y/n)" << endl;
			cout << "> ";
			cin >> confirm;
			while (confirm != 'y' && confirm != 'n') {
				cout << "Invalid input, please try again" << endl;
				cout << "> ";
				cin >> confirm;
			}
			if (confirm == 'n') {
				exit(0);
			} else if (confirm == 'y') {
				promptMenu();
			}
		}
	}
}



/**
 * Main function
 * @author Min CHun Fu
 * @version 1.0
 */
int main() {

	cout
			<< "Welcome to the contact manager!\nPlease choose which function you would like to execute by entering the corresponding number\n==========================================================="
			<< endl;

	//think about a way to prevent data from refreshing EDIT: done wooohoo
	//I tried using switch case but that doesn't work that great. Sorry for this ugly cout code.
	promptMenu();
	return 0;
}